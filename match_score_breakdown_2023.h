#ifndef MATCH_SCORE_BREAKDOWN_2023_H
#define MATCH_SCORE_BREAKDOWN_2023_H

namespace tba{

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

}

#endif
