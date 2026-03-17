#ifndef TBA_MATCH_H
#define TBA_MATCH_H

#include "macro.h"
#include<optional>
#include "int_limited.h"
#include "simdjson.h"
#include "match_key.h"
#include "data.h"//for Competition_level

namespace tba{

using u8=Int_limited<0,255>;

#define TBA_LIST(A) A,

#define TBA_MAKE_ENUM(NAME,ITEMS)\
	enum class NAME:char{ITEMS(TBA_LIST)};\
	NAME decode(JSON_value,NAME const*);\
	std::optional<NAME> maybe_decode(JSON_value,NAME const*);\
	std::ostream& operator<<(std::ostream&,NAME);\
	NAME rand(NAME const*);\

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
	X(std::optional<u8>,auto_points)\
	X(std::optional<short>,teleop_points)\
	X(std::optional<u8>,container_points)\
	X(std::optional<u8>,tote_points)\
	X(std::optional<u8>,litter_points)\
	X(std::optional<u8>,foul_points)\
	X(std::optional<short>,adjust_points)\
	X(std::optional<short>,total_points)\
	X(std::optional<u8>,foul_count)\
	X(std::optional<short>,tote_count_far)\
	X(std::optional<u8>,tote_count_near)\
	X(std::optional<bool>,tote_set)\
	X(std::optional<bool>,tote_stack)\
	X(std::optional<u8>,container_count_level1)\
	X(std::optional<u8>,container_count_level2)\
	X(std::optional<u8>,container_count_level3)\
	X(std::optional<u8>,container_count_level4)\
	X(std::optional<u8>,container_count_level5)\
	X(std::optional<u8>,container_count_level6)\
	X(std::optional<bool>,container_set)\
	X(std::optional<u8>,litter_count_container)\
	X(std::optional<u8>,litter_count_landfill)\
	X(std::optional<u8>,litter_count_unprocessed)\
	X(std::optional<bool>,robot_set)

TBA_MAKE_INST(Match_Score_Breakdown_2015_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2015_ALLIANCE)

//docs do not include "Set"
#define TBA_COOPERTITION_TYPES(X)\
	X(None) X(Unknown) X(Stack) X(Set)

enum class Coopertition:char{
	#define X(A) A,
	TBA_COOPERTITION_TYPES(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Coopertition);
Coopertition decode(JSON_value,const Coopertition*);
std::optional<Coopertition> maybe_decode(JSON_value,Coopertition const*);
Coopertition rand(Coopertition const*);

#define TBA_MATCH_SCORE_BREAKDOWN_2015(X)\
	X(Match_Score_Breakdown_2015_Alliance,blue)\
	X(Match_Score_Breakdown_2015_Alliance,red)\
	X(std::optional<Coopertition>,coopertition)\
	X(std::optional<u8>,coopertition_points)

TBA_MAKE_INST(Match_Score_Breakdown_2015,TBA_MATCH_SCORE_BREAKDOWN_2015)

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

#define TBA_AUTO_2017(X) X(Unknown) X(Mobility) X(None)
#define NAME Auto_2017
TBA_STR_OPTIONS(TBA_AUTO_2017)
#undef NAME

#define TBA_TOUCHPAD(X) X(None) X(ReadyForTakeoff)
TBA_MAKE_ENUM(Touchpad,TBA_TOUCHPAD)

#define TBA_MATCH_SCORE_BREAKDOWN_2017_ALLIANCE(X)\
	X(u8,autoPoints)\
	X(short,teleopPoints)\
	X(short,foulPoints)\
	X(std::optional<short>,adjustPoints)\
	X(short,totalPoints)\
	X(std::optional<Auto_2017>,robot1Auto)\
	X(std::optional<Auto_2017>,robot2Auto)\
	X(std::optional<Auto_2017>,robot3Auto)\
	X(bool,rotor1Auto)\
	X(bool,rotor2Auto)\
	X(short,autoFuelLow)\
	X(u8,autoFuelHigh)\
	X(u8,autoMobilityPoints)\
	X(u8,teleopFuelPoints)\
	X(short,teleopFuelLow)\
	X(u8,teleopFuelHigh)\
	X(u8,teleopRotorPoints)\
	X(std::optional<bool>,kPaRankingPointArchieved)\
	X(short,teleopTakeoffPoints)\
	X(u8,kPaBonusPoints)\
	X(u8,rotorBonusPoints)\
	X(bool,rotor1Engaged)\
	X(bool,rotor2Engaged)\
	X(bool,rotor3Engaged)\
	X(bool,rotor4Engaged)\
	X(bool,rotorRankingPointAchieved)\
	X(std::optional<u8>,techFoulCount)\
	X(std::optional<u8>,foulCount)\
	X(std::optional<Touchpad>,touchpadNear)\
	X(std::optional<Touchpad>,touchpadMiddle)\
	X(std::optional<Touchpad>,touchpadFar)

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
	X(short,assist,assist)\
	X(short,auto_pts,auto)\
	X(short,teleop_goal_and_foul,teleop_goal+foul)\
	X(short,truss_and_catch,truss+catch)

struct Match_Score_Breakdown_2014_Alliance{
	#define X(A,B,C) A B;
	TBA_MATCH_SCORE_BREAKDOWN_2014_ALLIANCE(X)
	#undef X

