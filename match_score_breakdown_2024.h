#ifndef TBA_MATCH_SCORE_BREAKDOWN_2024_H
#define TBA_MATCH_SCORE_BREAKDOWN_2024_H

namespace tba{

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

}

#endif
