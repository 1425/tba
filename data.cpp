#include "data.h"
#include<set>
#include<typeinfo>
#include "util.h"
#include "simdjson.h"

namespace tba{

/*template<size_t LEN>
std::array<char,LEN> take(std::string const& s){
	std::array<char,LEN> r;
	std::copy_n(s.begin(),LEN,std::begin(r));
	return r;
}*/

template<typename T>
std::ostream& operator<<(std::ostream& o,std::set<T> const& a){
	o<<"{";
	for(auto const& x:a){
		o<<x<<" ";
	}
	return o<<"}";
}

#define DECODE_FAIL TBA_DECODE_FAIL
//obviously, this is the slow way to do this, but should be sufficient to see that the other pieces are working.
DECODE_FAIL(Webcast_type)
DECODE_FAIL(Event_key)
DECODE_FAIL(Media_type)
DECODE_FAIL(unsigned)
DECODE_FAIL(Pick_order)
DECODE_FAIL(double)
//DECODE_FAIL(Yes_no)
DECODE_FAIL(Event_type)
DECODE_FAIL(Playoff_status)
//DECODE_FAIL(Endgame_2022)
DECODE_FAIL(Award_type)
DECODE_FAIL(Match_key)
//DECODE_FAIL(Auto_2016)
DECODE_FAIL(Winning_alliance)
DECODE_FAIL(Playoff_level)
DECODE_FAIL(Alliance_color)
DECODE_FAIL(M_score)
//DECODE_FAIL(Match_Score_Breakdown_2014_Alliance)
DECODE_FAIL(District_key)
DECODE_FAIL(Year)
DECODE_FAIL(Team_key)

TBA_NO_NULL(std::string)

template<typename K,typename V>
TBA_NO_NULL(std::map<TBA_SINGLE_ARG(K,V)>)

//NO_NULL(IID)
//NO_NULL(ISS)
//NO_NULL(D8)
//NO_NULL(D6)

/*template<typename T>
std::optional<T> maybe_decode(std::nullptr_t a,T const* x){
	try{
		return decode(a,x);
	}catch(...){
		return std::nullopt;
	}
}*/

std::strong_ordering operator<=>(std::optional<std::nullptr_t> const& a,std::optional<std::nullptr_t> const& b){
	if(a){
		if(b){
			return std::strong_ordering::equal;
		}
		return std::strong_ordering::greater;
	}
	if(b){
		return std::strong_ordering::less;
	}
	return std::strong_ordering::equal;
}

#define INST(A,B) A B;

/*
 * How to do a faster decode (?)
 * 1) make a list of all the elements and whether or not they can be null
 * 2) sort them alphabetically
 * 3) iterate over the items, which appear to always be in alphabetical order
 * although the parser says it shows them in whatever order they appear in the input
 * and so that seems to just be an artifact of upstream
 * */

#define DECODE(A,B) [&](){ \
	if(!in.IsObject()){\
		std::ostringstream ss; \
		ss<<"Expected obj, got:"<<in;\
		throw Decode_error{""#B,in,"expected object"}; \
	}\
	try{\
		if(!in.HasMember(""#B)){\
			return decode(nullptr,(A*)nullptr); \
		}\
		return decode(in[""#B],(A*)nullptr); \
	}catch(Decode_error e){\
		e.path.push_back(""#B);\
		throw e;\
	}\
}(),

#define MAKE_INST TBA_MAKE_IMPL

MAKE_INST(API_Status_App_Version,TBA_API_STATUS_APP_VERSION)

MAKE_INST(API_Status,TBA_API_STATUS)
MAKE_INST(District_Ranking,TBA_DISTRICT_RANKING)

MAKE_INST(Team,TBA_TEAM)

MAKE_INST(Team_Robot,TBA_TEAM_ROBOT)

MAKE_INST(Team_Simple,TBA_TEAM_SIMPLE)

MAKE_INST(District_List,TBA_DISTRICT_LIST)

std::ostream& operator<<(std::ostream& o,Webcast_type a){
	#define X(A) if(a==Webcast_type::A) return o<<""#A;
	TBA_WEBCAST_TYPES(X)
	#undef X
	assert(0);
}

TBA_ENUM_RAND(Webcast_type,TBA_WEBCAST_TYPES)

Webcast_type decode(JSON_value in,const Webcast_type*){
	auto s=decode(in,(std::string*)nullptr);
	#define X(A) if(s==""#A) return Webcast_type::A;
	TBA_WEBCAST_TYPES(X)
	#undef X
	throw std::invalid_argument{"Webcast_type:"+s};
}

MAKE_INST(Webcast,TBA_WEBCAST)

std::ostream& operator<<(std::ostream& o,Event_type a){
	switch(a){
		#define X(A,B) case Event_type::A: return o<<""#A;
		TBA_EVENT_TYPES(X)
		#undef X
		default:
			assert(0);
	}
}

//TBA_ENUM_RAND(Event_type,TBA_EVENT_TYPES)

auto options(Event_type const*){
	return std::array{
		#define X(A,B) Event_type::A,
		TBA_EVENT_TYPES(X)
		#undef X
	};
}

Event_type rand(Event_type const* x){
	return choose(options(x));
}

Event_type decode(JSON_value in,const Event_type *){
	auto i=decode(in,(int*)nullptr);
	#define X(A,B) if(i==B) return Event_type::A;
	TBA_EVENT_TYPES(X)
	#undef X
	std::ostringstream ss;
	ss<<"Event_type:"<<i;
	throw std::invalid_argument{ss.str()};
}

std::ostream& operator<<(std::ostream& o,Playoff_type a){
	#define X(A,B,C) if(a==Playoff_type::B) return o<<C;
	TBA_PLAYOFF_TYPES(X)
	#undef X
	assert(0);
}

Playoff_type decode(JSON_value in,const Playoff_type*){
	auto i=decode(in,(int*)0);
	#define X(A,B,C) if(i==A) return Playoff_type::B;
	TBA_PLAYOFF_TYPES(X)
	#undef X
	std::stringstream ss;
	ss<<"Playoff_type"<<i;
	throw std::invalid_argument(ss.str());
}

std::optional<Playoff_type> maybe_decode(JSON_value in,Playoff_type const*){
	auto i1=maybe_decode(in,(int*)nullptr);
	if(!i1) return std::nullopt;
	auto i=*i1;
	#define X(A,B,C) if(i==A) return Playoff_type::B;
	TBA_PLAYOFF_TYPES(X)
	#undef X
	return std::nullopt;
}

auto options(Playoff_type const*){
	return std::array{
		#define X(A,B,C) Playoff_type::B,
		TBA_PLAYOFF_TYPES(X)
		#undef X
	};
}

Playoff_type rand(Playoff_type const* x){
	return choose(options(x));
}

MAKE_INST(Event,TBA_EVENT)

Date decode(std::string const& s,Date const*){
	std::chrono::year_month_day ymd{};
	std::istringstream ss(s);
    
	ss >> std::chrono::parse("%Y-%m-%d", ymd);

	if (ss.fail()) {
		throw Decode_error("Date",s,"Invalid date");
	}

	return ymd;
}

Date decode(JSON_value in,Date const* x){
	auto s=decode(in,(std::string*)nullptr);
	return decode(s,x);
}

std::optional<Date> maybe_decode(JSON_value in,Date const*){
	auto s=maybe_decode(in,(std::string*)nullptr);
	if(!s) return std::nullopt;

	std::chrono::year_month_day ymd{};
	std::istringstream ss(*s);
    
	ss >> std::chrono::parse("%Y-%m-%d", ymd);

	if (ss.fail()) {
		//throw Decode_error("Date",s,"Invalid date");
		return std::nullopt;
	}

	return ymd;
}

/*Date rand(Date const*){
	TBA_NYI
}*/

std::chrono::year rand(std::chrono::year const*){
	return std::chrono::year(std::rand()%3000);
}

std::chrono::month rand(std::chrono::month const*){
	return std::chrono::month(1+std::rand()%12);
}

std::chrono::day rand(std::chrono::day const*){
	//give a day that is always valid for all months
	return std::chrono::day(1+std::rand()%28);
}

std::chrono::year_month_day rand(std::chrono::year_month_day const*){
	std::chrono::year_month_day r{
		rand((std::chrono::year*)0),
		rand((std::chrono::month*)0),
		rand((std::chrono::day*)0)
	};
	return r;
}

MAKE_INST(Event_Simple,TBA_EVENT_SIMPLE)

std::ostream& operator<<(std::ostream& o,Media_type a){
	#define X(A,B) if(a==Media_type::A) return o<<""#B;
	TBA_MEDIA_TYPES(X)
	#undef X
	assert(0);
}

//TBA_ENUM_RAND(Media_type,TBA_MEDIA_TYPES)
Media_type rand(Media_type const*){
	TBA_NYI
}

Media_type decode(JSON_value in,const Media_type*){
	if(in.type()!=simdjson::dom::element_type::STRING){
		throw Decode_error{"Media_type",as_string(in),"expected string"};
	}
	std::string_view s=in.get_string();
	#define X(A,B) if(s==""#B) return Media_type::A;
	TBA_MEDIA_TYPES(X)
	#undef X
	throw Decode_error{"Media_type",as_string(in),"unrecognized option"};
}

MAKE_INST(Media_details,TBA_MEDIA_DETAILS)
MAKE_INST(Media,TBA_MEDIA)


M_score::M_score(int i1):i(i1){
	if(i1<-1){
		std::ostringstream ss;
		ss<<"M_score:"<<i1;
		throw std::invalid_argument{ss.str()};
	}
}

bool M_score::valid()const{ return i!=-1; }

int M_score::value()const{
	assert(valid());
	return i;
}

std::ostream& operator<<(std::ostream& o,M_score const& a){
	if(!a.valid()) return o<<"NULL";
	return o<<a.value();
}

M_score rand(M_score const*){
	TBA_NYI
}

M_score decode(JSON_value in,const M_score*){
	if(in.is_null()){
		return M_score(-1);
	}
	return M_score(decode(in,(int*)nullptr));
}

MAKE_INST(Match_Alliance,TBA_MATCH_ALLIANCE)

MAKE_INST(Alliances,TBA_ALLIANCES)

std::ostream& operator<<(std::ostream& o,Winning_alliance a){
	switch(a){
		case Winning_alliance::red: return o<<"red";
		case Winning_alliance::blue: return o<<"blue";
		case Winning_alliance::NONE: return o<<"NONE";
		default: assert(0);
	}
}

Winning_alliance decode(JSON_value in,const Winning_alliance *){
	if(in.type()!=simdjson::dom::element_type::STRING){
		throw Decode_error{"Winning_alliance",as_string(in.type()),"expected string"};
	}
	std::string_view s=in.get_string();
	if(s=="red") return Winning_alliance::red;
	if(s=="blue") return Winning_alliance::blue;
	if(s=="") return Winning_alliance::NONE;
	throw Decode_error{"Winning_alliance",s,"unrecognized option"};
}

Winning_alliance rand(Winning_alliance const*){
	TBA_NYI
}

#define PLAYOFF_LEVELS(X)\
	X(qm) X(ef) X(qf) X(sf) X(f)

std::ostream& operator<<(std::ostream& o,Playoff_level a){
	#define X(A) if(a==Playoff_level::A) return o<<""#A;
	PLAYOFF_LEVELS(X)
	#undef X
	assert(0);
}

TBA_ENUM_RAND(Playoff_level,PLAYOFF_LEVELS)

Playoff_level decode(JSON_value in,const Playoff_level*){
	if(in.type()!=simdjson::dom::element_type::STRING){
		throw Decode_error{"Playoff_level",as_string(in.type()),"expected string"};
	}
	std::string_view s=in.get_string();
	#define X(A) if(s==""#A) return Playoff_level::A;
	PLAYOFF_LEVELS(X)
	#undef X
	throw Decode_error{"Playoff_level",s,"unrecognized option"};
}

MAKE_INST(Match_Simple,TBA_MATCH_SIMPLE)

MAKE_INST(Award_Recipient,TBA_RECIPIENT)

std::ostream& operator<<(std::ostream& o,Award_type a){
	#define X(A,B) if(a==Award_type::A) return o<<""#A;
	TBA_AWARD_TYPES(X)
	#undef X
	assert(0);
}

//TBA_ENUM_RAND(Award_type,TBA_AWARD_TYPES)

auto options(Award_type const*){
	return std::array{
		#define X(A,B) Award_type::A,
		TBA_AWARD_TYPES(X)
		#undef X
	};
}

Award_type rand(Award_type const* x){
	return choose(options(x));
	TBA_NYI
}

Award_type decode(JSON_value in,const Award_type *){
	auto i=decode(in,(int*)nullptr);
	#define X(A,B) if(i==B) return Award_type::A;
	TBA_AWARD_TYPES(X)
	#undef X
	std::ostringstream ss;
	ss<<"Award_type:"<<i;
	throw std::invalid_argument(ss.str());
}

MAKE_INST(Award,TBA_AWARD)

MAKE_INST(Record,TBA_RECORD)

MAKE_INST(Ranking,TBA_RANKING)

MAKE_INST(Sort_order,TBA_SORT_ORDER)

MAKE_INST(Team_Event_Status_rank,TBA_TEAM_EVENT_STATUS_RANK)

MAKE_INST(Team_Event_Status_alliance_backup,TBA_TEAM_EVENT_STATUS_ALLIANCE_BACKUP)

Pick_order::Pick_order(int i1):i(i1){
	//note that doc says 0-2, but actually returns 3 sometimes, which makes sense given the recent championship formats.
	//-1 can also be returned; seems to indicate being pulled in as a backup.
	if(i1<-1 || i>3){
		std::ostringstream ss;
		ss<<"Pick_order:"<<i;
		throw std::invalid_argument(ss.str());
	}
}

int Pick_order::get()const{ return i; }

Pick_order rand(Pick_order const*){
	TBA_NYI
}

std::ostream& operator<<(std::ostream& o,Pick_order a){
	return o<<a.get();
}

Pick_order decode(JSON_value in,const Pick_order *){
	return Pick_order{decode(in,(int*)nullptr)};
}

MAKE_INST(Team_Event_Status_alliance,TBA_TEAM_EVENT_STATUS_ALLIANCE)

std::ostream& operator<<(std::ostream& o,Playoff_status a){
	#define X(A) if(a==Playoff_status::A) return o<<""#A;
	TBA_PLAYOFF_STATUS(X)
	#undef X
	assert(0);
}

Playoff_status decode(JSON_value in,const Playoff_status*){
	auto s=decode(in,(std::string*)nullptr);
	#define X(A) if(s==""#A) return Playoff_status::A;
	TBA_PLAYOFF_STATUS(X)
	#undef X
	throw std::invalid_argument{"Playoff_status:"+s};
}

Playoff_status rand(Playoff_status const*){
	TBA_NYI
}

MAKE_INST(Team_Event_Status_playoff,TBA_TEAM_EVENT_STATUS_PLAYOFF)

MAKE_INST(Team_Event_Status,TBA_TEAM_STATUS)

MAKE_INST(Event_ranking,TBA_EVENT_RANKING)

MAKE_INST(Points,TBA_POINTS)

MAKE_INST(Tiebreaker,TBA_TIEBREAKER)

MAKE_INST(Event_District_Points,TBA_EVENT_DISTRICT_POINTS)

MAKE_INST(Event_OPRs,TBA_EVENT_OPRS)

//#define EVENT_PREDICTTIONS(X)
//	X(
//seems to not be gaurnteed to do anything.


MAKE_INST(Elimination_Alliance_status,TBA_ELIMINATION_ALLIANCE_STATUS)

MAKE_INST(Elimination_Alliance,TBA_ELIMINATION_ALLIANCE)


MAKE_INST(Year_info,TBA_YEAR_INFO)
MAKE_INST(Event_points,TBA_EVENT_POINTS)

#define TAKE2(A,B,C) X(A,B)

//DECODE_B(Match_Score_Breakdown_2014_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2014_ALLIANCE(TAKE2))

//prediction stuff from here down; the docs warn that it is subject to change.

MAKE_INST(Brier_scores,TBA_BRIER_SCORES)
MAKE_INST(Match_prediction_set,TBA_MATCH_PREDICTION_SET)
MAKE_INST(Match_prediction_stats,TBA_MATCH_PREDICTION_STATS)

std::ostream& operator<<(std::ostream &o,Alliance_color a){
	if(a==Alliance_color::RED) return o<<"red";
	if(a==Alliance_color::BLUE) return o<<"blue";
	assert(0);
}

#define TBA_ALLIANCE_COLOR(X)\
	X(red) X(blue)

#define TBA_ALLIANCE_COLOR_NAME(X)\
	X(RED)\
	X(BLUE)

TBA_ENUM_RAND(Alliance_color,TBA_ALLIANCE_COLOR_NAME)

Alliance_color decode(JSON_value in,const Alliance_color*){
	auto s=decode(in,(std::string*)nullptr);
	if(s=="red") return Alliance_color::RED;
	if(s=="blue") return Alliance_color::BLUE;
	throw std::invalid_argument{"Alliance color:"+s};
}

MAKE_INST(Match_prediction,TBA_MATCH_PREDICTION)
MAKE_INST(Per_match_predictions,TBA_PER_MATCH_PREDICTIONS)
MAKE_INST(Ranking_prediction_stats,TBA_RANKING_PREDICTION_STATS)
MAKE_INST(Mean_var,TBA_MEAN_VAR)
MAKE_INST(Stat_mean_var_set,TBA_STAT_MEAN_VAR_SET)
MAKE_INST(Stat_mean_vars,TBA_STAT_MEAN_VARS)
MAKE_INST(Event_predictions,TBA_EVENT_PREDICTIONS)
MAKE_INST(Alliance_prediction,TBA_ALLIANCE_PREDICTION)
MAKE_INST(Zebra_team,TBA_ZEBRA_TEAM)
MAKE_INST(Zebra_alliances,TBA_ZEBRA_ALLIANCES)
MAKE_INST(Zebra,TBA_ZEBRA)

std::ostream& operator<<(std::ostream& o,Unknown){
	return o<<"unknown";
}

Unknown decode(JSON_value in,const Unknown*){
	auto s=decode(in,(std::string*)nullptr);
	if(s=="unknown") return Unknown{};
	std::ostringstream ss;
	ss<<"Expected \"unknown\", but got:"<<in;
	throw std::invalid_argument{ss.str()};
}

std::optional<Unknown> maybe_decode(JSON_value in,Unknown const*){
	if(in.type()!=simdjson::dom::element_type::STRING){
		return std::nullopt;
	}
	std::string_view s=in.get_string();
	if(s!="unknown"){
		return std::nullopt;
	}
	return Unknown{};
}

MAKE_INST(Dcmp_history,TBA_DCMP_HISTORY)
MAKE_INST(District_insights,TBA_DISTRICT_INSIGHTS)
MAKE_INST(Team_data,TBA_TEAM_DATA)
MAKE_INST(District_data,TBA_DISTRICT_DATA)
MAKE_INST(Year_data,TBA_YEAR_DATA)
MAKE_INST(Advancement_status,TBA_ADVANCEMENT_STATUS)

District_abbreviation::District_abbreviation(std::string a):
	s(std::move(a))
{}

std::string const& District_abbreviation::get()const{
	return s;
}

District_abbreviation::operator std::string()const{
	return s;
}

std::ostream& operator<<(std::ostream& o,District_abbreviation const& a){
	return o<<a.get();
}

std::string operator+(std::string const& a,District_abbreviation const& b){
	return a+b.get();
}

District_abbreviation decode(std::string const& s,District_abbreviation const*){
	return s;
}

District_abbreviation decode(JSON_value in,District_abbreviation const*){
	return decode(in,(std::string*)0);
}

std::optional<District_abbreviation> maybe_decode(JSON_value in,District_abbreviation const*){
	return maybe_decode(in,(std::string*)0);
}

std::optional<District_abbreviation> maybe_decode(std::nullptr_t,District_abbreviation const*){
	return std::nullopt;
}

District_abbreviation rand(District_abbreviation const*){
	std::stringstream ss;
	for(auto _:range(2+std::rand()%2)){
		ss<<char('a'+std::rand()%26);
	}
	return ss.str();
}

}
