#include "match.h"
#include "util.h"

namespace tba{

template<typename T>
std::string type_name(T* x){
	return typeid(x).name();
}

#define MAKE_INST TBA_MAKE_IMPL

#define STR_OPT_INST(A) A,
#define STR_OPT_F2(A) if(a==NAME::A) return o<<""#A;
#define STR_OPT_DEC(A) if(s==""#A) return NAME::A;
#define STR(A) ""#A

#define DECODE2(A,B) [&](){ \
	if(!in.is_object()){\
		std::ostringstream ss; \
		ss<<"Expected obj, got:"<<in;\
		throw Decode_error{""#B,as_string(in),"expected object"}; \
	}\
	try{\
		try{\
			return decode(in[""#B],(A*)nullptr); \
		}catch(simdjson::simdjson_error const&){\
			return decode(nullptr,(A*)nullptr); \
		}\
	}catch(Decode_error e){\
		try{\
		}catch(...){}\
		e.path.push_back(""#B);\
		throw e;\
	}\
}(),

#define DECODE_FAIL TBA_DECODE_FAIL
//DECODE_FAIL(High_score)
DECODE_FAIL(Endgame)
DECODE_FAIL(Init_line)
DECODE_FAIL(Target_color)
DECODE_FAIL(Rung_level)

Match_Score_Breakdown decode(JSON_value in,std::optional<Year>& year,Match_Score_Breakdown const*){
	assert(year);

	switch(year->get()){
		//case 2014: return decode(in,(Match_Score_Breakdown_2014*)0);
		#define X(YEAR) case YEAR: return decode(in,(Match_Score_Breakdown_##YEAR*)0);
		X(2014)
	   	X(2015)
		X(2016)
		X(2017)
		//X(2018)
		//X(2019)
		X(2020)
		//X(2021)
		X(2022)
		X(2023)
		X(2024)
		X(2025)
		X(2026)
		#undef X
		case 2018:
		case 2019:
		case 2021:
			return Ignore();
		default:
			TBA_PRINT(year);
			TBA_NYI
	}
}

Match_key decode(JSON_value,std::optional<Year> &,Match_key const*);

template<typename T>
std::optional<T> decode(JSON_value a,std::optional<Year> &year,std::optional<T> const*);

template<typename T>
T decode(JSON_value a,std::optional<Year> &,T const* x){
	return decode(a,x);
}

template<typename T>
std::optional<T> decode(JSON_value a,std::optional<Year> &year,std::optional<T> const*){
	if(a.is_null()){
		return std::nullopt;
	}
	try{
		return decode(a,year,(T*)0);
	}catch(Decode_error e){
		e.path|=std::string("t-year");
		throw e;
	}
}

Match_key decode(JSON_value a,std::optional<Year> &year,Match_key const* x){
	auto r=decode(a,x);
	assert(!year);
	year=r.year();
	return r;
}


#define DECODE_Y(A,B)\
	try{\
		if(k==""#B) VAR_##B=decode(p.value,year,(A*)nullptr);\
	}catch(Decode_error e){\
		e.path.push_back(""#B);\
		throw e;\
	}\

Match decode(JSON_object in,Match const*){
	std::optional<Year> year;

	TBA_MATCH(TBA_DECODE_B1)

	for(auto p:in){
		std::string_view k=p.key;
		try{
			TBA_MATCH(DECODE_Y)
		}catch(Decode_error e){
			e.path.push_back("Match");
			throw e;
		}
	}
	return Match{TBA_MATCH(TBA_DECODE_B3)};
}

Match decode(JSON_value in,Match const* x){
	if(in.type()!=simdjson::dom::element_type::OBJECT){
		throw Decode_error("Match",as_string(in),"expected obj");
	}
	return decode(in.get_object(),x);
}

Match decode(JSON_array,Match const*)TBA_NYI
Match decode(std::nullptr_t,Match const*)TBA_NYI
Match rand(Match const*)TBA_NYI

TBA_INST_PRINT(Match,TBA_MATCH)

Match_Score_Breakdown decode(JSON_value,std::optional<Year>&,Match_Score_Breakdown const*);

MAKE_INST(Match_Score_Breakdown_2015_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2015_ALLIANCE)

std::ostream& operator<<(std::ostream& o,Coopertition a){
	#define X(A) if(a==Coopertition::A) return o<<""#A;
	TBA_COOPERTITION_TYPES(X)
	#undef X
	assert(0);
}

Coopertition rand(Coopertition const*){
	TBA_NYI
}

Coopertition decode(JSON_value in,const Coopertition*){
	if(in.type()!=simdjson::dom::element_type::STRING){
		throw Decode_error("Coopertiton",as_string(in),"expected string");
	}
	std::string_view s=in.get_string();
	#define X(A) if(s==""#A) return Coopertition::A;
	TBA_COOPERTITION_TYPES(X)
	#undef X
	throw Decode_error("Coopertition",s,"unexpected string");
}

std::optional<Coopertition> maybe_decode(JSON_value in,Coopertition const*){
	if(in.type()!=simdjson::dom::element_type::STRING){
		return std::nullopt;
	}
	std::string_view s=in.get_string();
	#define X(A) if(s==""#A) return Coopertition::A;
	TBA_COOPERTITION_TYPES(X)
	#undef X
	return std::nullopt;
}

MAKE_INST(Match_Score_Breakdown_2015,TBA_MATCH_SCORE_BREAKDOWN_2015)

#define NAME Defense
//STR_OPTIONS(TBA_DEFENSE)
NAME decode(JSON_value in,NAME const*){
	if(in.type()!=simdjson::dom::element_type::STRING){
		throw Decode_error("Defense",as_string(in),"wrong type");
	}
	std::string_view s=in.get_string();
	TBA_DEFENSE(STR_OPT_DEC)
	if(s==""){
		return Defense::NotSpecified;
	}
	throw Decode_error("Defense",s,"unrecognized");
}

std::optional<NAME> maybe_decode(JSON_value in,NAME const*){
	if(in.type()!=simdjson::dom::element_type::STRING){
		return std::nullopt;
	}
	std::string_view s=in.get_string();
	TBA_DEFENSE(STR_OPT_DEC)
	if(s==""){
		return Defense::NotSpecified;
	}
	return std::nullopt;
}

NAME maybe_decode(std::nullptr_t,NAME const*){
	return Defense::NotSpecified;
}

std::ostream& operator<<(std::ostream& o,Defense a){
	TBA_DEFENSE(STR_OPT_F2)
	assert(0);
}

NAME rand(NAME const*){
	TBA_NYI
}
#undef NAME

#define STR_OPTIONS(OPTIONS)\
	std::ostream& operator<<(std::ostream& o,NAME a){\
		OPTIONS(STR_OPT_F2)\
		assert(0); \
	}\
	NAME decode(JSON_value in,NAME const* x){\
		if(in.type()!=simdjson::dom::element_type::STRING){\
			throw Decode_error(type_name(x),as_string(in),"expected string");\
		}\
		std::string_view s=in.get_string();\
		OPTIONS(STR_OPT_DEC)\
		throw Decode_error{type_name(x),as_string(s),std::string("unrecognized str")};\
	}\
	std::optional<NAME> maybe_decode(JSON_value in,NAME const*){\
		if(in.type()!=simdjson::dom::element_type::STRING){\
			return std::nullopt;\
		}\
		std::string_view s=in.get_string();\
		OPTIONS(STR_OPT_DEC)\
		return std::nullopt;\
	}\
	TBA_NO_NULL(NAME)\
	TBA_ENUM_RAND(NAME,OPTIONS)\

#define AUTO_2017(X) X(Unknown) X(Mobility) X(None)
#define NAME Auto_2017
STR_OPTIONS(AUTO_2017)
#undef NAME

#define NAME Endgame_2022
STR_OPTIONS(TBA_ENDGAME_2022_OPTIONS)
#undef NAME

#define NAME Auto_2016
STR_OPTIONS(TBA_AUTO_2016_TYPES)
#undef NAME

#define NAME Endgame_2025
STR_OPTIONS(TBA_ENDGAME_2025)
#undef NAME

#define NAME Endgame_2024
STR_OPTIONS(TBA_ENDGAME_2024)
#undef NAME

#define NAME Bridge_state
STR_OPTIONS(TBA_BRIDGE_STATE)
#undef NAME

#define NAME Auto_charge_station
STR_OPTIONS(TBA_AUTO_CHARGE_STATION)
#undef NAME

#define NAME End_charge_station
STR_OPTIONS(TBA_END_CHARGE_STATION)
#undef NAME

#define NAME Tower
STR_OPTIONS(TBA_TOWER)
#undef NAME

#define NAME Touchpad
STR_OPTIONS(TBA_TOUCHPAD)
#undef NAME

#define NAME TowerRobot_2026
STR_OPTIONS(TBA_TOWERROBOT_2026)
#undef NAME


#define YES_NO_OPTIONS(X) X(Yes) X(No)
#define NAME Yes_no
STR_OPTIONS(YES_NO_OPTIONS)
#undef NAME

Ignore decode(JSON_value,Ignore const*){
	return Ignore();
}

Ignore decode(JSON_object,Ignore const*){
	return Ignore();
}

Ignore decode(std::nullptr_t,Ignore const*){
	return Ignore();
}

Ignore rand(Ignore const*){
	return Ignore();
}

std::optional<Ignore> maybe_decode(std::nullptr_t,Ignore const*){
	return Ignore();
}

std::optional<Ignore> maybe_decode(JSON_value,Ignore const*){
	return Ignore();
}

std::ostream& operator<<(std::ostream& o,Ignore const&){
	return o<<"Ignore";
}

Match_Score_Breakdown_2014_Alliance decode(JSON_value in,const Match_Score_Breakdown_2014_Alliance*){
	if(!in.is_object()){
		throw Decode_error{
			"Match_Score_Breakdown_2014_Alliance",
			as_string(in),
			"Expected object"
		};
	}
	return Match_Score_Breakdown_2014_Alliance{
		#define X(A,B,C) DECODE2(A,C)
		TBA_MATCH_SCORE_BREAKDOWN_2014_ALLIANCE(X)
		#undef X
	};
}

Match_Score_Breakdown_2014_Alliance rand(Match_Score_Breakdown_2014_Alliance const*){
	TBA_NYI
}

std::optional<Match_Score_Breakdown_2014_Alliance> maybe_decode(
	std::nullptr_t,Match_Score_Breakdown_2014_Alliance const*
){
	return std::nullopt;
}

std::optional<Match_Score_Breakdown_2014_Alliance> maybe_decode(
	JSON_value in,Match_Score_Breakdown_2014_Alliance const*
){
	if(!in.is_object()){
		return std::nullopt;
	}
	#define X(A,B,C) std::optional<A> VAR_##B;
	TBA_MATCH_SCORE_BREAKDOWN_2014_ALLIANCE(X)
	#undef X
	for(auto [k,v]:in.get_object()){
		bool any=0;

		#define X(A,B,C) if(k==""#C){\
			VAR_##B=maybe_decode(v,(A*)nullptr);\
			if(!VAR_##B) return std::nullopt;\
			any=1;\
		}
		TBA_MATCH_SCORE_BREAKDOWN_2014_ALLIANCE(X)
		#undef X

		/*if(!any){
			std::cout<<"Did not find: "<<k<<"\n";
			std::set<std::string> keys;
			for(auto [k,v]:in.get_object()){
				keys.insert(std::string(k));
			}
			if(keys.count("autoBoulderPoints")){
				//2016; ignore
			}else if(keys.count("container_count_level6")){
				//2015; ignore
			}else{
				std::cout<<keys<<"\n";
			}
			return std::nullopt;
		}*/
		(void)any;
	}

	#define X(A,B,C) if(!VAR_##B){\
		VAR_##B=maybe_decode(nullptr,(A*)nullptr);\
		if(!VAR_##B){\
			return std::nullopt;\
		}\
	}
	TBA_MATCH_SCORE_BREAKDOWN_2014_ALLIANCE(X)
	#undef X

	return Match_Score_Breakdown_2014_Alliance{
		#define X(A,B,C) *VAR_##B,
		TBA_MATCH_SCORE_BREAKDOWN_2014_ALLIANCE(X)
		#undef X
	};
}

std::ostream& operator<<(std::ostream& o,Match_Score_Breakdown_2014_Alliance const& a){
	o<<"Match_score_breakdown_2014_alliance(";
	#define X(A,B,C) TBA_PRINT_ITEM(A,B)
	TBA_MATCH_SCORE_BREAKDOWN_2014_ALLIANCE(X)
	#undef X
	return o<<")";
}

MAKE_INST(Match_Score_Breakdown_2014,TBA_MATCH_SCORE_BREAKDOWN_2014)

std::ostream& operator<<(std::ostream& o,Init_line a){
	#define X(A) if(a==Init_line::A) return o<<""#A;
	TBA_INIT_LINE_OPTIONS(X)
	#undef X
	assert(0);
}

TBA_ENUM_RAND(Init_line,TBA_INIT_LINE_OPTIONS)

Init_line decode(JSON_value in,Init_line const*){
	auto s=decode(in,(std::string*)nullptr);
	#define X(A) if(s==""#A) return Init_line::A;
	TBA_INIT_LINE_OPTIONS(X)
	#undef X
	throw std::invalid_argument{s};
}

std::ostream& operator<<(std::ostream& o,Endgame a){
	#define X(A) if(a==Endgame::A) return o<<""#A;
	TBA_ENDGAME_OPTIONS(X)
	#undef X
	assert(0); 
}

Endgame decode(JSON_value in,Endgame const*){
	auto s=decode(in,(std::string*)nullptr);
	#define X(A) if(s==""#A) return Endgame::A;
	TBA_ENDGAME_OPTIONS(X)
	#undef X
	throw Decode_error("Endgame",as_string(in),"unexpected string");
}

Endgame rand(Endgame const*)TBA_NYI

std::ostream& operator<<(std::ostream& o,Target_color a){
	#define X(A) if(a==Target_color::A) return o<<""#A;
	TBA_TARGET_COLOR_OPTIONS(X)
	#undef X
	assert(0);
}

Target_color decode(JSON_value in,Target_color const*){
	auto s=decode(in,(std::string*)nullptr);
	#define X(A) if(s==""#A) return Target_color::A;
	TBA_TARGET_COLOR_OPTIONS(X)
	#undef X
	TBA_PRINT(s);
	TBA_NYI
}

Target_color rand(Target_color const*){
	TBA_NYI
}

std::ostream& operator<<(std::ostream& o,Rung_level a){
	#define X(A) if(a==Rung_level::A) return o<<""#A;
	TBA_RUNG_LEVEL_OPTIONS(X)
	#undef X
	assert(0);
}

Rung_level decode(JSON_value in,Rung_level const*){
	auto s=decode(in,(std::string*)nullptr);
	#define X(A) if(s==""#A) return Rung_level::A;
	TBA_RUNG_LEVEL_OPTIONS(X)
	#undef X
	TBA_PRINT(s);
	TBA_NYI
}

Rung_level rand(Rung_level const*){
	TBA_NYI
}

MAKE_INST(Match_Score_Breakdown_2016_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2016_ALLIANCE)

MAKE_INST(Match_Score_Breakdown_2016,TBA_MATCH_SCORE_BREAKDOWN_2016)

MAKE_INST(Match_Score_Breakdown_2017_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2017_ALLIANCE)

MAKE_INST(Match_Score_Breakdown_2017,TBA_MATCH_SCORE_BREAKDOWN_2017)

MAKE_INST(Match_Score_Breakdown_2020_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2020_ALLIANCE)

MAKE_INST(Match_Score_Breakdown_2020,TBA_MATCH_SCORE_BREAKDOWN_2020)

MAKE_INST(Match_Score_Breakdown_2022_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2022_ALLIANCE)

MAKE_INST(Match_Score_Breakdown_2022,TBA_MATCH_SCORE_BREAKDOWN_2022)

MAKE_INST(Match_Score_Breakdown_2023_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2023_ALLIANCE)

MAKE_INST(Match_Score_Breakdown_2023,TBA_MATCH_SCORE_BREAKDOWN_2023)

MAKE_INST(Match_Score_Breakdown_2024_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2024_ALLIANCE)

MAKE_INST(Match_Score_Breakdown_2024,TBA_MATCH_SCORE_BREAKDOWN_2024)

MAKE_INST(Match_Score_Breakdown_2025_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2025_ALLIANCE)

MAKE_INST(Match_Score_Breakdown_2025,TBA_MATCH_SCORE_BREAKDOWN_2025)

MAKE_INST(Match_Score_Breakdown_2026_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2026_ALLIANCE)

MAKE_INST(Match_Score_Breakdown_2026,TBA_MATCH_SCORE_BREAKDOWN_2026)

}
