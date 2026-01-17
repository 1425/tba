#include "tba.h"
#include<iostream>
#include<algorithm>
#include<future>
#include<queue>
#include<variant>
#include<fstream>
#include<optional>
#include<set>
#include "data.h"
#include "curl.h"
#include "db.h"
#include "util.h"
#include "simdjson.h"

namespace tba{

template<typename T>
std::vector<T> reversed(std::vector<T> a){
	reverse(a.begin(),a.end());
	return a;
}

class NullBuffer:public std::streambuf{
	public:
	int overflow(int c){ return c; }
};

template<typename T>
std::vector<T> range(T a,T b){
	std::vector<T> r;
	for(T at=a;at<b;++at){
		r|=at;
	}
	return r;
}

template<typename T>
std::vector<T> range(T lim){
	std::vector<T> r;
	for(T at=0;at<lim;++at){
		r.push_back(at);
	}
	return r;
}

template<typename T>
std::string to_string(T a){
	std::ostringstream ss;
	ss<<a;
	return ss.str();
}

template<typename T>
std::vector<T> take(size_t num,std::vector<T> in){
	std::vector<T> out;
	copy_n(begin(in),std::min(num,in.size()),back_inserter(out));
	return out;
}

template<typename T>
std::vector<T> take_last(size_t num,std::vector<T> in){
	std::vector<T> out;
	auto num_out=std::min(num,in.size());
	copy_n(begin(in)+(in.size()-num_out),num_out,back_inserter(out));
	return out;
}

std::vector<std::string> args(int argc,char **argv){
	std::vector<std::string> r;
	for(int i=1;i<argc;i++){
		r|=std::string{argv[i]};
	}
	return r;
}

template<typename T>
std::vector<T> tail(std::vector<T> a){
	std::vector<T> r;
	for(size_t i=1;i<a.size();i++){
		r|=a[i];
	}
	return r;
}

//start program-specific stuff

#define nyi TBA_NYI

using namespace std;

void do_indent(int indent){
	for(auto i:range(indent)){
		(void)i;
		std::cout<<"\t";
	}
}

template<typename T>
void print_r(int indent,T t){
	do_indent(indent);
	std::cout<<t<<"\n";
}

template<typename T>
void print_r(int indent,std::optional<T> const& a){
	if(a) return print_r(indent,*a);
	do_indent(indent);
	cout<<"NULL\n";
}

template<typename A,typename B>
void print_r(int indent,std::pair<A,B> const& p){
	do_indent(indent);
	cout<<"pair\n";
	indent++;
	print_r(indent,p.first);
	print_r(indent,p.second);
}

template<typename K,typename V>
void print_r(int indent,std::map<K,V> const& m){
	do_indent(indent);
	cout<<"map\n";
	indent++;
	for(auto p:m){
		print_r(indent,p);
	}
}

template<typename T>
void print_r(int indent,std::vector<T> const& a){
	do_indent(indent);
	cout<<"vector\n";
	indent++;
	for(auto x:a){
		print_r(indent,x);
	}
}

void print_r(int,int)TBA_NYI

void print_r(int indent,Event_OPRs const& e){
	do_indent(indent);
	std::cout<<"Event_OPRs\n";
	indent++;
	#define X(A,B) {\
		do_indent(indent);\
		std::cout<<""#B<<"\n";\
		print_r(indent+1,e.B);\
	}
	TBA_EVENT_OPRS(X)
	#undef X
}

#define PRINT_R_ITEM(A,B) {\
		do_indent(indent);\
		std::cout<<""#B<<"\n";\
		print_r(indent+1,a.B);\
	}

#define PRINT_R(NAME,LIST)\
	void print_r(int indent,NAME const& a){\
		do_indent(indent);\
		std::cout<<""#NAME<<"\n";\
		indent++;\
		LIST(PRINT_R_ITEM)\
	}


PRINT_R(Event,TBA_EVENT)
PRINT_R(Dcmp_history,TBA_DCMP_HISTORY)
PRINT_R(District_data,TBA_DISTRICT_DATA)
PRINT_R(District_insights,TBA_DISTRICT_INSIGHTS)

