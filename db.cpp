#include "db.h"
#include<sstream>
#include<cassert>
#include<algorithm>
#include "curl.h"
#include "util.h"

namespace tba{

std::ostream& operator<<(std::ostream& o,Fetch_result const& a){
	o<<"Fetche_results( ";
	#define X(A,B) o<<""#B<<":"<<a.B<<" ";
	FETCH_RESULT(X)
	#undef X
	return o<<")";
}

static int callback2(void *data,int arg,char **argv,char **azColname);

Sqlite::Sqlite(const char *filename){
	int rc=sqlite3_open(filename,&db);
	if(rc){
		std::ostringstream ss;
		ss<<"Could not open database: "<<filename;
		throw std::runtime_error{ss.str()};
	}
}

Sqlite::~Sqlite(){
	sqlite3_close(db);
}

Sqlite::operator sqlite3 *()const{ return db; }

std::vector<Row> Sqlite::query(std::string const& s){
	std::vector<Row> r;
	r.reserve(1);
	char *err_msg;
	int rc=sqlite3_exec(db,s.c_str(),callback2,&r,&err_msg);
	if(rc!=SQLITE_OK){
		std::ostringstream ss;
		ss<<"SQL error:"<<err_msg<<" tried running: "<<s;
		sqlite3_free(err_msg);
		throw std::runtime_error{ss.str()};
	}
	return r;
}

static int callback2(void *data,int argc,char **argv,char **azColname){
	std::vector<Row> &r=*(std::vector<Row>*)data;
	Row row;
	row.reserve(argc);
	for(int i=0;i<argc;i++){
		row.push_back(std::make_pair(azColname[i],argv[i]));
	}
	r.push_back(std::move(row));
	return 0;
}

using Date=std::string;

Fetch_result Fetcher::fetch(URL url,std::optional<ETag> etag_in)const{
	auto g=tba::get_url(
		url,
		[&](){
			std::vector<std::string> r;
			r|={"X-TBA-Auth-Key: "+auth_key};
			if(etag_in){
				r|="ETag: "+*etag_in;
			}
			return r;
		}()
	);

	auto get_header=[&](std::string name)->std::optional<std::string>{
		auto f=std::find_if(g.headers.begin(),g.headers.end(),[=](auto const& p){ return p.first==name; });
		if(f!=g.headers.end()){
			return f->second;
		}
		return std::nullopt;
	};

	auto date=[&]()->std::optional<std::string>{
		auto f2=std::find_if(g.headers.begin(),g.headers.end(),[](auto const& p){ return p.first=="Date" || p.first=="date"; });
		if(f2!=g.headers.end()){
			return f2->second;
		}
		return std::nullopt;
	}();

	auto etag_out=[&]()->std::optional<std::string>{
		auto f=std::find_if(g.headers.begin(),g.headers.end(),[](auto const& p){ return p.first=="ETag"; });
		if(f!=g.headers.end()){
			return f->second;
		}
		return std::nullopt;
	}();

	assert(date);

	return Fetch_result(
		date,
		etag_out,
		get_header("Cache-Control"),
		g.data
	);

	/*{
		std::ostringstream ss;
		ss<<"fetching:"<<url<<"\n";
		//ss<<"got:"<<g.headers<<"\n";
		ss<<"got:\n";
		for(auto elem:g.headers) ss<<elem<<"\n";
		ss<<"Error: Did not find Last-Modified header";
		throw std::runtime_error{ss.str()};
	}*/
}

Cache_policy::Cache_policy(Type type1):type_(type1){}

Cache_policy::Type Cache_policy::type()const{ return type_; }

HTTP_Date const& Cache_policy::date()const{
	assert(type()==Type::DATE);
	return date_;
}

Cache_policy Cache_policy::any(){ return Cache_policy{Type::ANY}; }

Cache_policy Cache_policy::date(Date date){
	Cache_policy r{Type::DATE};
	r.date_=date;
	return r;
}

Cache_policy Cache_policy::none(){ return Cache_policy{Type::NONE}; }

Cache::Cache(const char *filename):db(filename),policy(Cache_policy::any()){
	db.query("CREATE TABLE IF NOT EXISTS cache (url STRING UNIQUE NOT NULL,date INT NOT NULL,body VARCHAR NOT NULL);");

	db.query(
		"CREATE TABLE IF NOT EXISTS cache2 ("
		       	//could make this enforce uniqueness, but want to be able to keep track of how data changes
			//so queries will have to ask for the most recent.
			"url TEXT NOT NULL,"

			//because sqlite does not include a real date/time type
			//this will be UNIX time, in relative to GMT.
			"date INTEGER NOT NULL,"

			//supposedly included in all the queries, so hopefully the non-null is ok.
			"etag TEXT NOT NULL,"

			"cache_control TEXT NOT NULL,"

			"body TEXT NOT NULL"
		") STRICT;" //strict not used originally because it didn't exist yet.
	);
}

Cache::Cache():Cache("cache.db"){
}

void Cache::update(URL url,Fetch_result a){
	assert(a.date);
	
	//const char* sql = "INSERT INTO cache (url, date, etag, body) VALUES (?, ?, ?)";
	
	//const char *sql="UPDATE cache2 SET date=?, body=?, WHERE url=?";
	//nyi



	update(url,std::pair<Date,Data>(*a.date,a.data));
}

void Cache::update(URL url,std::pair<Date,Data> p){
	const char *sql="UPDATE cache SET date=?, body=? WHERE url=?";
	sqlite3_stmt *stmt;

	{
		int r=sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
		if(r!=SQLITE_OK){
			std::stringstream ss;
			ss<<"sqlite3: Failed to prepate statement: "<<sqlite3_errstr(r);
			throw ss.str();
		}
	}

	auto bind=[&](int index,std::string const& s){
		int r=sqlite3_bind_text(stmt,index,s.c_str(),s.size(),SQLITE_STATIC);
		if(r!=SQLITE_OK){
			throw "sqlite3_bind_text";
		}
	};

	bind(1,p.first);
	bind(2,p.second);
	bind(3,url);

	{
		int r=sqlite3_step(stmt);
		if(r!=SQLITE_DONE){
			std::stringstream ss;
			ss<<"sqlite3: Execution failed: "<<sqlite3_errstr(r);
			throw ss.str();
		}
	}

	{
		auto r=sqlite3_finalize(stmt);
		if(r!=SQLITE_OK){
			throw "sqlite3_finalize";
		}
	}
}

void Cache::add(URL url,std::pair<Date,Data> p){
	auto date=p.first;
	auto body=p.second;

	const char* sql = "INSERT INTO cache (url, date, body) VALUES (?, ?, ?)";
	sqlite3_stmt *stmt;

	{
		int r = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		if (r != SQLITE_OK) {
			std::stringstream ss;
			ss<< "Failed to prepare statement: " << sqlite3_errstr(r);
			throw ss.str();
		}
	}

	//Note the 1-based index
	auto bind=[&](int index,std::string const& s){
		int r=sqlite3_bind_text(stmt,index,s.c_str(),s.size(),SQLITE_STATIC);
		if(r!=SQLITE_OK){
			throw "sqlite3 failed";
		}
	};
	bind(1,url);
	bind(2,date);
	bind(3,body);

	{
		int r=sqlite3_step(stmt);
		if (r!=SQLITE_DONE){
			std::stringstream ss;
			ss<<"sqlite3: Execution failed: "<<sqlite3_errstr(r);
			throw ss.str();
		}
	}

	{
		auto r=sqlite3_finalize(stmt);
		if(r!=SQLITE_OK){
			throw "sqlite3 error";
		}
	}
}

void Cache::add(URL url,Fetch_result fr){
	if(!fr.date){
		TBA_PRINT(fr);
	}
	assert(fr.date);
	return add(
		url,
		make_pair(*fr.date,fr.data)
	);
}

struct Mutex_lock{
	std::mutex &mutex;

