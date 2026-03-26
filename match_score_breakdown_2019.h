#ifndef TBA_MATCH_SCORE_BREAKDOWN_2019_H
#define TBA_MATCH_SCORE_BREAKDOWN_2019_H

namespace tba{

#define TBA_MATCH_SCORE_BREAKDOWN_2019_ALLIANCE(X)\
	X(std::optional<int>,adjustPoints)\
	X(std::optional<int>,autoPoints)\
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
	X(std::optional<bool>,completeRocketFar)\
	X(std::optional<bool>,completeRocketNear)\
	X(std::string,endgameRobot1)\
	X(std::string,endgameRobot2)\
	X(std::string,endgameRobot3)\
	X(std::optional<int>,foulCount)\
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
	X(std::optional<std::string>,preMatchBay4)\
	X(std::optional<std::string>,preMatchBay5)\
	X(std::string,preMatchBay6)\
	X(std::string,preMatchBay7)\
	X(std::string,preMatchBay8)\
	X(std::string,preMatchLevelRobot1)\
	X(std::string,preMatchLevelRobot2)\
	X(std::string,preMatchLevelRobot3)\
	X(int,rp)\
	X(int,sandStormBonusPoints)\
	X(std::optional<int>,techFoulCount)\
	X(int,teleopPoints)\
	X(std::string,topLeftRocketFar)\
	X(std::string,topLeftRocketNear)\
	X(std::string,topRightRocketFar)\
	X(std::string,topRightRocketNear)\
	X(int,totalPoints)

TBA_MAKE_INST(Match_Score_Breakdown_2019_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2019_ALLIANCE)

#define TBA_MATCH_SCORE_BREAKDOWN_2019(X)\
	X(Match_Score_Breakdown_2019_Alliance,red)\
	X(Match_Score_Breakdown_2019_Alliance,blue)

TBA_MAKE_INST(Match_Score_Breakdown_2019,TBA_MATCH_SCORE_BREAKDOWN_2019)

}

#endif
