#ifndef TBA_DATA_H
#define TBA_DATA_H

#include<vector>
#include<optional>
#include<map>
#include<variant>
#include<array>
#include "rapidjson/document.h"
#include "simdjson.h"

#define TBA_SINGLE_ARG(A,B) A,B

namespace tba{

std::strong_ordering operator<=>(std::optional<std::nullptr_t> const&,std::optional<std::nullptr_t> const&);

using JSON=rapidjson::GenericValue<rapidjson::UTF8<>>;
using URL=std::string;

#define TBA_INST(A,B) A B;

#define TBA_MAKE_INST(NAME,ITEMS)\
	struct NAME{ \
		ITEMS(TBA_INST) \
		auto operator<=>(NAME const&)const=default;\
	};\
	std::ostream& operator<<(std::ostream&,NAME const&);\
	NAME decode(JSON const& in,const NAME*);\
	NAME decode(JSON_value,const NAME*);\
	NAME decode(JSON_object,const NAME*);\
	NAME decode(JSON_array,const NAME*);\
	NAME decode(std::nullptr_t,NAME const*);\

using Page=unsigned;

class Year{
	//An integer that is between 1992 and 2092.
	int i;

	bool valid()const;

	public:
	explicit Year(int);
	int get()const;

	Year& operator--();

	auto operator<=>(Year const&)const=default;
	friend Year& operator++(Year&);
};

std::ostream& operator<<(std::ostream& o,Year);
Year& operator++(Year&);
Year operator++(Year&,int);
Year operator-(Year,int);
Year decode(JSON const&,const Year*);
Year decode(JSON_value,const Year*);

#define TBA_API_STATUS_APP_VERSION(X)\
	X(int,min_app_version)\
	X(int,latest_app_version)

TBA_MAKE_INST(API_Status_App_Version,TBA_API_STATUS_APP_VERSION)

#define TBA_API_STATUS(X) \
	X(int,current_season)\
	X(int,max_season)\
	X(bool,is_datafeed_down)\
	X(std::vector<std::string>,down_events)\
	X(API_Status_App_Version,ios)\
	X(API_Status_App_Version,android)

TBA_MAKE_INST(API_Status,TBA_API_STATUS)

class Team_key{
	std::string s;

	public:
	explicit Team_key(std::string);
	std::string const& str()const;

	auto operator<=>(Team_key const&)const=default;
};

std::ostream& operator<<(std::ostream&,Team_key const&);
Team_key decode(JSON const& in,const Team_key*);
Team_key decode(JSON_value,Team_key const*);

#define TBA_TEAM(X)\
	X(Team_key,key)\
	X(int,team_number)\
	X(std::optional<std::string>,nickname)\
	X(std::optional<std::string>,name)\
	X(std::optional<std::string>,city)\
	X(std::optional<std::string>,state_prov)\
	X(std::optional<std::string>,country)\
	X(std::optional<std::string>,address)\
	X(std::optional<std::string>,postal_code)\
	X(std::optional<std::string>,gmaps_place_id)\
	X(std::optional<URL>,gmaps_url)\
	X(std::optional<double>,lat)\
	X(std::optional<double>,lng)\
	X(std::optional<std::string>,location_name)\
	X(std::optional<URL>,website)\
	X(std::optional<Year>,rookie_year)\
	X(std::optional<std::string>,motto)\
	X(std::optional<TBA_SINGLE_ARG(std::map<std::string,std::string>)>,home_championship)

TBA_MAKE_INST(Team,TBA_TEAM)

#define TBA_TEAM_ROBOT(X)\
	X(Year,year)\
	X(std::string,robot_name)\
	X(std::string,key)\
	X(Team_key,team_key)

TBA_MAKE_INST(Team_Robot,TBA_TEAM_ROBOT)

using Team_number=int;

#define TBA_TEAM_SIMPLE(X)\
	X(Team_key,key)\
	X(Team_number,team_number)\
	X(std::optional<std::string>,nickname)\
	X(std::optional<std::string>,name)\
	X(std::optional<std::string>,city)\
	X(std::optional<std::string>,state_prov)\
	X(std::optional<std::string>,country)

TBA_MAKE_INST(Team_Simple,TBA_TEAM_SIMPLE)

class District_key{
	std::string s;

	public:
	explicit District_key(std::string);
	std::string const& get()const;

	auto operator<=>(District_key const&)const=default;
};

std::ostream& operator<<(std::ostream&,District_key const&);
bool operator==(District_key const&,std::string const&);
District_key decode(JSON const&,const District_key*);
District_key decode(JSON_value,const District_key*);

#define TBA_DISTRICT_LIST(X)\
	X(std::string,abbreviation)\
	X(std::string,display_name)\
	X(District_key,key)\
	X(Year,year)

TBA_MAKE_INST(District_List,TBA_DISTRICT_LIST)

class Event_key{
	std::string s;

	public:
	explicit Event_key(std::string);
	std::string const& get()const;

	auto operator<=>(Event_key const&)const=default;
};

bool operator==(Event_key const&,const char *);
std::ostream& operator<<(std::ostream&,Event_key const&);
Event_key decode(JSON const& in,const Event_key*);
Event_key decode(JSON_value,Event_key const*);

#define TBA_EVENT_POINTS(X)\
	X(Event_key,event_key)\
	X(bool,district_cmp)\
	X(int,alliance_points)\
	X(int,award_points)\
	X(int,qual_points)\
	X(double,elim_points)\
	X(double,total)

TBA_MAKE_INST(Event_points,TBA_EVENT_POINTS)

#define TBA_DISTRICT_RANKING(X)\
	X(Team_key,team_key)\
	X(int,rank)\
	X(int,rookie_bonus)\
	X(double,point_total)\
	X(std::vector<Event_points>,event_points)

TBA_MAKE_INST(District_Ranking,TBA_DISTRICT_RANKING)

#define TBA_WEBCAST_TYPES(X)\
	X(youtube)\
	X(twitch)\
	X(ustream)\
	X(ifream)\
	X(html5)\
	X(rtmp)\
	X(livestream)

enum class Webcast_type{
	#define X(A) A,
	TBA_WEBCAST_TYPES(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Webcast_type);
Webcast_type decode(JSON const& in,const Webcast_type*);
Webcast_type decode(JSON_value,const Webcast_type*);

#define TBA_WEBCAST(X)\
	X(Webcast_type,type)\
	X(std::string,channel)\
	X(std::string,file)
//supposedly, file may be null; it never seems to be though.

TBA_MAKE_INST(Webcast,TBA_WEBCAST)

#define TBA_EVENT_TYPES(X)\
	X(REGIONAL,0)\
	X(DISTRICT,1)\
	X(DISTRICT_CMP,2)\
	X(CMP_DIVISION,3)\
	X(CMP_FINALS,4)\
	X(DISTRICT_CMP_DIVISION,5)\
	X(FOC,6)\
	X(REMOTE,7)\
	X(OFFSEASON,99)\
	X(PRESEASON,100)\
	X(UNLABLED,-1)

enum class Event_type{
	#define X(A,B) A,
	TBA_EVENT_TYPES(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Event_type);
Event_type decode(JSON const& in,const Event_type *);
Event_type decode(JSON_value,const Event_type *);

#define TBA_PLAYOFF_TYPES(X)\
	X(0,BRACKET_8_TEAM,"Elimination Bracket (8 Alliances)")\
	X(1,BRACKET_16_TEAM,"Elimination Bracket (16 Alliances)")\
	X(2,BRACKET_4_TEAM,"Elimination Bracket (4 Alliances)")\
	X(3,AVG_SCORE_8_TEAM, "Average Score (8 Alliances)")\
	X(4,ROUND_ROBIN_6_TEAM, "Round Robin (6 Alliances)")\
	X(5,DOUBLE_ELIM_8_TEAM, "Double Elimination Bracket (8 Alliances)")\
	X(6,BO5_FINALS,"Best of 5 Finals")\
	X(7,BO3_FINALS,"Best of 3 Finals")\
	X(8,CUSTOM,"Custom playoff type")\
	X(9,EB2,"Elimination Bracket (2 Alliances)")\
	X(10,DE8,"Double Elimination Bracket (8 Alliances)")\
	X(11,DE4,"Double Elimination Bracket (4 Alliances)")

enum class Playoff_type{
	#define X(A,B,C) B,
	TBA_PLAYOFF_TYPES(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Playoff_type);

Playoff_type decode(JSON const& in,const Playoff_type*);
Playoff_type decode(JSON_value,const Playoff_type*);

class Date{
	//yyyy-mm-dd format
	std::string s;

