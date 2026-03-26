#ifndef TBA_MATCH_SCORE_BREAKDOWN_2026_H
#define TBA_MATCH_SCORE_BREAKDOWN_2026_H

namespace tba{

#define TBA_TOWERROBOT_2026(X)\
	X(Level1)\
	X(Level2)\
	X(Level3)\
	X(None)

TBA_MAKE_ENUM(TowerRobot_2026,TBA_TOWERROBOT_2026)

#define TBA_MATCH_SCORE_BREAKDOWN_2026_ALLIANCE(X)\
	X(short,adjustPoints)\
	X(u8,autoTowerPoints)\
	X(TowerRobot_2026,autoTowerRobot1)\
	X(TowerRobot_2026,autoTowerRobot2)\
	X(TowerRobot_2026,autoTowerRobot3)\
	X(u8,endGameTowerPoints)\
	X(TowerRobot_2026,endGameTowerRobot1)\
	X(TowerRobot_2026,endGameTowerRobot2)\
	X(TowerRobot_2026,endGameTowerRobot3)\
	X(bool,energizedAchieved)\
	X(short,foulPoints)\
	X(bool,g206Penalty)\
	X(Ignore,hubScore)\
	X(u8,majorFoulCount)\
	X(u8,minorFoulCount)\
	X(u8,rp)\
	X(bool,superchargedAchieved)\
	X(short,totalAutoPoints)\
	X(short,totalPoints)\
	X(short,totalTeleopPoints)\
	X(u8,totalTowerPoints)\
	X(bool,traversalAchieved)

TBA_MAKE_INST(Match_Score_Breakdown_2026_Alliance,TBA_MATCH_SCORE_BREAKDOWN_2026_ALLIANCE)

#define TBA_MATCH_SCORE_BREAKDOWN_2026(X)\
	X(Match_Score_Breakdown_2026_Alliance,blue)\
	X(Match_Score_Breakdown_2026_Alliance,red)

TBA_MAKE_INST(Match_Score_Breakdown_2026,TBA_MATCH_SCORE_BREAKDOWN_2026)

}

#endif
