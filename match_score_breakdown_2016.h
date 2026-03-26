#ifndef TBA_MATCH_SCORE_BREAKDOWN_2016_H
#define TBA_MATCH_SCORE_BREAKDOWN_2016_H

namespace tba{

#define TBA_LIST(A) A,

#define TBA_MAKE_ENUM(NAME,ITEMS)\
	enum class NAME:char{ITEMS(TBA_LIST)};\
	NAME decode(JSON_value,NAME const*);\
	std::optional<NAME> maybe_decode(JSON_value,NAME const*);\
	std::ostream& operator<<(std::ostream&,NAME);\
	NAME rand(NAME const*);\

#define TBA_STR_OPT_INST(A) A,

#define TBA_STR_OPTIONS(OPTIONS)\
	enum class NAME:char{ OPTIONS(TBA_STR_OPT_INST) };\
	std::ostream& operator<<(std::ostream&,NAME);\
	NAME decode(JSON_value,const NAME *);\
	std::optional<NAME> maybe_decode(JSON_value,NAME const*);\
	NAME rand(NAME const*);\

#define TBA_AUTO_2016_TYPES(X) X(Crossed) X(Reached) X(None) X(Unknown)

#define NAME Auto_2016
TBA_STR_OPTIONS(TBA_AUTO_2016_TYPES)
#undef NAME

#define TBA_TOWER(X)\
	X(Both)\
	X(Challenged)\
	X(None)\
	X(Scaled)\
	X(Unknown)

TBA_MAKE_ENUM(Tower,TBA_TOWER)

#define TBA_DEFENSE(X)\
	X(A_ChevalDeFrise)\
	X(A_Portcullis)\
	X(B_Moat)\
	X(B_Ramparts)\
	X(C_Drawbridge)\
	X(C_SallyPort)\
	X(D_RockWall)\
	X(D_RoughTerrain)\
	X(NotSpecified)

TBA_MAKE_ENUM(Defense,TBA_DEFENSE)

/*	X(int,autoBoulderPoints)\
	X(int,breachPoints)\
	X(int,tba_rpEarned)\*/

#define TBA_MATCH_SCORE_BREAKDOWN_2016_ALLIANCE(X)\
	X(u8,autoPoints)\
	X(std::optional<u8>,teleopPoints)\
	X(std::optional<short>,breechPoints)\
	X(u8,foulPoints)\
	X(u8,capturePoints)\
	X(std::optional<short>,adjustPoints)\
	X(short,totalPoints)\
	X(std::optional<Auto_2016>,robot1Auto)\
	X(std::optional<Auto_2016>,robot2Auto)\
	X(std::optional<Auto_2016>,robot3Auto)\
	X(u8,autoReachPoints)\
	X(u8,autoCrossingPoints)\
	X(std::optional<u8>,autoBouldersLow)\
	X(std::optional<u8>,autoBouldersHigh)\
	X(u8,teleopCrossingPoints)\
	X(u8,teleopBouldersLow)\
	X(u8,teleopBouldersHigh)\
	X(u8,teleopBoulderPoints)\
	X(bool,teleopDefensesBreached)\
	X(u8,teleopChallengePoints)\
	X(u8,teleopScalePoints)\
	X(bool,teleopTowerCaptured)\
	X(std::optional<Tower>,towerFaceA)\
	X(std::optional<Tower>,towerFaceB)\
	X(std::optional<Tower>,towerFaceC)\
	X(std::optional<short>,towerEndStrength)\
	X(std::optional<u8>,techFoulCount)\
	X(std::optional<u8>,foulCount)\
	X(Defense,position2)\
	X(Defense,position3)\
	X(Defense,position4)\
	X(Defense,position5)\
	X(u8,position1crossings)\
	X(u8,position2crossings)\
	X(u8,position3crossings)\
	X(u8,position4crossings)\
	X(u8,position5crossings)\

TBA_MAKE_INST(Match_Score_Breakdown_2016_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2016_ALLIANCE)

#define TBA_MATCH_SCORE_BREAKDOWN_2016(X)\
	X(Match_Score_Breakdown_2016_Alliance,blue)\
	X(Match_Score_Breakdown_2016_Alliance,red)

TBA_MAKE_INST(Match_Score_Breakdown_2016,TBA_MATCH_SCORE_BREAKDOWN_2016)

}

#endif
