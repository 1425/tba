#ifndef TBA_MATCH_SCORE_BREAKDOWN_2022_H
#define TBA_MATCH_SCORE_BREAKDOWN_2022_H

namespace tba{

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

}

#endif
