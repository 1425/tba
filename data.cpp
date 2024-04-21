#include "data.h"
#include "util.h"
#include "rapidjson.h"

namespace tba{

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
#define PRINT_ITEM(A,B) o<<""#B<<":"<<a.B<<" ";

#define MAKE_INST(NAME,ITEMS)\
	std::ostream& operator<<(std::ostream& o,NAME const& a){\
		o<<""#NAME<<"(";\
		ITEMS(PRINT_ITEM)\
		return o<<")";\
	}\
	NAME decode(JSON const& in,const NAME*){\
		if(!in.IsObject()){\
			throw Decode_error{""#NAME,in,"expected object"};\
		}\
		try{\
			return NAME{ITEMS(DECODE)}; \
		}catch(Decode_error e){\
			e.path.push_back(""#NAME);\
			throw e;\
		}\
	}

template<typename T>
T decode(std::nullptr_t,const T *x){
	throw Decode_error(typeid(x).name(),"null","wrong type");
}

template<typename T>
std::optional<T> decode(std::nullptr_t,const std::optional<T>*){
	return {};
}

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

MAKE_INST(API_Status_App_Version,TBA_API_STATUS_APP_VERSION)

MAKE_INST(API_Status,TBA_API_STATUS)
MAKE_INST(District_Ranking,TBA_DISTRICT_RANKING)

Match_key::Match_key(std::string s1):s(std::move(s1)){
	//format: event_key / "_" / level / (maybe set # and 'm') / match #
	auto check=[&](bool b){
		if(b) return;
		throw std::invalid_argument{[&](){
			std::ostringstream ss;
			ss<<"Expected Match_key, found:"<<s;
			return ss.str();
		}()};
	};

	Year{atoi(s.c_str())};
	size_t at=4;
	while(at<s.size() && s[at]!='_') at++;

	check(s[at]=='_');
	at++;

	at+=2;//skip match type, which is 2 chars long.
	check(at<s.size());

	/*while(at<s.size()){
		check(isdigit(s[at]));
		at++;
	}*/
}

std::string const& Match_key::get()const{ return s; }

Match_key decode(JSON const& in,const Match_key*){
	return Match_key{decode(in,(std::string*)nullptr)};
}

std::ostream& operator<<(std::ostream& o,Match_key const& a){
	return o<<a.get();
}

District_key::District_key(std::string s1):s(std::move(s1)){
	Year{atoi(s.c_str())};//check that starts with a year
	//then a 2-3 letter code.
	if( !(s.size()>=6 && s.size()<=7) ){
		throw std::invalid_argument{[&](){
			std::ostringstream ss;
			ss<<"Expected District_key, found:"<<s;
			return ss.str();
		}()};
	}
}

std::string const& District_key::get()const{
	return s;
}

std::ostream& operator<<(std::ostream& o,District_key const& a){
	return o<<a.get();
}

bool operator==(District_key const& a,std::string const& b){
	return a.get()==b;
}

District_key decode(JSON const& in,const District_key *){
	return District_key{decode(in,(std::string*)nullptr)};
}

Team_key::Team_key(std::string s1):s(s1){
	auto check=[&](bool b){
		if(b) return;
		std::ostringstream ss;
		ss<<"Invalid Team_key: \""<<s<<"\"";
		throw std::invalid_argument{ss.str()};
	};
	check(s.size()>=3);
	check(s[0]=='f');
	check(s[1]=='r');
	check(s[2]=='c');

	//note: can be stuff like frc1111b
	//can also be just "frc", oddly.
}

std::string const& Team_key::str()const{ return s; }

std::ostream& operator<<(std::ostream& o,Team_key const& a){
	//return o<<"Team_key("<<a.str()<<")";
	return o<<a.str();
}

Team_key decode(JSON const& in,const Team_key*){
	return Team_key{decode(in,(std::string*)0)};
}


MAKE_INST(Team,TBA_TEAM)

Year::Year(int i1):i(i1){
	if(!valid()){
		std::ostringstream ss;
		ss<<"year:"<<i;
		throw std::invalid_argument{ss.str()};
	}
}

bool Year::valid()const{
	return i>=1992 && i<2092;
}

int Year::get()const{
	return i;
}

std::ostream& operator<<(std::ostream& o,Year a){
	return o<<a.get();
}

Year& operator++(Year& a){
	a.i++;
	if(!a.valid()){
		a.i--;
		throw std::range_error{"Year too high"};
	}
	return a;
}

Year& Year::operator--(){
	i--;
	if(!valid()){
		i++;
		throw std::range_error{"Year too low"};
	}
	return *this;
}

Year operator++(Year& a,int){
	auto r=a;
	++a;
	return r;
}

Year operator-(Year a,int b){
	return Year{a.get()-b};
}

Year decode(JSON const& in,const Year*){
	return Year{decode(in,(int*)nullptr)};
}

MAKE_INST(Team_Robot,TBA_TEAM_ROBOT)

MAKE_INST(Team_Simple,TBA_TEAM_SIMPLE)

Event_key::Event_key(std::string s1):s(std::move(s1)){
	if(s.size()<6) throw std::invalid_argument{"Event_key:"+s};
	//starts with a year then has at least 2 more chars.
	if(!s.starts_with("202121")){
		Year{atoi(s.c_str())};
	}
}

std::string const& Event_key::get()const{
	return s;
}

bool operator==(Event_key const& a,const char *s){
	if(!s) return 0;
	return a.get()==s;
}

std::ostream& operator<<(std::ostream& o,Event_key const& a){
	return o<<a.get();
}

Event_key decode(JSON const& in,const Event_key*){
	return Event_key{decode(in,(std::string*)nullptr)};
}

MAKE_INST(District_List,TBA_DISTRICT_LIST)

std::ostream& operator<<(std::ostream& o,Webcast_type a){
	#define X(A) if(a==Webcast_type::A) return o<<""#A;
	TBA_WEBCAST_TYPES(X)
	#undef X
	assert(0);
}

Webcast_type decode(JSON const& in,const Webcast_type*){
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

Event_type decode(JSON const& in,const Event_type *){
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

Playoff_type decode(JSON const& in,const Playoff_type*){
	auto i=decode(in,(int*)0);
	#define X(A,B,C) if(i==A) return Playoff_type::B;
	TBA_PLAYOFF_TYPES(X)
	#undef X
	TBA_PRINT(in);
	throw std::invalid_argument(std::string()+"Playoff_type"+in.GetString());
}

MAKE_INST(Event,TBA_EVENT)

template<size_t LEN>
std::array<char,LEN> take(std::string const& s){
	std::array<char,LEN> r;
	std::copy_n(s.begin(),LEN,std::begin(r));
	return r;
}

Date::Date(std::string s1):s(s1){
	auto check=[*this](bool b){
		if(b) return;
		throw std::invalid_argument{"Date:"+s};
	};
	check(s.size()==10);

	{
		auto cs=take<4>(s);
		std::for_each(begin(cs),end(cs),[&](auto c){ check(isdigit(c)); });
	}

	check(s[4]=='-');
	check(isdigit(s[5]));
	check(isdigit(s[6]));
	check(s[7]=='-');
	check(isdigit(s[8]));
	check(isdigit(s[9]));
}

std::string Date::str()const{ return s; }

std::ostream& operator<<(std::ostream& o,Date const& a){
	return o<<a.str();
}

Date decode(JSON const& in,const Date*){
	return Date{decode(in,(std::string*)nullptr)};
}

MAKE_INST(Event_Simple,TBA_EVENT_SIMPLE)

std::ostream& operator<<(std::ostream& o,Media_type a){
	#define X(A,B) if(a==Media_type::A) return o<<""#B;
	TBA_MEDIA_TYPES(X)
	#undef X
	assert(0);
}

Media_type decode(JSON const& in,const Media_type*){
	auto s=decode(in,(std::string*)nullptr);
	#define X(A,B) if(s==""#B) return Media_type::A;
	TBA_MEDIA_TYPES(X)
	#undef X
	throw Decode_error{"Media_type",in,"unrecognized option"};
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

M_score decode(JSON const& in,const M_score*){
	if(in.IsNull()){
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

Winning_alliance decode(JSON const& in,const Winning_alliance *){
	auto s=decode(in,(std::string*)nullptr);
	if(s=="red") return Winning_alliance::red;
	if(s=="blue") return Winning_alliance::blue;
	if(s=="") return Winning_alliance::NONE;
	throw Decode_error{"Winning_alliance",in,"unrecognized option"};
}

#define PLAYOFF_LEVELS(X)\
	X(qm) X(ef) X(qf) X(sf) X(f)

std::ostream& operator<<(std::ostream& o,Playoff_level a){
	#define X(A) if(a==Playoff_level::A) return o<<""#A;
	PLAYOFF_LEVELS(X)
	#undef X
	assert(0);
}

Playoff_level decode(JSON const& in,const Playoff_level*){
	auto s=decode(in,(std::string*)nullptr);
	#define X(A) if(s==""#A) return Playoff_level::A;
	PLAYOFF_LEVELS(X)
	#undef X
	throw Decode_error{"Playoff_level",in,"unrecognized option"};
}

MAKE_INST(Match,TBA_MATCH)

MAKE_INST(Match_Simple,TBA_MATCH_SIMPLE)

MAKE_INST(Award_Recipient,TBA_RECIPIENT)

std::ostream& operator<<(std::ostream& o,Award_type a){
	#define X(A,B) if(a==Award_type::A) return o<<""#A;
	TBA_AWARD_TYPES(X)
	#undef X
	assert(0);
}

Award_type decode(JSON const& in,const Award_type *){
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

std::ostream& operator<<(std::ostream& o,Pick_order a){
	return o<<a.get();
}

Pick_order decode(JSON const& in,const Pick_order *){
	return Pick_order{decode(in,(int*)nullptr)};
}

MAKE_INST(Team_Event_Status_alliance,TBA_TEAM_EVENT_STATUS_ALLIANCE)

std::ostream& operator<<(std::ostream& o,Playoff_status a){
	#define X(A) if(a==Playoff_status::A) return o<<""#A;
	TBA_PLAYOFF_STATUS(X)
	#undef X
	assert(0);
}

Playoff_status decode(JSON const& in,const Playoff_status*){
	auto s=decode(in,(std::string*)nullptr);
	#define X(A) if(s==""#A) return Playoff_status::A;
	TBA_PLAYOFF_STATUS(X)
	#undef X
	throw std::invalid_argument{"Playoff_status:"+s};
}

MAKE_INST(Team_Event_Status_playoff,TBA_TEAM_EVENT_STATUS_PLAYOFF)

MAKE_INST(Team_Event_Status,TBA_TEAM_STATUS)

MAKE_INST(Event_ranking,TBA_EVENT_RANKING)

MAKE_INST(Points,TBA_POINTS)

MAKE_INST(Tiebreaker,TBA_TIEBREAKER)

MAKE_INST(Event_District_Points,TBA_EVENT_DISTRICT_POINTS)

std::ostream& operator<<(std::ostream& o,High_score const& a){
	o<<"High_score(";
	TBA_HIGH_SCORE(PRINT_ITEM)
	return o<<")";
}

High_score decode(JSON const& in,const High_score*){
	auto check=[&](bool b){
		if(b) return;
		std::ostringstream ss;
		ss<<"High_score:"<<in;
		throw std::invalid_argument{ss.str()};
	};
	check(in.IsArray());
	check(in.Size()==3);
	return High_score{
		decode(in[0],(int*)nullptr),
		decode(in[1],(Match_key*)nullptr),
		decode(in[2],(std::string*)nullptr),
	};
}

MAKE_INST(Event_Insights_2016_Detail,TBA_EVENT_INSIGHTS_2016_DETAIL)

MAKE_INST(Event_Insights_2016,TBA_EVENT_INSIGHTS_2016)

MAKE_INST(Event_Insights_2017_Detail,TBA_EVENT_INSIGHTS_2017_DETAIL)

MAKE_INST(Event_Insights_2017,TBA_EVENT_INSIGHTS_2017)

MAKE_INST(Event_Insights_2018_Detail,TBA_EVENT_INSIGHTS_2018_DETAIL)

MAKE_INST(Event_Insights_2018,TBA_EVENT_INSIGHTS_2018)

MAKE_INST(Event_Insights_2019_Detail,TBA_EVENT_INSIGHTS_2019_DETAIL)

MAKE_INST(Event_Insights_2019,TBA_EVENT_INSIGHTS_2019)

MAKE_INST(Event_Insights_2020_Detail,TBA_EVENT_INSIGHTS_2020_DETAIL)

MAKE_INST(Event_Insights_2020,TBA_EVENT_INSIGHTS_2020)

MAKE_INST(Event_Insights_2022_Detail,TBA_EVENT_INSIGHTS_2022_DETAIL)

MAKE_INST(Event_Insights_2022,TBA_EVENT_INSIGHTS_2022)

MAKE_INST(Event_Insights_2023_Detail,TBA_EVENT_INSIGHTS_2023_DETAIL)

MAKE_INST(Event_Insights_2023,TBA_EVENT_INSIGHTS_2023)

MAKE_INST(Average_rocket_count,TBA_AVERAGE_ROCKET_COUNT)

MAKE_INST(Event_OPRs,TBA_EVENT_OPRS)

MAKE_INST(Match_Score_Breakdown_2015_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2015_ALLIANCE)

std::ostream& operator<<(std::ostream& o,Coopertition a){
	#define X(A) if(a==Coopertition::A) return o<<""#A;
	TBA_COOPERTITION_TYPES(X)
	#undef X
	assert(0);
}

Coopertition decode(JSON const& in,const Coopertition*){
	auto s=decode(in,(std::string*)nullptr);
	#define X(A) if(s==""#A) return Coopertition::A;
	TBA_COOPERTITION_TYPES(X)
	#undef X
	throw std::invalid_argument{"Coopertition:"+s};
}

MAKE_INST(Match_Score_Breakdown_2015,TBA_MATCH_SCORE_BREAKDOWN_2015)

//#define EVENT_PREDICTTIONS(X)
//	X(
//seems to not be gaurnteed to do anything.

#define STR_OPT_INST(A) A,
#define STR_OPT_F2(A) if(a==NAME::A) return o<<""#A;
#define STR_OPT_DEC(A) if(s==""#A) return NAME::A;
#define STR(A) ""#A

#define STR_OPTIONS(OPTIONS)\
	std::ostream& operator<<(std::ostream& o,NAME a){\
		OPTIONS(STR_OPT_F2)\
		assert(0); \
	}\
	NAME decode(JSON const& in,const NAME *){\
		auto s=decode(in,(std::string*)nullptr);\
		OPTIONS(STR_OPT_DEC)\
		throw std::invalid_argument{STR(NAME)+std::string{":"}+s};\
	}

#define AUTO_2016_TYPES(X) X(Crossed) X(Reached) X(None)
#define NAME Auto_2016
STR_OPTIONS(AUTO_2016_TYPES)
#undef NAME

MAKE_INST(Match_Score_Breakdown_2016_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2016_ALLIANCE)

MAKE_INST(Match_Score_Breakdown_2016,TBA_MATCH_SCORE_BREAKDOWN_2016)

#define AUTO_2017(X) X(Unknown) X(Mobility) X(None)
#define NAME Auto_2017
STR_OPTIONS(AUTO_2017)
#undef NAME

MAKE_INST(Match_Score_Breakdown_2017_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2017_ALLIANCE)

MAKE_INST(Match_Score_Breakdown_2017,TBA_MATCH_SCORE_BREAKDOWN_2017)

MAKE_INST(Match_Score_Breakdown_2020_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2020_ALLIANCE)

MAKE_INST(Match_Score_Breakdown_2020,TBA_MATCH_SCORE_BREAKDOWN_2020)

#define YES_NO_OPTIONS(X) X(Yes) X(No)
#define NAME Yes_no
STR_OPTIONS(YES_NO_OPTIONS)
#undef NAME

#define NAME Endgame_2022
STR_OPTIONS(TBA_ENDGAME_2022_OPTIONS)
#undef NAME

MAKE_INST(Match_Score_Breakdown_2022_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2022_ALLIANCE)

MAKE_INST(Match_Score_Breakdown_2022,TBA_MATCH_SCORE_BREAKDOWN_2022)

MAKE_INST(Elimination_Alliance_status,TBA_ELIMINATION_ALLIANCE_STATUS)

MAKE_INST(Elimination_Alliance,TBA_ELIMINATION_ALLIANCE)

MAKE_INST(Year_info,TBA_YEAR_INFO)
MAKE_INST(Event_points,TBA_EVENT_POINTS)

Match_Score_Breakdown_2014_Alliance decode(JSON const& in,const Match_Score_Breakdown_2014_Alliance*){
	if(!in.IsObject()){
		throw Decode_error{"Match_Score_Breakdown_2014_Alliance",in,"Expected object"};
	}
	return Match_Score_Breakdown_2014_Alliance{
		#define X(A,B,C) DECODE(A,C)
		TBA_MATCH_SCORE_BREAKDOWN_2014_ALLIANCE(X)
		#undef X
	};
}

std::ostream& operator<<(std::ostream& o,Match_Score_Breakdown_2014_Alliance const& a){
	o<<"Match_score_breakdown_2014_alliance(";
	#define X(A,B,C) PRINT_ITEM(A,B)
	TBA_MATCH_SCORE_BREAKDOWN_2014_ALLIANCE(X)
	#undef X
	return o<<")";
}

MAKE_INST(Match_Score_Breakdown_2014,TBA_MATCH_SCORE_BREAKDOWN_2014)

//prediction stuff from here down; the docs warn that it is subject to change.

MAKE_INST(Brier_scores,TBA_BRIER_SCORES)
MAKE_INST(Match_prediction_set,TBA_MATCH_PREDICTION_SET)
MAKE_INST(Match_prediction_stats,TBA_MATCH_PREDICTION_STATS)

std::ostream& operator<<(std::ostream &o,Alliance_color a){
	if(a==Alliance_color::RED) return o<<"red";
	if(a==Alliance_color::BLUE) return o<<"blue";
	assert(0);
}

Alliance_color decode(JSON const& in,const Alliance_color*){
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

Unknown decode(JSON const& in,const Unknown*){
	auto s=decode(in,(std::string*)nullptr);
	if(s=="unknown") return Unknown{};
	std::ostringstream ss;
	ss<<"Expected \"unknown\", but got:"<<in;
	throw std::invalid_argument{ss.str()};
}

std::ostream& operator<<(std::ostream& o,Init_line a){
	#define X(A) if(a==Init_line::A) return o<<""#A;
	TBA_INIT_LINE_OPTIONS(X)
	#undef X
	assert(0);
}

Init_line decode(JSON const& in,Init_line const*){
	auto s=decode(in,(std::string*)nullptr);
	#define X(A) if(s==""#A) return Init_line::A;
	TBA_INIT_LINE_OPTIONS(X)
	#undef X
	TBA_PRINT(s);
	TBA_NYI
	//throw std::invalid_argument{s};
}

std::ostream& operator<<(std::ostream& o,Endgame a){
	#define X(A) if(a==Endgame::A) return o<<""#A;
	TBA_ENDGAME_OPTIONS(X)
	#undef X
	assert(0); 
}

Endgame decode(JSON const& in,Endgame const*){
	auto s=decode(in,(std::string*)nullptr);
	#define X(A) if(s==""#A) return Endgame::A;
	TBA_ENDGAME_OPTIONS(X)
	#undef X
	TBA_PRINT(s);
	TBA_NYI
}

std::ostream& operator<<(std::ostream& o,Target_color a){
	#define X(A) if(a==Target_color::A) return o<<""#A;
	TBA_TARGET_COLOR_OPTIONS(X)
	#undef X
	assert(0);
}

Target_color decode(JSON const& in,Target_color const*){
	auto s=decode(in,(std::string*)nullptr);
	#define X(A) if(s==""#A) return Target_color::A;
	TBA_TARGET_COLOR_OPTIONS(X)
	#undef X
	TBA_PRINT(s);
	TBA_NYI
}

std::ostream& operator<<(std::ostream& o,Rung_level a){
	#define X(A) if(a==Rung_level::A) return o<<""#A;
	TBA_RUNG_LEVEL_OPTIONS(X)
	#undef X
	assert(0);
}

Rung_level decode(JSON const& in,Rung_level const*){
	auto s=decode(in,(std::string*)nullptr);
	#define X(A) if(s==""#A) return Rung_level::A;
	TBA_RUNG_LEVEL_OPTIONS(X)
	#undef X
	TBA_PRINT(s);
	TBA_NYI
}

}
