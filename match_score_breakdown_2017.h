#ifndef TBA_MATCH_SCORE_BREAKDOWN_2017_H
#define TBA_MATCH_SCORE_BREAKDOWN_2017_H

namespace tba{

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

}

#endif