	Mutex_lock(std::mutex &m):mutex(m){
		m.lock();
	}

	~Mutex_lock(){
		mutex.unlock();
	}
};

std::optional<std::pair<Date,Data>> Cache::fetch(URL url){
	switch(policy.type()){
		case Cache_policy::Type::NONE:
			return {};
		case Cache_policy::Type::ANY:
			break;
		default:
			TBA_NYI
	}
	Mutex_lock lock(mutex);
	std::ostringstream ss;
	ss<<"SELECT date,body FROM cache WHERE url=\'"<<url<<"\'";
	auto r=db.query(ss.str());
	if(r.size()==0){
		return {};
	}
	if(r.size()==1){
		auto &x=r[0];
		assert(x.size()==2);
		auto &date=x[0].second;
		auto &body=x[1].second;
		//cout<<"date:"<<date<<"\n";
		//cout<<"body:"<<body<<"\n";
		assert(date);
		assert(body);
		return make_pair(std::move(*date),std::move(*body));
	}
	assert(0);TBA_NYI
}

std::pair<Date,Data> Cached_fetcher::fetch(URL url){
	auto c=cache.fetch(url);
	if(c) return std::move(*c);
	auto f=fetcher.fetch(url,std::nullopt);
	cache.add(url,f);
	TBA_PRINT(url);
	assert(f.date);
	return make_pair(*f.date,f.data);
}

Nonempty_string::Nonempty_string(std::string s1):s(std::move(s1)){}

std::string const& Nonempty_string::str()const{
	return s;
}

std::string operator+(const char *s1,Nonempty_string const& s2){
	return s1+s2.str();
}

}