template<typename T>
void print_r(T t){
	print_r(0,t);
}

template<typename Func,typename T>
auto mapv(Func f,std::vector<T> const& a){
	for(auto const& elem:a){
		f(elem);
	}
}

void csv_export(Zebra const& a){
	cout<<"event,time,";
	for(auto x:a.alliances.red){
		cout<<x.team_key<<"_x,"<<x.team_key<<"_y,";
	}
	for(auto x:a.alliances.blue){
		cout<<x.team_key<<"_x,"<<x.team_key<<"_y,";
	}
	cout<<"\n";

	for(auto i:range(a.times.size())){
		cout<<a.key<<",";
		cout<<a.times[i]<<",";
		auto show_team=[&](Zebra_team x){
			cout<<x.xs[i]<<",";
			cout<<x.ys[i]<<",";
		};
		mapv(show_team,a.alliances.red);
		mapv(show_team,a.alliances.blue);
		cout<<"\n";
	}
}

struct Args{
	bool quick=0;
	std::optional<Event_key> opr_event;
	std::optional<std::string> tba_key;
	bool show_cache=0;
};

Args parse_args(int argc,char **argv){
	auto a=args(argc,argv);
	Args r;

	struct Flag{
		string s;
		vector<string> args;
		std::string help;
		std::function<void(std::vector<std::string>)> f;
	};

	vector<Flag> flags{
		Flag{
			"--short",vector<string>{},
			"Pull down and check less data",
			[&](vector<string>){
				r.quick=1;
			}
		},
		Flag{
			"--opr",{"EVENT_CODE"},
			"Show the OPRs from the given event code",
			[&](vector<string> v){
				r.opr_event=Event_key{v[0]};
			}
		},
		Flag{
			"--tba_key",{"KEY"},
			"Specify the key to use when talking to The Blue Alliance, rather than having it be read from a file",
			[&](vector<string> v){
				r.tba_key=v[0];
			}
		},
		Flag{
			"--show_cache",vector<string>{},
			"Show what's in the cache",
			[&](vector<string> const& v){
				assert(v.empty());
				r.show_cache=1;
			}
		}
	};

	flags|=Flag{
		"--help",{},
		"Show this message",
		[&](vector<string>){
			cout<<"./demo";
			for(auto flag:flags){
				cout<<" ["<<flag.s;
				for(auto arg:flag.args){
					cout<<" "<<arg;
				}
				cout<<"]";
			}
			cout<<"\n\n";

			for(auto flag:flags){
				cout<<flag.s<<"\n";
				cout<<"\t"<<flag.help<<"\n";
			}

			exit(0);
		}
	};

	auto find=[&](auto s)->optional<Flag>{
		for(auto f:flags){
			if(f.s==s){
				return f;
			}
		}
		return std::nullopt;
	};

	for(auto at=a.begin();at!=a.end();){
		auto f=find(*at);
		if(!f){
			cerr<<"Unrecognized flag: \""<<*at<<"\"\n";
			exit(1);
		}
		at++;
		vector<string> v;
		for(size_t i=0;i<f->args.size() && at!=a.end();i++,++at){
			v|=*at;
		}
		if(v.size()<f->args.size()){
			cerr<<"Error: missing argument to "<<f->s<<"\n";
			exit(1);
		}
		f->f(v);
	}

	return r;
}

void show_cache(){
	Sqlite db("cache.db");//TODO: Make this configurable
	auto x=db.query("SELECT url,date FROM cache");
	print_lines(x);
}

template<typename T>
auto to_set(std::vector<T> a){
	return std::set<T>{a.begin(),a.end()};
}