	public:
	explicit Date(std::string);
	std::string str()const;

	auto operator<=>(Date const&)const=default;
};

std::ostream& operator<<(std::ostream&,Date const&);
Date decode(JSON const&,const Date*);
Date decode(JSON_value,const Date*);

#define TBA_EVENT(X)\
	X(Event_key,key)\
	X(std::string,name)\
	X(std::string,event_code)\
	X(Event_type,event_type)\
	X(std::optional<District_List>,district)\
	X(std::optional<std::string>,city)\
	X(std::optional<std::string>,state_prov)\
	X(std::optional<std::string>,country)\
	X(std::optional<Date>,start_date)\
	X(std::optional<Date>,end_date)\
	X(Year,year)\
	X(std::optional<std::string>,short_name)\
	X(std::string,event_type_string)\
	X(std::optional<int>,week)\
	X(std::optional<std::string>,address)\
	X(std::optional<std::string>,postal_code)\
	X(std::optional<std::string>,gmaps_place_id)\
	X(std::optional<URL>,gmaps_url)\
	X(std::optional<double>,lat)\
	X(std::optional<double>,lng)\
	X(std::optional<std::string>,location_name)\
	X(std::optional<std::string>,timezone)\
	X(std::optional<std::string>,website)\
	X(std::optional<std::string>,first_event_id)\
	X(std::optional<Webcast>,webcast)\
	X(std::vector<Event_key>,division_keys)\
	X(std::optional<std::string>,parent_event_key)\
	X(std::optional<Playoff_type>,playoff_type)\
	X(std::optional<std::string>,playoff_type_string)	
	
TBA_MAKE_INST(Event,TBA_EVENT)

#define TBA_EVENT_SIMPLE(X)\
	X(Event_key,key)\
	X(std::string,name)\
	X(std::string,event_code)\
	X(Event_type,event_type)\
	X(std::optional<District_List>,district)\
	X(std::optional<std::string>,city)\
	X(std::optional<std::string>,state_prov)\
	X(std::optional<std::string>,country)\
	X(std::optional<tba::Date>,start_date)\
	X(std::optional<tba::Date>,end_date)\
	X(Year,year)

TBA_MAKE_INST(Event_Simple,TBA_EVENT_SIMPLE)

#define TBA_MEDIA_TYPES(X)\
	X(YOUTUBE,youtube)\
	X(CDPHOTOTHREAD,cdphotothread)\
	X(IMGUR,imgur)\
	X(FACEBOOK_PROFILE,facebook-profile)\
	X(YOUTUBE_CHANNEL,youtube-channel)\
	X(TWITTER_PROFILE,twitter-profile)\
	X(GITHUB_PROFILE,github-profile)\
	X(INSTAGRAM_PROFILE,instagram-profile)\
	X(PREISCOPE_PROFILE,periscope-profile)\
	X(GRABCAD,grabcad)\
	X(PINTEREST_PROFILE,pinterest-profile)\
	X(SNAPCHAT_PROFILE,snapchat-profile)\
	X(TWITCH_CHANNEL,twitch-channel)\
	X(TBA,tba)\
	X(INSTAGRAM_IMAGE,instagram-image)\
	X(EXTERNAL_LINK,external-link)\
	X(AVATAR,avatar)\
	X(ONSHAPE,onshape)
//"tba" occurs, but is not documented.
//"instagram-image", and "external-link" were originally not documented but are as of 2019.

enum class Media_type{
	#define X(A,B) A,
	TBA_MEDIA_TYPES(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Media_type);
Media_type decode(JSON const&,const Media_type*);
Media_type decode(JSON_value,const Media_type*);

#define TBA_MEDIA_DETAILS(X)\
	X(std::optional<int64_t>,author_id)\
	X(std::optional<std::string>,author_name)\
	X(std::optional<std::string>,author_url)\
	X(std::optional<std::nullptr_t>,height)\
	X(std::optional<std::string>,html)\
	X(std::optional<std::string>,media_id)\
	X(std::optional<std::string>,provider_name)\
	X(std::optional<std::string>,provider_url)\
	X(std::optional<unsigned>,thumbnail_height)\
	X(std::optional<std::string>,thumbnail_url)\
	X(std::optional<unsigned>,thumbnail_width)\
	X(std::optional<std::string>,title)\
	X(std::optional<std::string>,type)\
	X(std::optional<std::string>,version)\
	X(std::optional<unsigned>,width)\
	X(std::optional<std::string>,image_partial)

TBA_MAKE_INST(Media_details,TBA_MEDIA_DETAILS)

#define TBA_MEDIA(X)\
	X(std::optional<std::string>,key)\
	X(Media_type,type)\
	X(std::optional<std::string>,foreign_key)\
	X(std::optional<Media_details>,details)\
	X(std::optional<bool>,preferred)

TBA_MAKE_INST(Media,TBA_MEDIA)

class M_score{
	//score=-1 or null => not played
	int i;

	public:
	explicit M_score(int i1);

	bool valid()const;
	int value()const;