	auto operator<=>(Match_Score_Breakdown_2014_Alliance const&)const=default;
};

std::ostream& operator<<(std::ostream&,Match_Score_Breakdown_2014_Alliance const&);
Match_Score_Breakdown_2014_Alliance decode(JSON_value,const Match_Score_Breakdown_2014_Alliance*);
std::optional<Match_Score_Breakdown_2014_Alliance> maybe_decode(JSON_value,Match_Score_Breakdown_2014_Alliance const*);
Match_Score_Breakdown_2014_Alliance rand(Match_Score_Breakdown_2014_Alliance const*);

#define TBA_MATCH_SCORE_BREAKDOWN_2014(X)\
	X(Match_Score_Breakdown_2014_Alliance,blue)\
	X(Match_Score_Breakdown_2014_Alliance,red)

TBA_MAKE_INST(Match_Score_Breakdown_2014,TBA_MATCH_SCORE_BREAKDOWN_2014)

#define TBA_INIT_LINE_OPTIONS(X)\
	X(Exited)\
	X(None)

enum class Init_line:char{
	#define X(A) A,
	TBA_INIT_LINE_OPTIONS(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Init_line);
Init_line decode(JSON_value,Init_line const*);
std::optional<Init_line> maybe_decode(JSON_value,Init_line const*);
Init_line rand(Init_line const*);

#define TBA_ENDGAME_OPTIONS(X)\
	X(Park)\
	X(None)\
	X(Hang)

enum class Endgame:char{
	#define X(A) A,
	TBA_ENDGAME_OPTIONS(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Endgame);
Endgame decode(JSON_value,Endgame const*);
std::optional<Endgame> maybe_decode(JSON_value,Endgame const*);
Endgame rand(Endgame const*);

#define TBA_TARGET_COLOR_OPTIONS(X)\
	X(Unknown)\
	X(Blue)\
	X(Green)\
	X(Yellow)\
	X(Red)

enum class Target_color:char{
	#define X(A) A,
	TBA_TARGET_COLOR_OPTIONS(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Target_color);
Target_color decode(JSON_value,Target_color const*);
std::optional<Target_color> maybe_decode(JSON_value,Target_color const*);
Target_color rand(Target_color const*);

#define TBA_RUNG_LEVEL_OPTIONS(X)\
	X(NotLevel)\
	X(IsLevel)

enum class Rung_level:char{
	#define X(A) A,
	TBA_RUNG_LEVEL_OPTIONS(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Rung_level);
Rung_level decode(JSON_value,Rung_level const*);
std::optional<Rung_level> maybe_decode(JSON_value,Rung_level const*);
Rung_level rand(Rung_level const*);

#define TBA_MATCH_SCORE_BREAKDOWN_2020_ALLIANCE(X)\
	X(Init_line,initLineRobot1)\
	X(Endgame,endgameRobot1)\
	X(Init_line,initLineRobot2)\
	X(Endgame,endgameRobot2)\
	X(Init_line,initLineRobot3)\
	X(Endgame,endgameRobot3)\
	X(u8,autoCellsBottom)\
	X(u8,autoCellsOuter)\
	X(u8,autoCellsInner)\
	X(u8,teleopCellsBottom)\
	X(u8,teleopCellsOuter)\
	X(u8,teleopCellsInner)\
	X(bool,stage1Activated)\
	X(bool,stage2Activated)\
	X(bool,stage3Activated)\
	X(Target_color,stage3TargetColor)\
	X(Rung_level,endgameRungIsLevel)\
	X(u8,autoInitLinePoints)\
	X(u8,autoCellPoints)\
	X(u8,autoPoints)\
	X(u8,teleopCellPoints)\
	X(u8,controlPanelPoints)\
	X(u8,endgamePoints)\
	X(u8,teleopPoints)\
	X(bool,shieldOperationalRankingPoint)\
	X(bool,shieldEnergizedRankingPoint)\
	X(bool,tba_shieldEnergizedRankingPointFromFoul)\
	X(u8,tba_numRobotsHanging)\
	X(u8,foulCount)\
	X(u8,techFoulCount)\
	X(short,adjustPoints)\
	X(u8,foulPoints)\
	X(u8,rp)\
	X(short,totalPoints)

struct Match_Score_Breakdown_2020_Alliance{
	#define X(A,B) A B;
	TBA_MATCH_SCORE_BREAKDOWN_2020_ALLIANCE(X)
	#undef X

