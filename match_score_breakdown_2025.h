#ifndef TBA_MATCH_SCORE_BREAKDOWN_2025_H
#define TBA_MATCH_SCORE_BREAKDOWN_2025_H

namespace tba{

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

}

#endif
