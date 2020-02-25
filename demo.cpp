#include "tba.h"
#include<iostream>
#include<algorithm>
#include<future>
#include<queue>
#include<variant>
#include<fstream>
#include<optional>
#include "data.h"
#include "rapidjson/document.h"
#include "curl.h"
#include "db.h"
#include "util.h"
#include "rapidjson.h"

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
	nyi
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

template<typename T>
void print_r(T t){
	print_r(0,t);
}

int main1(int argc,char **argv){
	std::string tba_key;

	auto a=args(argc,argv);
	bool quick=0;
	if(a.size() && a[0]=="--short"){
		quick=1;
		a=tail(a);
	}

	std::optional<Event_key> opr_event;
	if(a.size() && a[0]=="--opr"){
		a=tail(a);
		assert(a.size());
		opr_event=Event_key{a[0]};
		a=tail(a);
	}

	if(a.size()){
		tba_key=a[1];
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
	
	Cached_fetcher f{Fetcher{Nonempty_string{tba_key}},Cache{}};

	if(opr_event){
		auto d=event_oprs(f,*opr_event);
		//std::cout<<d<<"\n";//TBA_NYI
		print_r(d);
		return 0;
	}

	//auto years=range(Year{1992},Year{2020});//could get this via the API.
	auto years=range(Year{2020},Year{2021});//could get this via the API.

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
		null_stream<<event_district_points(f,event_key)<<"\n";

		null_stream<<event_matches(f,event_key)<<"\n";
		null_stream<<event_matches_simple(f,event_key)<<"\n";

		match_keys|=event_matches_keys(f,event_key);

		null_stream<<event_awards(f,event_key)<<"\n";
	}

	for(auto match_key:select(reversed(match_keys))){
		null_stream<<match(f,match_key)<<"\n";
		null_stream<<match_simple(f,match_key)<<"\n";
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
	}catch(std::invalid_argument const& e){
		std::cout<<e<<"\n";
		return 1;
	}catch(tba::Decode_error const& e){
		std::cout<<e<<"\n";
		return 1;
	}
}

}

int main(int argc,char **argv){
	return tba::main(argc,argv);
}