	auto operator<=>(M_score const&)const=default;
};

std::ostream& operator<<(std::ostream&,M_score const&);
M_score decode(JSON const&,const M_score*);
M_score decode(JSON_value,const M_score*);

#define TBA_MATCH_ALLIANCE(X)\
	X(M_score,score)\
	X(std::vector<Team_key>,team_keys)\
	X(std::vector<Team_key>,surrogate_team_keys)

TBA_MAKE_INST(Match_Alliance,TBA_MATCH_ALLIANCE)

#define TBA_ALLIANCES(X)\
	X(Match_Alliance,red)\
	X(Match_Alliance,blue)

TBA_MAKE_INST(Alliances,TBA_ALLIANCES)

enum class Winning_alliance{red,blue,NONE};

std::ostream& operator<<(std::ostream&,Winning_alliance);

Winning_alliance decode(JSON const&,const Winning_alliance *);
Winning_alliance decode(JSON_value,const Winning_alliance *);

#define TBA_PLAYOFF_LEVELS(X) X(qm) X(ef) X(qf) X(sf) X(f)

enum class Playoff_level{
	#define X(A) A,
	TBA_PLAYOFF_LEVELS(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Playoff_level);
Playoff_level decode(JSON const&,const Playoff_level*);
Playoff_level decode(JSON_value,const Playoff_level*);

using Competition_level=Playoff_level;//this is probably going to have to change.

/*
curiosly, this sometimes appears as just:
    "score_breakdown": {
      "blue": {
        "auto": null, 
        "foul": null
      }, 
      "red": {
        "auto": null, 
        "foul": null
      }
which basically means that nothing can be relied on to be there.
*/
#define TBA_MATCH_SCORE_BREAKDOWN_2015_ALLIANCE(X)\
	X(std::optional<int>,auto_points)\
	X(std::optional<int>,teleop_points)\
	X(std::optional<int>,container_points)\
	X(std::optional<int>,tote_points)\
	X(std::optional<int>,litter_points)\
	X(std::optional<int>,foul_points)\
	X(std::optional<int>,adjust_points)\
	X(std::optional<int>,total_points)\
	X(std::optional<int>,foul_count)\
	X(std::optional<int>,tote_count_far)\
	X(std::optional<int>,tote_count_near)\
	X(std::optional<bool>,tote_set)\
	X(std::optional<bool>,tote_stack)\
	X(std::optional<int>,container_count_level1)\
	X(std::optional<int>,container_count_level2)\
	X(std::optional<int>,container_count_level3)\
	X(std::optional<int>,container_count_level4)\
	X(std::optional<int>,container_count_level5)\
	X(std::optional<int>,container_count_level6)\
	X(std::optional<bool>,container_set)\
	X(std::optional<int>,litter_count_container)\
	X(std::optional<int>,litter_count_landfill)\
	X(std::optional<int>,litter_count_unprocessed)\
	X(std::optional<bool>,robot_set)

TBA_MAKE_INST(Match_Score_Breakdown_2015_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2015_ALLIANCE)

//docs do not include "Set"
#define TBA_COOPERTITION_TYPES(X)\
	X(None) X(Unknown) X(Stack) X(Set)

enum class Coopertition{
	#define X(A) A,
	TBA_COOPERTITION_TYPES(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Coopertition);
Coopertition decode(JSON const& in,const Coopertition*);
Coopertition decode(JSON_value,const Coopertition*);

#define TBA_MATCH_SCORE_BREAKDOWN_2015(X)\
	X(Match_Score_Breakdown_2015_Alliance,blue)\
	X(Match_Score_Breakdown_2015_Alliance,red)\
	X(std::optional<Coopertition>,coopertition)\
	X(std::optional<int>,coopertition_points)

TBA_MAKE_INST(Match_Score_Breakdown_2015,TBA_MATCH_SCORE_BREAKDOWN_2015)

#define TBA_STR_OPT_INST(A) A,

#define TBA_STR_OPTIONS(OPTIONS)\
	enum class NAME{ OPTIONS(TBA_STR_OPT_INST) };\
	std::ostream& operator<<(std::ostream&,NAME);\
	NAME decode(JSON const&,const NAME *);\
	NAME decode(JSON_value,const NAME *);\

#define TBA_AUTO_2016_TYPES(X) X(Crossed) X(Reached) X(None)

#define NAME Auto_2016
TBA_STR_OPTIONS(TBA_AUTO_2016_TYPES)
#undef NAME

#define TBA_MATCH_SCORE_BREAKDOWN_2016_ALLIANCE(X)\
	X(int,autoPoints)\
	X(int,teleopPoints)\
	X(std::optional<int>,breechPoints)\
	X(int,foulPoints)\
	X(int,capturePoints)\
	X(std::optional<int>,adjustPoints)\
	X(int,totalPoints)\
	X(Auto_2016,robot1Auto)\
	X(Auto_2016,robot2Auto)\
	X(Auto_2016,robot3Auto)\
	X(int,autoReachPoints)\
	X(int,autoCrossingPoints)\
	X(int,autoBouldersLow)\
	X(int,autoBouldersHigh)\
	X(int,teleopCrossingPoints)\
	X(int,teleopBouldersLow)\
	X(int,teleopBouldersHigh)\
	X(int,teleopBoulderPoints)\
	X(bool,teleopDefensesBreached)\
	X(int,teleopChallengePoints)\
	X(int,teleopScalePoints)\
	X(bool,teleopTowerCaptured)\
	X(std::string,towerFaceA)\
	X(std::string,towerFaceB)\
	X(std::string,towerFaceC)\
	X(int,towerEndStrength)\
	X(int,techFoulCount)\
	X(int,foulCount)\
	X(std::string,position2)\
	X(std::string,position3)\
	X(std::string,position4)\
	X(std::string,position5)\
	X(int,position1crossings)\
	X(int,position2crossings)\
	X(int,position3crossings)\
	X(int,position4crossings)\
	X(int,position5crossings)

TBA_MAKE_INST(Match_Score_Breakdown_2016_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2016_ALLIANCE)

#define TBA_MATCH_SCORE_BREAKDOWN_2016(X)\
	X(Match_Score_Breakdown_2016_Alliance,blue)\
	X(Match_Score_Breakdown_2016_Alliance,red)

TBA_MAKE_INST(Match_Score_Breakdown_2016,TBA_MATCH_SCORE_BREAKDOWN_2016)

#define TBA_AUTO_2017(X) X(Unknown) X(Mobility) X(None)
#define NAME Auto_2017
TBA_STR_OPTIONS(TBA_AUTO_2017)
#undef NAME

#define TBA_MATCH_SCORE_BREAKDOWN_2017_ALLIANCE(X)\
	X(int,autoPoints)\
	X(int,teleopPoints)\
	X(std::optional<int>,breechPoints)\
	X(int,foulPoints)\
	X(std::optional<int>,capturePoints)\
	X(std::optional<int>,adjustPoints)\
	X(int,totalPoints)\
	X(std::optional<Auto_2017>,robot1Auto)\
	X(std::optional<Auto_2017>,robot2Auto)\
	X(std::optional<Auto_2017>,robot3Auto)\
	X(bool,rotor1Auto)\
	X(bool,rotor2Auto)\
	X(int,autoFuelLow)\
	X(int,autoFuelHigh)\
	X(int,autoMobilityPoints)\
	X(std::optional<int>,autoRobotPoints)\
	X(int,teleopFuelPoints)\
	X(int,teleopFuelLow)\
	X(int,teleopFuelHigh)\
	X(int,teleopRotorPoints)\
	X(std::optional<bool>,kPaRankingPointArchieved)\
	X(int,teleopTakeoffPoints)\
	X(int,kPaBonusPoints)\
	X(int,rotorBonusPoints)\
	X(bool,rotor1Engaged)\
	X(bool,rotor2Engaged)\
	X(bool,rotor3Engaged)\
	X(bool,rotor4Engaged)\
	X(bool,rotorRankingPointAchieved)\
	X(std::optional<int>,techFoulCount)\
	X(std::optional<int>,foulCount)\
	X(std::optional<std::string>,touchpadNear)\
	X(std::optional<std::string>,touchpadMiddle)\
	X(std::optional<std::string>,touchpadFar)

TBA_MAKE_INST(Match_Score_Breakdown_2017_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2017_ALLIANCE)

#define TBA_MATCH_SCORE_BREAKDOWN_2017(X)\
	X(Match_Score_Breakdown_2017_Alliance,blue)\
	X(Match_Score_Breakdown_2017_Alliance,red)

TBA_MAKE_INST(Match_Score_Breakdown_2017,TBA_MATCH_SCORE_BREAKDOWN_2017)

#define TBA_MATCH_SCORE_BREAKDOWN_2019(X)\
        X(int,adjustPoints)\
        X(int,autoPoints)\
        X(std::string,bay1)\
        X(std::string,bay2)\
        X(std::string,bay3)\
        X(std::string,bay4)\
        X(std::string,bay5)\
        X(std::string,bay6)\
        X(std::string,bay7)\
        X(std::string,bay8)\
        X(int,cargoPoints)\
        X(bool,completeRocketRankingPoint)\
        X(bool,completedRocketFar)\
        X(bool,completedRocketNear)\
        X(std::string,endgameRobot1)\
        X(std::string,endgameRobot2)\
        X(std::string,endgameRobot3)\
        X(int,foulCount)\
        X(int,foulPoints)\
        X(int,habClimbPoints)\
        X(bool,habDockingRankingPoint)\
        X(std::string,habLineRobot1)\
        X(std::string,habLineRobot2)\
        X(std::string,habLineRobot3)\
        X(int,hatchPanelPoints)\
        X(std::string,lowLeftRocketFar)\
        X(std::string,lowLeftRocketNear)\
        X(std::string,lowRightRocketFar)\
        X(std::string,lowRightRocketNear)\
        X(std::string,midLeftRocketFar)\
        X(std::string,midLeftRocketNear)\
        X(std::string,midRightRocketFar)\
        X(std::string,midRightRocketNear)\
        X(std::string,preMatchBay1)\
        X(std::string,preMatchBay2)\
        X(std::string,preMatchBay3)\
        X(std::string,preMatchBay6)\
        X(std::string,preMatchBay7)\
        X(std::string,preMatchBay8)\
        X(std::string,preMatchLevelRobot1)\
        X(std::string,preMatchLevelRobot2)\
        X(std::string,preMatchLevelRobot3)\
        X(int,rp)\
        X(int,sandStormBonusPoints)\
        X(int,techFoulCount)\
        X(int,teleopPoints)\
        X(std::string,topLeftRocketFar)\
        X(std::string,topLeftRocketNear)\
        X(std::string,topRightRocketFar)\
        X(std::string,topRightRocketNear)\
        X(int,totalPoints)


//TBA_MAKE_INST(Match_Score_Breakdown_2018,TBA_MATCH_SCORE_BREAKDOWN_2018)

#define TBA_MATCH_SCORE_BREAKDOWN_2014_ALLIANCE(X)\
	X(int,assist,assist)\
	X(int,auto_pts,auto)\
	X(int,teleop_goal_and_foul,teleop_goal+foul)\
	X(int,truss_and_catch,truss+catch)

struct Match_Score_Breakdown_2014_Alliance{
	#define X(A,B,C) A B;
	TBA_MATCH_SCORE_BREAKDOWN_2014_ALLIANCE(X)
	#undef X