	auto operator<=>(Match_Score_Breakdown_2020_Alliance const&)const=default;
};

std::ostream& operator<<(std::ostream&,Match_Score_Breakdown_2020_Alliance const&);
Match_Score_Breakdown_2020_Alliance decode(JSON_value,const Match_Score_Breakdown_2020_Alliance*);
std::optional<Match_Score_Breakdown_2020_Alliance> maybe_decode(JSON_value,Match_Score_Breakdown_2020_Alliance const*);

#define TBA_MATCH_SCORE_BREAKDOWN_2020(X)\
	X(Match_Score_Breakdown_2020_Alliance,blue)\
	X(Match_Score_Breakdown_2020_Alliance,red)

TBA_MAKE_INST(Match_Score_Breakdown_2020,TBA_MATCH_SCORE_BREAKDOWN_2020)

enum class Yes_no:char{
	Yes,No //not all-caps to preserve being as documented in API
};

std::ostream& operator<<(std::ostream&,Yes_no);
Yes_no decode(JSON_value,Yes_no const*);
std::optional<Yes_no> maybe_decode(JSON_value,Yes_no const*);
Yes_no rand(Yes_no const*);

#define TBA_ENDGAME_2022_OPTIONS(X)\
	X(Traversal)\
	X(High)\
	X(Mid)\
	X(Low)\
	X(None)

enum class Endgame_2022:char{
	#define X(A) A,
	TBA_ENDGAME_2022_OPTIONS(X)
	#undef X
};

std::ostream& operator<<(std::ostream&,Endgame_2022);
Endgame_2022 decode(JSON_value,Endgame_2022 const*);
std::optional<Endgame_2022> maybe_decode(JSON_value,Endgame_2022 const*);
Endgame_2022 rand(Endgame_2022 const*);

#define TBA_MATCH_SCORE_BREAKDOWN_2022_ALLIANCE(X)\
	X(std::optional<Yes_no>,taxiRobot1)\
	X(std::optional<Endgame_2022>,endgameRobot1)\
	X(std::optional<Yes_no>,taxiRobot2)\
	X(std::optional<Endgame_2022>,endgameRobot2)\
	X(std::optional<Yes_no>,taxiRobot3)\
	X(std::optional<Endgame_2022>,endgameRobot3)\
	X(std::optional<u8>,autoCargoLowerNear)\
	X(std::optional<u8>,autoCargoLowerFar)\
	X(std::optional<u8>,autoCargoLowerBlue)\
	X(std::optional<u8>,autoCargoLowerRed)\
	X(std::optional<u8>,autoCargoUpperNear)\
	X(std::optional<u8>,autoCargoUpperFar)\
	X(std::optional<u8>,autoCargoUpperBlue)\
	X(std::optional<u8>,autoCargoUpperRed)\
	X(std::optional<u8>,autoCargoTotal)\
	X(std::optional<u8>,teleopCargoLowerNear)\
	X(std::optional<u8>,teleopCargoLowerFar)\
	X(std::optional<u8>,teleopCargoLowerBlue)\
	X(std::optional<u8>,teleopCargoLowerRed)\
	X(std::optional<u8>,teleopCargoUpperNear)\
	X(std::optional<u8>,teleopCargoUpperFar)\
	X(std::optional<u8>,teleopCargoUpperBlue)\
	X(std::optional<u8>,teleopCargoUpperRed)\
	X(std::optional<u8>,teleopCargoTotal)\
	X(std::optional<u8>,matchCargoTotal)\
	X(std::optional<u8>,autoTaxiPoints)\
	X(std::optional<u8>,autoCargoPoints)\
	X(std::optional<u8>,autoPoints)\
	X(std::optional<bool>,quintetAchieved)\
	X(std::optional<u8>,teleopCargoPoints)\
	X(std::optional<u8>,endgamePoints)\
	X(std::optional<bool>,cargoBonusRankingPoint)\
	X(std::optional<bool>,hangarBonusRankingPoint)\
	X(std::optional<u8>,foulCount)\
	X(std::optional<u8>,techFoulCount)\
	X(std::optional<short>,adjustPoints)\
	X(std::optional<u8>,foulPoints)\
	X(std::optional<u8>,rp)\
	X(std::optional<short>,totalPoints)

TBA_MAKE_INST(Match_Score_Breakdown_2022_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2022_ALLIANCE)

#define TBA_MATCH_SCORE_BREAKDOWN_2022(X)\
	X(Match_Score_Breakdown_2022_Alliance,blue)\
	X(Match_Score_Breakdown_2022_Alliance,red)

TBA_MAKE_INST(Match_Score_Breakdown_2022,TBA_MATCH_SCORE_BREAKDOWN_2022)

#define TBA_IGNORE(X)

TBA_MAKE_INST(Ignore,TBA_IGNORE)

//enum class Pole{NONE,CONE,CUBE};

#define TBA_BRIDGE_STATE(X)\
	X(Level)\
	X(NotLevel)

TBA_MAKE_ENUM(Bridge_state,TBA_BRIDGE_STATE)

#define TBA_AUTO_CHARGE_STATION(X) X(Docked) X(None)
TBA_MAKE_ENUM(Auto_charge_station,TBA_AUTO_CHARGE_STATION)

#define TBA_END_CHARGE_STATION(X)\
	X(Docked)\
	X(None)\
	X(Park)\
	X(Parked)
TBA_MAKE_ENUM(End_charge_station,TBA_END_CHARGE_STATION)

#define TBA_MATCH_SCORE_BREAKDOWN_2023_ALLIANCE(X)\
	X(std::optional<bool>,activationBonusAchieved)\
	X(std::optional<short>,adjustPoints)\
	X(std::optional<Bridge_state>,autoBridgeState)\
	X(std::optional<Auto_charge_station>,autoChargeStationRobot1)\
	X(std::optional<Auto_charge_station>,autoChargeStationRobot2)\
	X(std::optional<Auto_charge_station>,autoChargeStationRobot3)\
	X(std::optional<bool>,autoDocked)\
	X(Ignore,autoCommunity)\
	X(std::optional<u8>,autoGamePieceCount)\
	X(std::optional<u8>,autoGamePiecePoints)\
	X(u8,autoMobilityPoints)\
	X(Yes_no,mobilityRobot1)\
	X(Yes_no,mobilityRobot2)\
	X(Yes_no,mobilityRobot3)\
	X(u8,autoPoints)\
	X(std::optional<u8>,coopGamePieceCount)\
	X(std::optional<bool>,coopertitionCriteriaMet)\
	X(std::optional<Bridge_state>,endGameBridgeState)\
	X(std::optional<u8>,endGameChargeStationPoints)\
	X(std::optional<End_charge_station>,endGameChargeStationRobot1)\
	X(std::optional<End_charge_station>,endGameChargeStationRobot2)\
	X(std::optional<End_charge_station>,endGameChargeStationRobot3)\
	X(std::optional<u8>,endGameParkPoints)\
	X(std::optional<u8>,extraGamePieceCount)\
	X(u8,foulCount)\
	X(short,foulPoints)\
	X(u8,techFoulCount)\
	X(std::optional<u8>,linkPoints)\
	X(Ignore,links)\
	X(std::optional<bool>,sustainabilityBonusAchieved)\
	X(Ignore,teleopCommunity)\
	X(std::optional<u8>,teleopGamePieceCount)\
	X(std::optional<u8>,teleopGamePiecePoints)\
	X(std::optional<u8>,totalChargeStationPoints)\
	X(u8,teleopPoints)\
	X(u8,rp)\
	X(short,totalPoints)

TBA_MAKE_INST(Match_Score_Breakdown_2023_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2023_ALLIANCE)

#define TBA_MATCH_SCORE_BREAKDOWN_2023(X)\
	X(Match_Score_Breakdown_2023_Alliance,blue)\
	X(Match_Score_Breakdown_2023_Alliance,red)

TBA_MAKE_INST(Match_Score_Breakdown_2023,TBA_MATCH_SCORE_BREAKDOWN_2023)

#define TBA_ENDGAME_2024(X)\
	X(CenterStage)\
	X(None)\
	X(Parked)\
	X(StageLeft)\
	X(StageRight)

TBA_MAKE_ENUM(Endgame_2024,TBA_ENDGAME_2024)

#define TBA_MATCH_SCORE_BREAKDOWN_2024_ALLIANCE(X)\
	X(std::optional<short>,adjustPoints)\
	X(std::optional<u8>,autoAmpNoteCount)\
	X(std::optional<u8>,autoAmpNotePoints)\
	X(std::optional<u8>,autoLeavePoints)\
	X(std::optional<Yes_no>,autoLineRobot1)\
	X(std::optional<Yes_no>,autoLineRobot2)\
	X(std::optional<Yes_no>,autoLineRobot3)\
	X(std::optional<u8>,autoPoints)\
	X(std::optional<u8>,autoSpeakerNoteCount)\
	X(std::optional<u8>,autoSpeakerNotePoints)\
	X(std::optional<u8>,autoTotalNotePoints)\
	X(std::optional<bool>,coopNotePlayed)\
	X(std::optional<bool>,coopertitionCriteriaMet)\
	X(std::optional<u8>,endGameHarmonyPoints)\
	X(std::optional<u8>,endGameOnStagePoints)\
	X(std::optional<u8>,endGameParkPoints)\
	X(std::optional<Endgame_2024>,endGameRobot1)\
	X(std::optional<Endgame_2024>,endGameRobot2)\
	X(std::optional<Endgame_2024>,endGameRobot3)\
	X(std::optional<u8>,endGameSpotLightBonusPoints)\
	X(std::optional<u8>,endGameTotalStagePoints)\
	X(std::optional<bool>,ensembleBonusAchieved)\
	X(std::optional<u8>,ensembleBonusOnStageRobotsThreshold)\
	X(std::optional<u8>,ensembleBonusStagePointsThreshold)\
	X(std::optional<u8>,foulCount)\
	X(std::optional<u8>,foulPoints)\
	X(std::optional<bool>,g206Penalty)\
	X(std::optional<bool>,g408Penalty)\
	X(std::optional<bool>,g424Penalty)\
	X(std::optional<bool>,melodyBonusAchieved)\
	X(std::optional<u8>,melodyBonusThreshold)\
	X(std::optional<u8>,melodyBonusThresholdCoop)\
	X(std::optional<u8>,melodyBonusThresholdNonCoop)\
	X(std::optional<bool>,micCenterStage)\
	X(std::optional<bool>,micStageLeft)\
	X(std::optional<bool>,micStageRight)\
	X(double,rp)\
	X(std::optional<u8>,techFoulCount)\
	X(std::optional<u8>,teleopAmpNoteCount)\
	X(std::optional<u8>,teleopAmpNotePoints)\
	X(std::optional<u8>,teleopPoints)\
	X(std::optional<u8>,teleopSpeakerNoteAmplifiedCount)\
	X(std::optional<u8>,teleopSpeakerNoteAmplifiedPoints)\
	X(std::optional<u8>,teleopTotalNotePoints)\
	X(u8,totalPoints)\
	X(std::optional<bool>,trapCenterStage)\
	X(std::optional<bool>,trapStageLeft)\
	X(std::optional<bool>,trapStageRight)

TBA_MAKE_INST(Match_Score_Breakdown_2024_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2024_ALLIANCE)

#define TBA_MATCH_SCORE_BREAKDOWN_2024(X)\
	X(Match_Score_Breakdown_2024_Alliance,blue)\
	X(Match_Score_Breakdown_2024_Alliance,red)

TBA_MAKE_INST(Match_Score_Breakdown_2024,TBA_MATCH_SCORE_BREAKDOWN_2024)

#define TBA_ENDGAME_2025(X)\
	X(DeepCage)\
	X(None)\
	X(Parked)\
	X(ShallowCage)

TBA_MAKE_ENUM(Endgame_2025,TBA_ENDGAME_2025)

#define TBA_MATCH_SCORE_BREAKDOWN_2025_ALLIANCE(X)\
	X(std::optional<short>,adjustPoints)\
	X(short,algaePoints)\
	X(std::optional<bool>,autoBonusAchieved)\
	X(u8,autoCoralCount)\
	X(u8,autoCoralPoints)\
	X(Yes_no,autoLineRobot1)\
	X(Yes_no,autoLineRobot2)\
	X(Yes_no,autoLineRobot3)\
	X(u8,autoMobilityPoints)\
	X(u8,autoPoints)\
	X(Ignore,autoReef)\
	X(std::optional<bool>,bargeBonusAchieved)\
	X(std::optional<bool>,coopertitionCriteriaMet)\
	X(std::optional<bool>,coralBonusAchieved)\
	X(u8,endGameBargePoints)\
	X(std::optional<Endgame_2025>,endGameRobot1)\
	X(std::optional<Endgame_2025>,endGameRobot2)\
	X(std::optional<Endgame_2025>,endGameRobot3)\
	X(std::optional<u8>,foulCount)\
	X(short,foulPoints)\
	X(std::optional<bool>,g206Penalty)\
	X(std::optional<bool>,g410Penalty)\
	X(std::optional<bool>,g418Penalty)\
	X(std::optional<bool>,g428Penalty)\
	X(u8,netAlgaeCount)\
	X(double,rp)\
	X(std::optional<u8>,techFoulCount)\
	X(u8,teleopCoralCount)\
	X(short,teleopCoralPoints)\
	X(short,teleopPoints)\
	X(Ignore,teleopReef)\
	X(short,totalPoints)\
	X(u8,wallAlgaeCount)\

TBA_MAKE_INST(Match_Score_Breakdown_2025_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2025_ALLIANCE)

#define TBA_MATCH_SCORE_BREAKDOWN_2025(X)\
	X(Match_Score_Breakdown_2025_Alliance,blue)\
	X(Match_Score_Breakdown_2025_Alliance,red)

TBA_MAKE_INST(Match_Score_Breakdown_2025,TBA_MATCH_SCORE_BREAKDOWN_2025)

#define TBA_TOWERROBOT_2026(X)\
	X(Level1)\
	X(Level2)\
	X(Level3)\
	X(None)

TBA_MAKE_ENUM(TowerRobot_2026,TBA_TOWERROBOT_2026)

#define TBA_MATCH_SCORE_BREAKDOWN_2026_ALLIANCE(X)\
	X(int,adjustPoints)\
	X(int,autoTowerPoints)\
	X(TowerRobot_2026,autoTowerRobot1)\
	X(TowerRobot_2026,autoTowerRobot2)\
	X(TowerRobot_2026,autoTowerRobot3)\
	X(int,endGameTowerPoints)\
	X(TowerRobot_2026,endGameTowerRobot1)\
	X(TowerRobot_2026,endGameTowerRobot2)\
	X(TowerRobot_2026,endGameTowerRobot3)\
	X(bool,energizedAchieved)\
	X(int,foulPoints)\
	X(bool,g206Penalty)\
	X(Ignore,hubScore)\
	X(int,majorFoulCount)\
	X(int,minorFoulCount)\
	X(int,rp)\
	X(bool,superchargedAchieved)\
	X(int,totalAutoPoints)\
	X(int,totalPoints)\
	X(int,totalTeleopPoints)\
	X(int,totalTowerPoints)\
	X(bool,traversalAchieved)

TBA_MAKE_INST(Match_Score_Breakdown_2026_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2026_ALLIANCE)

#define TBA_MATCH_SCORE_BREAKDOWN_2026(X)\
	X(Match_Score_Breakdown_2026_Alliance,blue)\
	X(Match_Score_Breakdown_2026_Alliance,red)

TBA_MAKE_INST(Match_Score_Breakdown_2026,TBA_MATCH_SCORE_BREAKDOWN_2026)

using Match_Score_Breakdown=std::variant<
	Match_Score_Breakdown_2026,
	Match_Score_Breakdown_2025,
	Match_Score_Breakdown_2024,
	Match_Score_Breakdown_2023,
	Match_Score_Breakdown_2022,
	Match_Score_Breakdown_2020,
	Match_Score_Breakdown_2017,
	Match_Score_Breakdown_2014,
	Match_Score_Breakdown_2016,
	Match_Score_Breakdown_2015,
	Ignore
>;

#define TBA_MATCH(X)\
	X(Match_key,key)\
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



}

#endif
