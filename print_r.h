#ifndef TBA_PRINT_R_H
#define TBA_PRINT_R_H

#include "util.h"

namespace tba{
	
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
	std::cout<<"NULL\n";
}

template<typename A,typename B>
void print_r(int indent,std::pair<A,B> const& p){
	do_indent(indent);
	std::cout<<"pair\n";
	indent++;
	print_r(indent,p.first);
	print_r(indent,p.second);
}

template<typename K,typename V>
void print_r(int indent,std::map<K,V> const& m){
	do_indent(indent);
	std::cout<<"map\n";
	indent++;
	for(auto p:m){
		print_r(indent,p);
	}
}

template<typename T>
void print_r(int indent,std::vector<T> const& a){
	do_indent(indent);
	std::cout<<"vector\n";
	indent++;
	for(auto x:a){
		print_r(indent,x);
	}
}

//void print_r(int,int)TBA_NYI

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
PRINT_R(Match,TBA_MATCH)
PRINT_R(Match_Score_Breakdown_2015_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2015_ALLIANCE)
PRINT_R(Match_Score_Breakdown_2015,TBA_MATCH_SCORE_BREAKDOWN_2015)
PRINT_R(Match_Score_Breakdown_2016_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2016_ALLIANCE)
PRINT_R(Match_Score_Breakdown_2016,TBA_MATCH_SCORE_BREAKDOWN_2016)
PRINT_R(Match_Score_Breakdown_2022_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2022_ALLIANCE)
PRINT_R(Match_Score_Breakdown_2022,TBA_MATCH_SCORE_BREAKDOWN_2022)

template<typename...Ts>
void print_r(int indent,std::variant<Ts...> const& a){
	return std::visit([&](auto const& x){ return print_r(indent,x); },a);
}

template<typename T>
void print_r(T t){
	print_r(0,t);
}

}

#endif