	auto operator<=>(Match_Score_Breakdown_2014_Alliance const&)const=default;
};

std::ostream& operator<<(std::ostream&,Match_Score_Breakdown_2014_Alliance const&);
Match_Score_Breakdown_2014_Alliance decode(JSON const&,const Match_Score_Breakdown_2014_Alliance*);
Match_Score_Breakdown_2014_Alliance decode(JSON_value,const Match_Score_Breakdown_2014_Alliance*);

#define TBA_MATCH_SCORE_BREAKDOWN_2014(X)\
	X(Match_Score_Breakdown_2014_Alliance,blue)\
	X(Match_Score_Breakdown_2014_Alliance,red)

TBA_MAKE_INST(Match_Score_Breakdown_2014,TBA_MATCH_SCORE_BREAKDOWN_2014)

#define TBA_INIT_LINE_OPTIONS(X)\
	X(Exited)\
	X(None)

enum class Init_line{
	#define X(A) A,
	TBA_INIT_LINE_OPTIONS(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Init_line);
Init_line decode(JSON const&,Init_line const*);
Init_line decode(JSON_value,Init_line const*);

#define TBA_ENDGAME_OPTIONS(X)\
	X(Park)\
	X(None)\
	X(Hang)

enum class Endgame{
	#define X(A) A,
	TBA_ENDGAME_OPTIONS(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Endgame);
Endgame decode(JSON const&,Endgame const*);
Endgame decode(JSON_value,Endgame const*);

#define TBA_TARGET_COLOR_OPTIONS(X)\
	X(Unknown)\
	X(Blue)\
	X(Green)\
	X(Yellow)\
	X(Red)

enum class Target_color{
	#define X(A) A,
	TBA_TARGET_COLOR_OPTIONS(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Target_color);
Target_color decode(JSON const&,Target_color const*);
Target_color decode(JSON_value,Target_color const*);

#define TBA_RUNG_LEVEL_OPTIONS(X)\
	X(NotLevel)\
	X(IsLevel)

enum class Rung_level{
	#define X(A) A,
	TBA_RUNG_LEVEL_OPTIONS(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Rung_level);
Rung_level decode(JSON const&,Rung_level const*);
Rung_level decode(JSON_value,Rung_level const*);

#define TBA_MATCH_SCORE_BREAKDOWN_2020_ALLIANCE(X)\
	X(Init_line,initLineRobot1)\
	X(Endgame,endgameRobot1)\
	X(Init_line,initLineRobot2)\
	X(Endgame,endgameRobot2)\
	X(Init_line,initLineRobot3)\
	X(Endgame,endgameRobot3)\
	X(int,autoCellsBottom)\
	X(int,autoCellsOuter)\
	X(int,autoCellsInner)\
	X(int,teleopCellsBottom)\
	X(int,teleopCellsOuter)\
	X(int,teleopCellsInner)\
	X(bool,stage1Activated)\
	X(bool,stage2Activated)\
	X(bool,stage3Activated)\
	X(Target_color,stage3TargetColor)\
	X(Rung_level,endgameRungIsLevel)\
	X(int,autoInitLinePoints)\
	X(int,autoCellPoints)\
	X(int,autoPoints)\
	X(int,teleopCellPoints)\
	X(int,controlPanelPoints)\
	X(int,endgamePoints)\
	X(int,teleopPoints)\
	X(bool,shieldOperationalRankingPoint)\
	X(bool,shieldEnergizedRankingPoint)\
	X(bool,tba_shieldEnergizedRankingPointFromFoul)\
	X(int,tba_numRobotsHanging)\
	X(int,foulCount)\
	X(int,techFoulCount)\
	X(int,adjustPoints)\
	X(int,foulPoints)\
	X(int,rp)\
	X(int,totalPoints)

struct Match_Score_Breakdown_2020_Alliance{
	#define X(A,B) A B;
	TBA_MATCH_SCORE_BREAKDOWN_2020_ALLIANCE(X)
	#undef X

