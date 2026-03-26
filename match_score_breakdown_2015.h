#ifndef TBA_MATCH_SCORE_BREAKDOWN_2015_H
#define TBA_MATCH_SCORE_BREAKDOWN_2015_H

namespace tba{

using u8=Int_limited<0,255>;

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

}

#endif
