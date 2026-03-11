#include "event_insights.h"
#include "util.h"

namespace tba{
	
#define NO_NULL(NAME) \
	std::optional<NAME> maybe_decode(std::nullptr_t,NAME const*){\
		return std::nullopt;\
	}\

//NO_NULL(std::string)

template<typename K,typename V>
NO_NULL(std::map<TBA_SINGLE_ARG(K,V)>)

NO_NULL(IID)
NO_NULL(ISS)
NO_NULL(D8)
NO_NULL(D6)

TBA_DECODE_FAIL(High_score)

std::ostream& operator<<(std::ostream& o,High_score const& a){
	o<<"High_score(";
	TBA_HIGH_SCORE(TBA_PRINT_ITEM)
	return o<<")";
}

High_score decode(JSON_value in,const High_score*){
	auto check=[&](bool b){
		if(b) return;
		std::ostringstream ss;
		ss<<"High_score:"<<in;
		throw std::invalid_argument{ss.str()};
	};
	check(in.is_array());
	auto a=in.get_array();
	check(a.size()==3);
	return High_score{
		decode(a.at(0),(int*)nullptr),
		decode(a.at(1),(Match_key*)nullptr),
		decode(a.at(2),(std::string*)nullptr),
	};
}

TBA_MAKE_IMPL(Event_Insights_2016_Detail,TBA_EVENT_INSIGHTS_2016_DETAIL)

TBA_MAKE_IMPL(Event_Insights_2016,TBA_EVENT_INSIGHTS_2016)

TBA_MAKE_IMPL(Event_Insights_2017_Detail,TBA_EVENT_INSIGHTS_2017_DETAIL)

TBA_MAKE_IMPL(Event_Insights_2017,TBA_EVENT_INSIGHTS_2017)

TBA_MAKE_IMPL(Event_Insights_2018_Detail,TBA_EVENT_INSIGHTS_2018_DETAIL)

TBA_MAKE_IMPL(Event_Insights_2018,TBA_EVENT_INSIGHTS_2018)

TBA_MAKE_IMPL(Event_Insights_2019_Detail,TBA_EVENT_INSIGHTS_2019_DETAIL)

TBA_MAKE_IMPL(Event_Insights_2019,TBA_EVENT_INSIGHTS_2019)

TBA_MAKE_IMPL(Event_Insights_2020_Detail,TBA_EVENT_INSIGHTS_2020_DETAIL)

TBA_MAKE_IMPL(Event_Insights_2020,TBA_EVENT_INSIGHTS_2020)

TBA_MAKE_IMPL(Event_Insights_2022_Detail,TBA_EVENT_INSIGHTS_2022_DETAIL)

TBA_MAKE_IMPL(Event_Insights_2022,TBA_EVENT_INSIGHTS_2022)

TBA_MAKE_IMPL(Event_Insights_2023_Detail,TBA_EVENT_INSIGHTS_2023_DETAIL)

TBA_MAKE_IMPL(Event_Insights_2023,TBA_EVENT_INSIGHTS_2023)

TBA_MAKE_IMPL(Event_Insights_2024_Detail,TBA_EVENT_INSIGHTS_2024_DETAIL)

TBA_MAKE_IMPL(Event_Insights_2024,TBA_EVENT_INSIGHTS_2024)

TBA_MAKE_IMPL(Event_Insights_2025_Detail,TBA_EVENT_INSIGHTS_2025_DETAIL)

TBA_MAKE_IMPL(Event_Insights_2025,TBA_EVENT_INSIGHTS_2025)

TBA_MAKE_IMPL(Average_rocket_count,TBA_AVERAGE_ROCKET_COUNT)

}