	auto operator<=>(Match_Score_Breakdown_2020_Alliance const&)const=default;
};

std::ostream& operator<<(std::ostream&,Match_Score_Breakdown_2020_Alliance const&);
Match_Score_Breakdown_2020_Alliance decode(JSON const&,const Match_Score_Breakdown_2020_Alliance*);
Match_Score_Breakdown_2020_Alliance decode(JSON_value,const Match_Score_Breakdown_2020_Alliance*);


#define TBA_MATCH_SCORE_BREAKDOWN_2020(X)\
	X(Match_Score_Breakdown_2020_Alliance,blue)\
	X(Match_Score_Breakdown_2020_Alliance,red)

TBA_MAKE_INST(Match_Score_Breakdown_2020,TBA_MATCH_SCORE_BREAKDOWN_2020)

enum class Yes_no{
	Yes,No //not all-caps to preserve being as documented in API
};

#define TBA_ENDGAME_2022_OPTIONS(X)\
	X(Traversal)\
	X(High)\
	X(Mid)\
	X(Low)\
	X(None)

enum class Endgame_2022{
	#define X(A) A,
	TBA_ENDGAME_2022_OPTIONS(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Endgame_2022);

#define TBA_MATCH_SCORE_BREAKDOWN_2022_ALLIANCE(X)\
	X(Yes_no,taxiRobot1)\
	X(Endgame_2022,endgameRobot1)\
	X(Yes_no,taxiRobot2)\
	X(Endgame_2022,endgameRobot2)\
	X(Yes_no,taxiRobot3)\
	X(Endgame_2022,endgameRobot3)\
	X(int,autoCargoLowerNear)\
	X(int,autoCargoLowerFar)\
	X(int,autoCargoLowerBlue)\
	X(int,autoCargoLowerRed)\
	X(int,autoCargoUpperNear)\
	X(int,autoCargoUpperFar)\
	X(int,autoCargoUpperBlue)\
	X(int,autoCargoUpperRed)\
	X(int,autoCargoTotal)\
	X(int,teleopCargoLowerNear)\
	X(int,teleopCargoLowerFar)\
	X(int,teleopCargoLowerBlue)\
	X(int,teleopCargoLowerRed)\
	X(int,teleopCargoUpperNear)\
	X(int,teleopCargoUpperFar)\
	X(int,teleopCargoUpperBlue)\
	X(int,teleopCargoUpperRed)\
	X(int,teleopCargoTotal)\
	X(int,matchCargoTotal)\
	X(int,autoTaxiPoints)\
	X(int,autoCargoPoints)\
	X(int,autoPoints)\
	X(bool,quintetAchieved)\
	X(int,teleopCargoPoints)\
	X(int,endgamePoints)\
	X(bool,cargoBonusRankingPoint)\
	X(bool,hangarBonusRankingPoint)\
	X(int,foulCount)\
	X(int,techFoulCount)\
	X(int,adjustPoints)\
	X(int,foulPoints)\
	X(int,rp)\
	X(int,totalPoints)

TBA_MAKE_INST(Match_Score_Breakdown_2022_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2022_ALLIANCE)

#define TBA_MATCH_SCORE_BREAKDOWN_2022(X)\
	X(Match_Score_Breakdown_2022_Alliance,blue)\
	X(Match_Score_Breakdown_2022_Alliance,red)

TBA_MAKE_INST(Match_Score_Breakdown_2022,TBA_MATCH_SCORE_BREAKDOWN_2022)

using Match_Score_Breakdown=std::variant<
	Match_Score_Breakdown_2022,
	Match_Score_Breakdown_2020,
	Match_Score_Breakdown_2017,
	Match_Score_Breakdown_2014,
	Match_Score_Breakdown_2016,
	Match_Score_Breakdown_2015
>;

#define TBA_MATCH(X)\
	X(std::string,key)\
	X(Competition_level,comp_level)\
	X(int,set_number)\
	X(int,match_number)\
	X(Alliances,alliances)\
	X(Winning_alliance,winning_alliance)\
	X(Event_key,event_key)\
	X(std::optional<time_t>,time)\
	X(std::optional<time_t>,actual_time)\
	X(std::optional<time_t>,predicted_time)\
	X(std::optional<time_t>,post_result_time)\
	X(std::optional<Match_Score_Breakdown>,score_breakdown)\
	X(std::vector<Media>,videos)

//TODO: score_breakdown likely needs work.

TBA_MAKE_INST(Match,TBA_MATCH)

#define TBA_MATCH_SIMPLE(X)\
	X(std::string,key)\
	X(Competition_level,comp_level)\
	X(int,set_number)\
	X(int,match_number)\
	X(Alliances,alliances)\
	X(Winning_alliance,winning_alliance)\
	X(Event_key,event_key)\
	X(std::optional<time_t>,time)\
	X(std::optional<time_t>,actual_time)\
	X(std::optional<time_t>,predicted_time)

TBA_MAKE_INST(Match_Simple,TBA_MATCH_SIMPLE)

//at least one of these items should be set though.
#define TBA_RECIPIENT(X)\
	X(std::optional<Team_key>,team_key)\
	X(std::optional<std::string>,awardee)

TBA_MAKE_INST(Award_Recipient,TBA_RECIPIENT)

#define TBA_AWARD_TYPES(X)\
	X(CHAIRMANS,0)\
	X(WINNER,1)\
	X(FINALIST,2)\
	X(WOODIE_FLOWERS,3)\
	X(DEANS_LIST,4)\
	X(VOLUNTEER,5)\
	X(FOUNDERS,6)\
	X(BART_KAMEN_MEMORIAL,7)\
	X(MAKE_IT_LOUD,8)\
	X(ENGINEERING_INSPIRATION,9)\
	X(ROOKIE_ALL_STAR,10)\
	X(GRACIOUS_PROFESSIONALISM,11)\
	X(COOPERTITION,12)\
	X(JUDGES,13)\
	X(HIGHEST_ROOKIE_SEED,14)\
	X(ROOKIE_INSPIRATION,15)\
	X(INDUSTRIAL_DEESIGN,16)\
	X(QUALITY,17)\
	X(SAFETY,18)\
	X(SPORTSMANSHIP,19)\
	X(CREATIVITY,20)\
	X(ENGINEERING_EXCELLENCE,21)\
	X(ENTREPRENEURSHIP,22)\
	X(EXCELLENCE_IN_DESIGN,23)\
	X(EXCELLENCE_IN_DESIGN_CAD,24)\
	X(EXCELLENCE_IN_DESIGN_ANIMATION,25)\
	X(DRIVING_TOMORROWS_TECHNOLOGY,26)\
	X(IMAGERY,27)\
	X(MEDIA_AND_TECHNOLOGY,28)\
	X(INNOVATION_IN_CONTROL,29)\
	X(SPIRIT,30)\
	X(WEBSITE,31)\
	X(VISUALIZATION,32)\
	X(AUTODESK_INVENTOR,33)\
	X(FUTURE_INNOVATOR,34)\
	X(RECOGNITION_OF_EXTRAORDINARY_SERVICE,35)\
	X(OUTSTANDING_CART,36)\
	X(WSU_AIM_HIGHER,37)\
	X(LEADERSHIP_IN_CONTROL,38)\
	X(NUM_1_SEED,39)\
	X(INCREDIBLE_PLAY,40)\
	X(PEOPLES_CHOICE_ANIMATION,41)\
	X(VISUALIZATION_RISING_STAR,42)\
	X(BEST_OFFENSIVE_ROUND,43)\
	X(BEST_PLAY_OF_THE_DAY,44)\
	X(FEATHERWEIGHT_IN_THE_FINALS,45)\
	X(MOST_PHOTOGENIC,46)\
	X(OUTSTANDING_DEFENSE,47)\
	X(POWER_TO_SIMPLIFY,48)\
	X(AGAINST_ALL_ODDS,49)\
	X(RISING_STAR,50)\
	X(CHAIRMANS_HONORABLE_MENTION,51)\
	X(CONTENT_COMMUNICATION_HONORABLE_MENTION,52)\
	X(TECHNICAL_EXECUTION_HONORABLE_MENTION,53)\
	X(REALIZATION,54)\
	X(REALIZATION_HONORABLE_MENTION,55)\
	X(DESIGN_YOUR_FUTURE,56)\
	X(DESIGN_YOUR_FUTURE_HONORABLE_MENTION,57)\
	X(SPECIAL_RECOGNITION_CHARACTER_ANIMATION,58)\
	X(HIGH_SCORE,59)\
	X(TEACHER_PIONEER,60)\
	X(BEST_CRAFTSMANSHIP,61)\
	X(BEST_DEFENSIVE_MATCH,62)\
	X(PLAY_OF_THE_DAY,63)\
	X(PROGRAMMING,64)\
	X(PROFESSIONALISM,65)\
	X(GOLDEN_CORNDOG,66)\
	X(MOST_IMPROVED_TEAM,67)\
	X(WILDCARD,68)\
	X(CHAIRMANS_FINALIST,69)\
	X(OTHER,70)\
	X(AUTONOMOUS,71)\
	X(INNOVATION_CHALLENGE_SEMI_FINALIST,72)\
	X(ROOKIE_GAME_CHANGER,73)\
	X(SKILLS_COMPETITION_WINNER,74)\
	X(SKILLS_COMPETITION_FINALIST,75)\
	X(ROOKIE_DESIGN,76)\
	X(ENGINEERING_DESIGN,77)\
	X(DESIGNERS,78)\
	X(CONCEPT,79)\
	X(GAME_DESIGN_CHALLENGE_WINNER,80)\
	X(GAME_DESIGN_CHALLENGE_FINALIST,81)\
	X(SUSTAINABILITY,82)

enum class Award_type{
	#define X(A,B) A,
	TBA_AWARD_TYPES(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Award_type);
Award_type decode(JSON const&,const Award_type *);
Award_type decode(JSON_value,const Award_type *);

#define TBA_AWARD(X)\
	X(std::string,name)\
	X(Award_type,award_type)\
	X(Event_key,event_key)\
	X(std::vector<Award_Recipient>,recipient_list)\
	X(Year,year)

TBA_MAKE_INST(Award,TBA_AWARD)

#define TBA_RECORD(X)\
	X(unsigned,losses)\
	X(unsigned,wins)\
	X(unsigned,ties)

TBA_MAKE_INST(Record,TBA_RECORD)

#define TBA_RANKING(X)\
	X(std::optional<unsigned>,dq)\
	X(unsigned,matches_played)\
	X(std::optional<double>,qual_average)\
	X(std::optional<unsigned>,rank)\
	X(std::optional<Record>,record)\
	X(std::optional<std::vector<double>>,sort_orders)\
	X(Team_key,team_key)

TBA_MAKE_INST(Ranking,TBA_RANKING)

#define TBA_SORT_ORDER(X)\
	X(std::string,name)\
	X(int,precision)

TBA_MAKE_INST(Sort_order,TBA_SORT_ORDER)

#define TBA_TEAM_EVENT_STATUS_RANK(X)\
	X(int,num_teams)\
	X(Ranking,ranking)\
	X(std::optional<std::vector<Sort_order>>,sort_order_info)\
	X(std::string,status)

TBA_MAKE_INST(Team_Event_Status_rank,TBA_TEAM_EVENT_STATUS_RANK)

#define TBA_TEAM_EVENT_STATUS_ALLIANCE_BACKUP(X)\
	X(std::string,out)\
	X(std::string,in)

TBA_MAKE_INST(Team_Event_Status_alliance_backup,TBA_TEAM_EVENT_STATUS_ALLIANCE_BACKUP)

class Pick_order{
	//docs say: 0-2; 0=captain
	//note that doc says 0-2, but actually returns 3 sometimes, which makes sense given the recent championship formats.
	//-1 can also be returned; seems to indicate being pulled in as a backup.
	int i;

