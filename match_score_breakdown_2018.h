#ifndef TBA_MATCH_SCORE_BREAKDOWN_2018_H
#define TBA_MATCH_SCORE_BREAKDOWN_2018_H

namespace tba{

#define TBA_MATCH_SCORE_BREAKDOWN_2018_ALLIANCE(X)\
	X(std::optional<short>,adjustPoints)\
	X(u8,autoOwnershipPoints)\
	X(u8,autoPoints)\
	X(std::optional<bool>,autoQuestRankingPoint)\
	X(std::optional<std::string>,autoRobot1)\
	X(std::optional<std::string>,autoRobot2)\
	X(std::optional<std::string>,autoRobot3)\
	X(u8,autoRunPoints)\
	X(u8,autoScaleOwnershipSec)\
	X(std::optional<bool>,autoSwitchAtZero)\
	X(u8,autoSwitchOwnershipSec)\
	X(std::optional<std::string>,endgameRobot1)\
	X(std::optional<std::string>,endgameRobot2)\
	X(std::optional<std::string>,endgameRobot3)\
	X(std::optional<bool>,faceTheBossRankingPoint)\
	X(std::optional<u8>,foulCount)\
	X(short,foulPoints)\
	X(u8,rp)\
	X(std::optional<u8>,techFoulCount)\
	X(short,teleopOwnershipPoints)\
	X(short,teleopPoints)\
	X(u8,teleopScaleBoostSec)\
	X(std::optional<u8>,teleopScaleForceSec)\
	X(short,teleopScaleOwnershipSec)\
	X(u8,teleopSwitchBoostSec)\
	X(std::optional<u8>,teleopSwitchForceSec)\
	X(short,teleopSwitchOwnershipSec)\
	X(short,totalPoints)\
	X(u8,vaultBoostPlayed)\
	X(u8,vaultBoostTotal)\
	X(u8,vaultForcePlayed)\
	X(u8,vaultForceTotal)\
	X(u8,vaultLevitatePlayed)\
	X(u8,vaultLevitateTotal)\
	X(u8,vaultPoints)\
	X(std::optional<std::string>,tba_gameData)

TBA_MAKE_INST(Match_Score_Breakdown_2018_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2018_ALLIANCE)

#define TBA_MATCH_SCORE_BREAKDOWN_2018(X)\
	X(Match_Score_Breakdown_2018_Alliance,red)\
	X(Match_Score_Breakdown_2018_Alliance,blue)

TBA_MAKE_INST(Match_Score_Breakdown_2018,TBA_MATCH_SCORE_BREAKDOWN_2018)

}

#endif