int main1(int argc,char **argv){
	auto aa=parse_args(argc,argv);
	std::string tba_key;
	bool quick=aa.quick;
	std::optional<Event_key> opr_event=aa.opr_event;

	if(aa.tba_key){
		tba_key=*aa.tba_key;
	}else{
		std::ifstream f("auth_key");
		if(!f.good()){
			std::cerr<<"Error: Could not find auth key.  Either specify one as a command line argument or in a file named \"auth_key\"\n";
			return 1;
		}
		getline(f,tba_key);
		if(tba_key.empty()){
			std::cerr<<"Error: Failed to read auth key.\n";
			return 1;
		}
	}

	if(aa.show_cache){
		show_cache();
		return 0;
	}

	Cached_fetcher f{Fetcher{Nonempty_string{tba_key}},Cache{}};

	//auto s=status(f);
	//TBA_PRINT(s);

	for(auto name:{"ca","pnw","fma","mar"}){
		auto d=dcmp_history(f,name);
		auto d1=history(f,name);
		auto d2=insights(f,name);
		//print_r(d2);
	}
	for(District_key k:vector{District_key("2025pnw")}){
		auto a1=advancement(f,k);
		//TBA_PRINT(a1);
		auto a2=awards(f,k);
		//TBA_PRINT(a2);
	}

	TBA_PRINT(team(f,Team_key(1425)));

	static const bool ZEBRA_DEMO=0;
	if(ZEBRA_DEMO){
		Match_key match{"2019cc_qm3"};
		auto z=zebra_motionworks(f,match);
		//TBA_PRINT(z);
		csv_export(z);
		exit(0);
	}

	if(opr_event){
		auto d=event_oprs(f,*opr_event);
		//std::cout<<d<<"\n";//TBA_NYI
		print_r(d);
		return 0;
	}

	//auto years=range(Year{1992},Year{2023});//could get this via the API.
	auto years=range(Year{2026},Year{2027});//could get this via the API.

	std::vector<Event_key> event_key_list;

	NullBuffer null_buffer;
	std::ostream null_stream(&null_buffer);

	for(auto year:years){
		null_stream<<events(f,year).size()<<"\n";
		null_stream<<events_simple(f,year).size()<<"\n";
		event_key_list|=events_keys(f,year);
	}

	std::vector<Match_key> match_keys;

	auto select=[&](auto a){
		if(quick){
			return take_last(10,a);
		}
		return a;
	};
	using namespace std;

	for(auto event_key:take(10,select(event_key_list))){
		null_stream<<event(f,event_key)<<"\n";
		null_stream<<event_simple(f,event_key)<<"\n";
		null_stream<<event_alliances(f,event_key)<<"\n";
		null_stream<<event_insights(f,event_key)<<"\n";
		null_stream<<event_oprs(f,event_key)<<"\n";
		null_stream<<event_predictions(f,event_key)<<"\n";
		null_stream<<event_rankings(f,event_key)<<"\n";

		//skip district points for now.
		try{
			null_stream<<event_district_points(f,event_key)<<"\n";
		}catch(Decode_error e){
			cout<<"event_district_points(...)\n";
		}

		null_stream<<event_matches(f,event_key)<<"\n";
		null_stream<<event_matches_simple(f,event_key)<<"\n";

		match_keys|=event_matches_keys(f,event_key);

		null_stream<<event_awards(f,event_key)<<"\n";
	}

	for(auto match_key:select(reversed(match_keys))){
		try{
			null_stream<<match(f,match_key)<<"\n";
		}catch(Decode_error){
			cout<<"match(...)\n";
		}
		try{
			null_stream<<match_simple(f,match_key)<<"\n";
		}catch(Decode_error){
			cout<<"match_simple(...)";
		}
	}

	std::vector<Team_key> team_keys1;
	for(auto i:range(20)){
		null_stream<<teams(f,i)<<"\n";
		null_stream<<teams_simple(f,i)<<"\n";
		//null_stream<<team_keys(f,i)<<"\n";
		team_keys1|=team_keys(f,i);
	}

	std::vector<District_key> district_keys;//TODO: Fill this in.
	
	for(auto year:select(years)){
		auto d=districts(f,year);
		for(auto a:d){
			district_keys|=a.key;
		}
		TBA_PRINT(year);
		TBA_PRINT(district_keys);
	}

	//These are all known to work
	for(auto district:select(district_keys)){
		null_stream<<district_events(f,district)<<"\n";
		null_stream<<district_events_keys(f,district)<<"\n";
		null_stream<<district_events_simple(f,district)<<"\n";

		null_stream<<district_teams(f,district)<<"\n";
		null_stream<<district_teams_simple(f,district)<<"\n";
		null_stream<<district_teams_keys(f,district)<<"\n";

		null_stream<<district_rankings(f,district)<<"\n";
	}

	std::queue<std::future<int>> q;

	auto add_to_queue=[&](std::function<int(void)> f){
		q.push(async(f));
		while(q.size()>1000){
			q.front().get();
			q.pop();
		}
	};

	for(auto team:take(5,select(team_keys1))){
		add_to_queue([&f,team](){ team_events(f,team); return 0; });
		add_to_queue([&f,team](){ team_events_simple(f,team); return 66; });
		add_to_queue([&f,team](){ team_events_keys(f,team); return 67; });
		add_to_queue([&f,team](){ team_districts(f,team); return 68; });
	}

	for(auto event:select(reversed(event_key_list))){
		null_stream<<event_teams(f,event)<<"\n";
		null_stream<<event_teams_simple(f,event)<<"\n";
		//std::cout<<event<<".";
		//std::cout.flush();
		auto team_keys=event_teams_keys(f,event);
		for(auto team:take(5,select(team_keys))){
			null_stream<<team_event_matches(f,team,event).size()<<"\n";
			q.push(std::async(
				[&f,team,event](){ team_event_matches_simple(f,team,event); return 0; }
			));
			q.push(std::async(
				[&f,team,event](){ team_event_matches_keys(f,team,event); return 1; }
			));
			q.push(std::async(
				[&f,team,event](){ team_event_awards(f,team,event); return 2; }
			));
			q.push(std::async(
				[&f,team,event](){ team_event_status(f,team,event); return 3; }
			));

			while(q.size()>200){
				q.front().get();
				q.pop();
			}
		}
	}

	for(auto year:years){
		for(auto page:range(20)){
			//std::cout<<"year:"<<year<<" page:"<<page<<"\n";
			null_stream<<teams_year(f,year,page)<<"\n";
			null_stream<<teams_year_simple(f,year,page)<<"\n";
			null_stream<<teams_year_keys(f,year,page)<<"\n";
		}
	}

	for(auto team:take(5,select(team_keys1))){
		add_to_queue([&f,team](){ team_awards(f,team); return 20; });
		for(auto year:years){
			add_to_queue([&f,team,year](){ team_awards_year(f,team,year); return 21; });
			add_to_queue([&f,team,year](){ team_matches_year(f,team,year); return 22; });
			add_to_queue([&f,team,year](){ team_matches_year_simple(f,team,year); return 23; });
			add_to_queue([&f,team,year](){ team_matches_year_keys(f,team,year); return 24; });
			add_to_queue([&f,team,year](){ team_media_year(f,team,year); return 25; });

			add_to_queue([&f,team,year](){ team_events_year(f,team,year); return 26; });
			add_to_queue([&f,team,year](){ team_events_year_simple(f,team,year); return 27; });
			add_to_queue([&f,team,year](){ team_events_year_keys(f,team,year); return 28; });
		}
		add_to_queue([&f,team](){ team_social_media(f,team); return 29; });
	}

	while(q.size()){
		q.front().get();
		q.pop();
	}

	return 0;
}

std::ostream& operator<<(std::ostream& o,std::invalid_argument const& a){
	return o<<"invalid_argument("<<a.what()<<")";
}

int main(int argc,char **argv){
	try{
		return tba::main1(argc,argv);
	}catch(std::string const& s){
		std::cout<<s<<"\n";
		return 1;
	}catch(const char *s){
		assert(s);
		std::cout<<s<<"\n";
		return 1;
	}catch(std::invalid_argument const& e){
		std::cout<<e<<"\n";
		return 1;
	}
	catch(tba::Decode_error const& e){
		std::cout<<e<<"\n";
		return 1;
	}
}

}

int main(int argc,char **argv){
	return tba::main(argc,argv);
}
