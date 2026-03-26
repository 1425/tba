#ifndef TBA_MATCH_SCORE_BREAKDOWN_2020_H
#define TBA_MATCH_SCORE_BREAKDOWN_2020_H

namespace tba{

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
	X(std::optional<bool>,tba_shieldEnergizedRankingPointFromFoul)\
	X(std::optional<u8>,tba_numRobotsHanging)\
	X(u8,foulCount)\
	X(u8,techFoulCount)\
	X(std::optional<short>,adjustPoints)\
	X(u8,foulPoints)\
	X(std::optional<u8>,rp)\
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

}

#endif