	public:
	explicit Pick_order(int);
	int get()const;

	auto operator<=>(Pick_order const&)const=default;
};

std::ostream& operator<<(std::ostream&,Pick_order);
Pick_order decode(JSON const&,const Pick_order *);
Pick_order decode(JSON_value,const Pick_order *);

#define TBA_TEAM_EVENT_STATUS_ALLIANCE(X)\
	X(std::string,name)\
	X(int,number)\
	X(std::optional<Team_Event_Status_alliance_backup>,backup)\
	X(Pick_order,pick)

TBA_MAKE_INST(Team_Event_Status_alliance,TBA_TEAM_EVENT_STATUS_ALLIANCE)

#define TBA_PLAYOFF_STATUS(X) X(won) X(eliminated) X(playing)

enum class Playoff_status{
	#define X(A) A,
	TBA_PLAYOFF_STATUS(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Playoff_status);

Playoff_status decode(JSON const&,const Playoff_status*);
Playoff_status decode(JSON_value,const Playoff_status*);

#define TBA_TEAM_EVENT_STATUS_PLAYOFF(X)\
	X(Playoff_level,level)\
	X(std::optional<Record>,current_level_record)\
	X(std::optional<Record>,record)\
	X(Playoff_status,status)\
	X(std::optional<double>,playoff_average)
//docs say that playoff_average is an int; it isn't though.

TBA_MAKE_INST(Team_Event_Status_playoff,TBA_TEAM_EVENT_STATUS_PLAYOFF)

#define TBA_TEAM_STATUS(X)\
	X(std::optional<Team_Event_Status_rank>,qual)\
	X(std::optional<Team_Event_Status_alliance>,alliance)\
	X(std::optional<Team_Event_Status_playoff>,playoff)\
	X(std::string,alliance_status_str)\
	X(std::string,playoff_status_str)\
	X(std::string,overall_status_str)

TBA_MAKE_INST(Team_Event_Status,TBA_TEAM_STATUS)

#define TBA_EVENT_RANKING(X)\
	X(std::optional<std::vector<Ranking>>,rankings)\
	X(std::optional<std::vector<Sort_order>>,sort_order_info)

TBA_MAKE_INST(Event_ranking,TBA_EVENT_RANKING)

//not sure why "elim_points" shows up as double sometimes; should be integer.
#define TBA_POINTS(X)\
	X(int,alliance_points)\
	X(int,award_points)\
	X(int,qual_points)\
	X(double,elim_points)\
	X(double,total)

TBA_MAKE_INST(Points,TBA_POINTS)

#define TBA_TIEBREAKER(X)\
	X(std::vector<int>,highest_qual_scores)\
	X(int,qual_wins)

TBA_MAKE_INST(Tiebreaker,TBA_TIEBREAKER)

#define TBA_EVENT_DISTRICT_POINTS(X)\
	X(std::map<TBA_SINGLE_ARG(Team_key,Points)>,points)\
	X(std::map<TBA_SINGLE_ARG(Team_key,Tiebreaker)>,tiebreakers)

TBA_MAKE_INST(Event_District_Points,TBA_EVENT_DISTRICT_POINTS)

class Match_key{
	std::string s;

	public:
	explicit Match_key(std::string);
	std::string const& get()const;

	auto operator<=>(Match_key const&)const=default;
};

std::ostream& operator<<(std::ostream&,Match_key const&);
Match_key decode(JSON const&,const Match_key*);
Match_key decode(JSON_value,Match_key const*);

#define TBA_HIGH_SCORE(X)\
	X(int,high_score)\
	X(Match_key,match_key)\
	X(std::string,match_name)

struct High_score{
	TBA_HIGH_SCORE(TBA_INST)

