#ifndef TBA_MATCH_H
#define TBA_MATCH_H

#include "macro.h"
#include<optional>
#include "data.h"//for Competition_level
#include "match_score_breakdown_2014.h"
#include "match_score_breakdown_2015.h"
#include "match_score_breakdown_2016.h"
#include "match_score_breakdown_2017.h"
#include "match_score_breakdown_2018.h"
#include "match_score_breakdown_2019.h"
#include "match_score_breakdown_2020.h"
#include "match_score_breakdown_2022.h"
#include "match_score_breakdown_2023.h"
#include "match_score_breakdown_2024.h"
#include "match_score_breakdown_2025.h"
#include "match_score_breakdown_2026.h"

namespace tba{

using Match_Score_Breakdown=std::variant<
	Match_Score_Breakdown_2026,
	Match_Score_Breakdown_2025,
	Match_Score_Breakdown_2024,
	Match_Score_Breakdown_2023,
	Match_Score_Breakdown_2022,
	Match_Score_Breakdown_2020,
	Match_Score_Breakdown_2019,
	Match_Score_Breakdown_2018,
	Match_Score_Breakdown_2017,
	Match_Score_Breakdown_2016,
	Match_Score_Breakdown_2015,
	Match_Score_Breakdown_2014
>;

#define TBA_MATCH(X)\
	X(Match_key,key)\
	X(Competition_level,comp_level)\
	X(int,set_number)\
	X(int,match_number)\
	X(Alliances,alliances)\
	X(Winning_alliance,winning_alliance)\
	X(Event_key,event_key)\
	X(std::optional<time_t>,time)\
	X(std::optional<time_t>,actual_time)\
	X(std::optional<time_t>,predicted_time)\
	X(std::optional<time_t>,post_result_time)\
	X(std::optional<Match_Score_Breakdown>,score_breakdown)\
	X(std::vector<Media>,videos)

TBA_MAKE_INST(Match,TBA_MATCH)

}

#endif