	auto operator<=>(High_score const&)const=default;
};

std::ostream& operator<<(std::ostream&,High_score const&);
High_score decode(JSON const&,const High_score*);
High_score decode(JSON_value,const High_score*);

using D3=std::array<double,3>;
using I3=std::array<int,3>;
using IID=std::tuple<int,int,double>;

#define TBA_EVENT_INSIGHTS_2016_DETAIL(X)\
	X(IID,LowBar)\
	X(IID,A_ChevalDeFrise)\
	X(IID,A_Portcullis)\
	X(IID,B_Ramparts)\
	X(IID,B_Moat)\
	X(IID,C_SallyPort)\
	X(IID,C_Drawbridge)\
	X(IID,D_RoughTerrain)\
	X(IID,D_RockWall)\
	X(double,average_high_goals)\
	X(double,average_low_goals)\
	X(IID,breaches)\
	X(IID,scales)\
	X(IID,challenges)\
	X(IID,captures)\
	X(double,average_win_score)\
	X(double,average_score)\
	X(double,average_auto_score)\
	X(double,average_crossing_score)\
	X(double,average_boulder_score)\
	X(double,average_tower_score)\
	X(double,average_foul_score)\
	X(High_score,high_score)

TBA_MAKE_INST(Event_Insights_2016_Detail,TBA_EVENT_INSIGHTS_2016_DETAIL)

#define TBA_EVENT_INSIGHTS_2016(X)\
	X(std::optional<Event_Insights_2016_Detail>,qual)\
	X(std::optional<Event_Insights_2016_Detail>,playoff)

TBA_MAKE_INST(Event_Insights_2016,TBA_EVENT_INSIGHTS_2016)

#define TBA_EVENT_INSIGHTS_2017_DETAIL(X)\
	X(double,average_foul_score)\
	X(double,average_fuel_points)\
	X(double,average_fuel_points_auto)\
	X(double,average_fuel_points_teleop)\
	X(double,average_high_goals)\
	X(double,average_high_goals_auto)\
	X(double,average_high_goals_teleop)\
	X(double,average_low_goals)\
	X(double,average_low_goals_auto)\
	X(double,average_low_goals_teleop)\
	X(double,average_mobility_points_auto)\
	X(double,average_points_auto)\
	X(double,average_points_teleop)\
	X(double,average_rotor_points)\
	X(double,average_rotor_points_auto)\
	X(double,average_score)\
	X(double,average_takeoff_points_teleop)\
	X(double,average_win_margin)\
	X(double,average_win_score)\
	X(High_score,high_kpa)\
	X(High_score,high_score)\
	X(IID,kpa_achieved)\
	X(IID,mobility_counts)\
	X(IID,rotor_1_engaged)\
	X(IID,rotor_1_engaged_auto)\
	X(IID,rotor_2_engaged)\
	X(IID,rotor_2_engaged_auto)\
	X(IID,rotor_3_engaged)\
	X(IID,rotor_4_engaged)\
	X(IID,takeoff_counts)

TBA_MAKE_INST(Event_Insights_2017_Detail,TBA_EVENT_INSIGHTS_2017_DETAIL)

#define TBA_EVENT_INSIGHTS_2017(X)\
	X(std::optional<Event_Insights_2017_Detail>,qual)\
	X(std::optional<Event_Insights_2017_Detail>,playoff)

TBA_MAKE_INST(Event_Insights_2017,TBA_EVENT_INSIGHTS_2017)

using ISS=std::tuple<int,std::string,std::string>;

#define TBA_EVENT_INSIGHTS_2018_DETAIL(X)\
	X(IID,auto_quest_achieved)\
	X(double,average_boost_played)\
	X(double,average_endgame_points)\
	X(double,average_force_played)\
	X(double,average_foul_score)\
	X(double,average_points_auto)\
	X(double,average_points_teleop)\
	X(double,average_run_points_auto)\
	X(double,average_scale_ownership_points)\
	X(double,average_scale_ownership_points_auto)\
	X(double,average_scale_ownership_points_teleop)\
	X(double,average_score)\
	X(double,average_switch_ownership_points)\
	X(double,average_switch_ownership_points_auto)\
	X(double,average_switch_ownership_points_teleop)\
	X(double,average_vault_points)\
	X(double,average_win_margin)\
	X(double,average_win_score)\
	X(IID,boost_played_counts)\
	X(IID,climb_counts)\
	X(IID,face_the_boss_achieved)\
	X(IID,force_played_counts)\
	X(ISS,high_score)\
	X(IID,levitate_played_counts)\
	X(IID,run_counts_auto)\
	X(double,scale_neutral_percentage)\
	X(double,scale_neutral_percentage_auto)\
	X(double,scale_neutral_percentage_teleop)\
	X(IID,switch_owned_counts_auto)\
	X(IID,unicorn_matches)\
	X(double,winning_opp_switch_denial_percentage_teleop)\
	X(double,winning_own_switch_ownership_percentage)\
	X(double,winning_own_switch_ownership_percentage_auto)\
	X(double,winning_own_switch_ownership_percentage_teleop)\
	X(double,winning_scale_ownership_percentage)\
	X(double,winning_scale_ownership_percentage_auto)\
	X(double,winning_scale_ownership_percentage_teleop)

TBA_MAKE_INST(Event_Insights_2018_Detail,TBA_EVENT_INSIGHTS_2018_DETAIL)

#define TBA_EVENT_INSIGHTS_2018(X)\
	X(std::optional<Event_Insights_2018_Detail>,playoff)\
	X(std::optional<Event_Insights_2018_Detail>,qual)

TBA_MAKE_INST(Event_Insights_2018,TBA_EVENT_INSIGHTS_2018)

using D8=std::array<double,8>;
using D6=std::array<double,6>;

#define TBA_AVERAGE_ROCKET_COUNT(X)\
	X(double,lowLeftFar)\
	X(double,lowLeftNear)\
	X(double,lowRightNear)\
	X(double,midLeftFar)\
	X(double,midLeftNear)\
	X(double,midRightNear)\
	X(double,midRightFar)\
	X(double,topLeftFar)\
	X(double,topLeftNear)\
	X(double,topRightFar)\
	X(double,topRightNear)

TBA_MAKE_INST(Average_rocket_count,TBA_AVERAGE_ROCKET_COUNT)

#define TBA_EVENT_INSIGHTS_2019_DETAIL(X)\
	X(double,average_cargo_points)\
	X(D8,average_cargo_ship_cargo_count)\
	X(D6,average_cargo_ship_cargo_preload_count)\
	X(D8,average_cargo_ship_hatch_panel_count)\
	X(D6,average_cargo_ship_hatch_panel_preload_count)\
	X(double,average_foul_score)\
	X(double,average_hab_climb_teleop)\
	X(Average_rocket_count,average_rocket_cargo_count)\
	X(Average_rocket_count,average_rocket_hatch_panel_count)\
	X(double,average_sandstorm_bonus_auto)\
	X(double,average_score)\
	X(double,average_win_margin)\
	X(double,average_win_score)\
	X(IID,climb_rp_achieved)\
	X(IID,complete_1_rocket_count)\
	X(IID,complete_2_rockets_count)\
	X(IID,cross_hab_line_count)\
	X(IID,cross_hab_line_sandstorm_count)\
	X(ISS,high_score)\
	X(IID,level1_climb_count)\
	X(IID,level2_climb_count)\
	X(IID,level3_climb_count)\
	X(IID,rocket_rp_achieved)\
	X(IID,unicorn_matches)

TBA_MAKE_INST(Event_Insights_2019_Detail,TBA_EVENT_INSIGHTS_2019_DETAIL)

#define TBA_EVENT_INSIGHTS_2019(X)\
	X(std::optional<Event_Insights_2019_Detail>,playoff)\
	X(std::optional<Event_Insights_2019_Detail>,qual)

TBA_MAKE_INST(Event_Insights_2019,TBA_EVENT_INSIGHTS_2019)

#define TBA_EVENT_INSIGHTS_2020_DETAIL(X)\
	X(IID,achieve_stage1_count)\
	X(IID,achieve_stage2_count)\
	X(IID,achieve_stage3_count)\
	X(double,average_cell_count)\
	X(double,average_cell_count_auto)\
	X(double,average_cell_count_bottom)\
	X(double,average_cell_count_bottom_auto)\
	X(double,average_cell_count_bottom_teleop)\
	X(double,average_cell_count_inner)\
	X(double,average_cell_count_inner_auto)\
	X(double,average_cell_count_inner_teleop)\
	X(double,average_cell_count_outer)\
	X(double,average_cell_count_outer_auto)\
	X(double,average_cell_count_outer_teleop)\
	X(double,average_cell_points_auto)\
	X(double,average_cell_points_teleop)\
	X(double,average_cell_score)\
	X(double,average_control_panel_points)\
	X(double,average_endgame_points)\
	X(double,average_foul_score)\
	X(double,average_init_line_points_auto)\
	X(double,average_num_robots_hanging)\
	X(double,average_points_auto)\
	X(double,average_points_teleop)\
	X(double,average_score)\
	X(double,average_win_margin)\
	X(double,average_win_score)\
	X(IID,exit_init_line_count)\
	X(IID,generator_energized_rp_achieved)\
	X(IID,generator_level_count)\
	X(IID,generator_operational_rp_achieved)\
	X(IID,hang_count)\
	X(ISS,high_score)\
	X(IID,park_count)\
	X(IID,unicorn_matches)

TBA_MAKE_INST(Event_Insights_2020_Detail,TBA_EVENT_INSIGHTS_2020_DETAIL)

#define TBA_EVENT_INSIGHTS_2020(X)\
	X(std::optional<Event_Insights_2020_Detail>,playoff)\
	X(std::optional<Event_Insights_2020_Detail>,qual)

TBA_MAKE_INST(Event_Insights_2020,TBA_EVENT_INSIGHTS_2020)

#define TBA_EVENT_INSIGHTS_2022_DETAIL(X)\
	X(double,average_cargo_count)\
	X(double,average_cargo_count_auto)\
	X(double,average_cargo_count_teleop)\
	X(double,average_cargo_points)\
	X(double,average_cargo_points_auto)\
	X(double,average_cargo_points_teleop)\
	X(double,average_endgame_points)\
	X(double,average_foul_score)\
	X(double,average_lower_cargo_count)\
	X(double,average_lower_cargo_count_auto)\
	X(double,average_lower_cargo_count_teleop)\
	X(double,average_points_auto)\
	X(double,average_points_teleop)\
	X(double,average_score)\
	X(double,average_taxi_points)\
	X(double,average_upper_cargo_count)\
	X(double,average_upper_cargo_count_auto)\
	X(double,average_upper_cargo_count_teleop)\
	X(double,average_win_margin)\
	X(double,average_win_score)\
	X(IID,cargo_bonus_rp)\
	X(IID,hangar_bonus_rp)\
	X(IID,high_climb_count)\
	X(High_score,high_score)\
	X(IID,low_climb_count)\
	X(IID,mid_climb_count)\
	X(IID,quintet_count)\
	X(IID,taxi_count)\
	X(IID,traversal_climb_count)\
	X(IID,unicorn_matches)

TBA_MAKE_INST(Event_Insights_2022_Detail,TBA_EVENT_INSIGHTS_2022_DETAIL)

#define TBA_EVENT_INSIGHTS_2022(X)\
	X(Event_Insights_2022_Detail,playoff)\
	X(Event_Insights_2022_Detail,qual)

TBA_MAKE_INST(Event_Insights_2022,TBA_EVENT_INSIGHTS_2022)

#define TBA_EVENT_INSIGHTS_2023_DETAIL(X)\
	X(IID,activation_bonus_rp)\
	X(IID,auto_docked_count)\
	X(IID,auto_engaged_count)\
	X(double,average_charge_station_points_auto)\
	X(double,average_charge_station_points_teleop)\
	X(double,average_foul_score)\
	X(double,average_link_points)\
	X(double,average_mobility_points)\
	X(double,average_park_points)\
	X(double,average_piece_points_auto)\
	X(double,average_piece_points_teleop)\
	X(double,average_points_auto)\
	X(double,average_points_teleop)\
	X(double,average_score)\
	X(double,average_win_margin)\
	X(double,average_win_score)\
	X(IID,coopertition)\
	X(High_score,high_score)\
	X(IID,mobility_count)\
	X(IID,sustainability_bonus_rp)\
	X(IID,unicorn_matches)

TBA_MAKE_INST(Event_Insights_2023_Detail,TBA_EVENT_INSIGHTS_2023_DETAIL)

#define TBA_EVENT_INSIGHTS_2023(X)\
	X(std::optional<Event_Insights_2023_Detail>,playoff)\
	X(Event_Insights_2023_Detail,qual)

TBA_MAKE_INST(Event_Insights_2023,TBA_EVENT_INSIGHTS_2023)

using Event_insights=std::variant<
	std::nullptr_t,
	Event_Insights_2017,
	Event_Insights_2016,
	Event_Insights_2018,
	Event_Insights_2019,
	Event_Insights_2020,
	Event_Insights_2022,
	Event_Insights_2023
>;

//These come back as null rather than empty lists for events that don't have these calculated yet.
#define TBA_EVENT_OPRS(X)\
	X(std::optional<std::map<TBA_SINGLE_ARG(Team_key,double)>>,oprs)\
	X(std::optional<std::map<TBA_SINGLE_ARG(Team_key,double)>>,dprs)\
	X(std::optional<std::map<TBA_SINGLE_ARG(Team_key,double)>>,ccwms)

TBA_MAKE_INST(Event_OPRs,TBA_EVENT_OPRS)

using WLT_Record=Record;

#define TBA_ELIMINATION_ALLIANCE_STATUS(X)\
	X(std::optional<WLT_Record>,current_level_record)\
	X(std::string,level)\
	X(std::optional<double>,playoff_average)\
	X(std::optional<WLT_Record>,record)\
	X(std::optional<std::string>,status)

TBA_MAKE_INST(Elimination_Alliance_status,TBA_ELIMINATION_ALLIANCE_STATUS)

struct Unknown{
	auto operator<=>(Unknown const&)const=default;
};

std::ostream& operator<<(std::ostream&,Unknown);
Unknown decode(JSON const&,const Unknown *);
Unknown decode(JSON_value,const Unknown *);

using M_Elimination_Alliance_status=std::variant<Unknown,Elimination_Alliance_status>;

#define TBA_ELIMINATION_ALLIANCE(X)\
	X(std::optional<std::string>,name)\
	X(std::optional<Team_Event_Status_alliance_backup>,backup)\
	X(std::vector<Team_key>,declines)\
	X(std::vector<Team_key>,picks)\
	X(std::optional<M_Elimination_Alliance_status>,status)

TBA_MAKE_INST(Elimination_Alliance,TBA_ELIMINATION_ALLIANCE)

#define TBA_YEAR_INFO(X)\
	X(std::string,abbreviation)\
	X(std::string,display_name)\
	X(District_key,key)\
	X(Year,year)

TBA_MAKE_INST(Year_info,TBA_YEAR_INFO)

//start stuff for predictions, which is subject to change per the doc.
#define TBA_BRIER_SCORES(X)\
	X(std::optional<double>,gears)\
	X(std::optional<double>,pressure)\
	X(std::optional<double>,win_loss)

TBA_MAKE_INST(Brier_scores,TBA_BRIER_SCORES)

#define TBA_MATCH_PREDICTION_SET(X)\
	X(Brier_scores,brier_scores)\
	X(std::optional<double>,err_mean)\
	X(std::optional<double>,err_var)\
	X(std::optional<double>,wl_accuracy)\
	X(std::optional<double>,wl_accuracy_75)

TBA_MAKE_INST(Match_prediction_set,TBA_MATCH_PREDICTION_SET)

#define TBA_MATCH_PREDICTION_STATS(X)\
	X(std::optional<Match_prediction_set>,playoff)\
	X(std::optional<Match_prediction_set>,qual)

TBA_MAKE_INST(Match_prediction_stats,TBA_MATCH_PREDICTION_STATS)

enum class Alliance_color{RED,BLUE};

std::ostream& operator<<(std::ostream&,Alliance_color);

Alliance_color decode(JSON const&,const Alliance_color *);
Alliance_color decode(JSON_value,const Alliance_color *);

#define TBA_ALLIANCE_PREDICTION(X)\
	X(std::optional<double>,gears)\
	X(std::optional<double>,gears_var)\
	X(std::optional<double>,pressure)\
	X(std::optional<double>,pressure_var)\
	X(std::optional<double>,prob_gears)\
	X(std::optional<double>,prob_pressure)\
	X(double,score)\
	X(double,score_var)
	
TBA_MAKE_INST(Alliance_prediction,TBA_ALLIANCE_PREDICTION)

#define TBA_MATCH_PREDICTION(X)\
	X(Alliance_prediction,blue)\
	X(double,prob)\
	X(Alliance_prediction,red)\
	X(Alliance_color,winning_alliance)

TBA_MAKE_INST(Match_prediction,TBA_MATCH_PREDICTION)

using Ind_match_prediction_set=std::map<Match_key,Match_prediction>;

#define TBA_PER_MATCH_PREDICTIONS(X)\
	X(std::optional<Ind_match_prediction_set>,playoff)\
	X(std::optional<Ind_match_prediction_set>,qual)

TBA_MAKE_INST(Per_match_predictions,TBA_PER_MATCH_PREDICTIONS)

#define TBA_RANKING_PREDICTION_STATS(X)\
	X(std::optional<Match_key>,last_match_played)

TBA_MAKE_INST(Ranking_prediction_stats,TBA_RANKING_PREDICTION_STATS)

using Ranking_prediction=std::pair<Team_key,std::tuple<double,int,double,int,double,int,int>>;

#define TBA_MEAN_VAR(X)\
	X(std::map<TBA_SINGLE_ARG(Team_key,double)>,mean)\
	X(std::map<TBA_SINGLE_ARG(Team_key,double)>,var)

TBA_MAKE_INST(Mean_var,TBA_MEAN_VAR)

#define TBA_STAT_MEAN_VAR_SET(X)\
	X(std::optional<Mean_var>,gears)\
	X(std::optional<Mean_var>,pressure)\
	X(std::optional<Mean_var>,score)\

TBA_MAKE_INST(Stat_mean_var_set,TBA_STAT_MEAN_VAR_SET)

#define TBA_STAT_MEAN_VARS(X)\
	X(Stat_mean_var_set,playoff)\
	X(Stat_mean_var_set,qual)

TBA_MAKE_INST(Stat_mean_vars,TBA_STAT_MEAN_VARS)

#define TBA_EVENT_PREDICTIONS(X)\
	X(std::optional<Match_prediction_stats>,match_prediction_stats)\
	X(std::optional<Per_match_predictions>,match_predictions)\
	X(std::optional<Ranking_prediction_stats>,ranking_prediction_stats)\
	X(std::optional<std::vector<Ranking_prediction>>,ranking_predictions)\
	X(std::optional<Stat_mean_vars>,stat_mean_vars)

TBA_MAKE_INST(Event_predictions,TBA_EVENT_PREDICTIONS)

#define TBA_ZEBRA_TEAM(X)\
	X(Team_key,team_key)\
	X(std::vector<std::optional<double>>,xs)\
	X(std::vector<std::optional<double>>,ys)

TBA_MAKE_INST(Zebra_team,TBA_ZEBRA_TEAM)

#define TBA_ZEBRA_ALLIANCES(X)\
	X(std::vector<Zebra_team>,red)\
	X(std::vector<Zebra_team>,blue)

TBA_MAKE_INST(Zebra_alliances,TBA_ZEBRA_ALLIANCES)

#define TBA_ZEBRA(X)\
	X(Match_key,key)\
	X(std::vector<double>,times)\
	X(Zebra_alliances,alliances)

TBA_MAKE_INST(Zebra,TBA_ZEBRA)

}

#endif
