#ifndef TBA_TBA_H
#define TBA_TBA_H

#include<string>
#include "data.h"
#include "simdjson.h"

namespace tba{

template<typename Fetch,typename T>
auto run(Fetch& fetcher,std::string const& url,const T*){
	auto json=fetcher.fetch(url.c_str()).second;
	simdjson::dom::parser parser;
	simdjson::padded_string str(json);
	auto doc=parser.parse(str);
	try{
		switch(doc.type()){
			case simdjson::dom::element_type::ARRAY:
				return decode(doc.get_array(),(T*)nullptr);
			case simdjson::dom::element_type::OBJECT:
				return decode(doc.get_object(),(T*)nullptr);
			case simdjson::dom::element_type::NULL_VALUE:
				return decode(nullptr,(T*)nullptr);
			default:
				throw Decode_error{typeid(T).name(),"","unexpected type"};
		}
	}catch(...){
		std::cout<<"Fail on "<<url<<"\n";
		std::cout<<json<<"\n";
		throw;
	}
}

#define TBA_QUERY1(NAME,RETURN_TYPE,URL1,TYPE1,URL2) \
	template<typename T>\
	RETURN_TYPE NAME(T& fetcher,TYPE1 arg1){\
		std::ostringstream ss;\
		ss<<"https://www.thebluealliance.com/api/v3/"<<URL1<<arg1<<URL2;\
		return run(fetcher,ss.str(),(RETURN_TYPE*)nullptr);\
	}

#define TBA_QUERY2(NAME,RETURN_TYPE,URL1,TYPE1,URL2,TYPE2,URL3) \
	template<typename T>\
	RETURN_TYPE NAME(T& fetcher,TYPE1 arg1,TYPE2 arg2){\
		std::ostringstream ss;\
		ss<<"https://www.thebluealliance.com/api/v3/"<<URL1<<arg1<<URL2<<arg2<<URL3;\
		return run(fetcher,ss.str(),(RETURN_TYPE*)nullptr);\
	}

TBA_QUERY1(teams,std::vector<Team>,"teams/",Page,"")
TBA_QUERY1(teams_simple,std::vector<Team_Simple>,"teams/",Page,"/simple")
TBA_QUERY1(team_keys,std::vector<Team_key>,"teams/",Page,"/keys")
TBA_QUERY2(teams_year,std::vector<Team>,"teams/",Year,"/",Page,"")
TBA_QUERY2(teams_year_simple,std::vector<Team_Simple>,"teams/",Year,"/",Page,"/simple")
TBA_QUERY2(teams_year_keys,std::vector<Team_key>,"teams/",Year,"/",Page,"/keys")
TBA_QUERY1(events,std::vector<Event>,"events/",Year,"")
TBA_QUERY1(events_simple,std::vector<Event_Simple>,"events/",Year,"/simple")
TBA_QUERY1(events_keys,std::vector<Event_key>,"events/",Year,"/keys")

TBA_QUERY1(districts,std::vector<Year_info>,"districts/",Year,"")
TBA_QUERY1(team_awards,std::vector<Award>,"team/",Team_key,"/awards")
TBA_QUERY2(team_awards_year,std::vector<Award>,"team/",Team_key,"/awards/",Year,"")
TBA_QUERY2(team_matches_year,std::vector<Match>,"team/",Team_key,"/matches/",Year,"")
TBA_QUERY2(team_matches_year_simple,std::vector<Match_Simple>,"team/",Team_key,"/matches/",Year,"/simple")
TBA_QUERY2(team_matches_year_keys,std::vector<Match_key>,"team/",Team_key,"/matches/",Year,"/keys")
TBA_QUERY2(team_media_year,std::vector<Media>,"team/",Team_key,"/media/",Year,"")
TBA_QUERY1(team_social_media,std::vector<Media>,"team/",Team_key,"/social_media")
TBA_QUERY1(event_teams,std::vector<Team>,"event/",Event_key,"/teams")
TBA_QUERY1(event_teams_simple,std::vector<Team_Simple>,"event/",Event_key,"/teams/simple")
TBA_QUERY1(event_teams_keys,std::vector<Team_key>,"event/",Event_key,"/teams/keys")
TBA_QUERY1(district_teams,std::vector<Team>,"district/",District_key,"/teams")
TBA_QUERY1(district_teams_simple,std::vector<Team_Simple>,"district/",District_key,"/teams/simple")
TBA_QUERY1(district_teams_keys,std::vector<Team_key>,"district/",District_key,"/teams/keys")

//event
TBA_QUERY1(team_events,std::vector<Event>,"team/",Team_key,"/events")
TBA_QUERY1(team_events_simple,std::vector<Event_Simple>,"team/",Team_key,"/events/simple")
TBA_QUERY1(team_events_keys,std::vector<Event_key>,"team/",Team_key,"/events/keys")
TBA_QUERY2(team_events_year,std::vector<Event>,"team/",Team_key,"/events/",Year,"")
TBA_QUERY2(team_events_year_simple,std::vector<Event_Simple>,"team/",Team_key,"/events/",Year,"/simple")
TBA_QUERY2(team_events_year_keys,std::vector<Event_key>,"team/",Team_key,"/events/",Year,"/keys")
TBA_QUERY2(team_event_matches,std::vector<Match>,"team/",Team_key,"/event/",Event_key,"/matches")
TBA_QUERY2(team_event_awards,std::vector<Award>,"team/",Team_key,"/event/",Event_key,"/awards")

//the "optional" is not as documented.
TBA_QUERY2(team_event_status,std::optional<Team_Event_Status>,"team/",Team_key,"/event/",Event_key,"/status")

TBA_QUERY1(events_year,std::vector<Event>,"events/",Year,"")
TBA_QUERY1(events_year_simple,std::vector<Event_Simple>,"events/",Year,"/simple")
TBA_QUERY1(events_year_keys,std::vector<Event_key>,"events/",Year,"/keys")

TBA_QUERY1(event,Event,"event/",Event_key,"")
TBA_QUERY1(event_simple,Event_Simple,"event/",Event_key,"/simple")

//it is not documented that this might return NULL
TBA_QUERY1(event_alliances,std::optional<std::vector<Elimination_Alliance>>,"event/",Event_key,"/alliances")

TBA_QUERY1(event_insights,Event_insights,"event/",Event_key,"/insights")

//doc doesn't say this might be null.
TBA_QUERY1(event_oprs,std::optional<Event_OPRs>,"event/",Event_key,"/oprs")

//doc doesn't say can be null
TBA_QUERY1(event_predictions,std::optional<Event_predictions>,"event/",Event_key,"/predictions")

//not documented that may be null.
TBA_QUERY1(event_rankings,std::optional<Event_ranking>,"event/",Event_key,"/rankings")

//not documented that may be null.
TBA_QUERY1(event_district_points,std::optional<Event_District_Points>,"event/",Event_key,"/district_points")

TBA_QUERY1(event_matches,std::vector<Match>,"event/",Event_key,"/matches")
TBA_QUERY1(event_matches_simple,std::vector<Match_Simple>,"event/",Event_key,"/matches/simple")
TBA_QUERY1(event_matches_keys,std::vector<Match_key>,"event/",Event_key,"/matches/keys")

TBA_QUERY1(event_awards,std::vector<Award>,"event/",Event_key,"/awards")

TBA_QUERY1(district_events,std::vector<Event>,"district/",District_key,"/events")
TBA_QUERY1(district_events_keys,std::vector<Event_key>,"district/", District_key,"/events/keys")
TBA_QUERY1(district_events_simple,std::vector<Event_Simple>,"district/", District_key,"/events/simple")

TBA_QUERY1(district_rankings,std::optional<std::vector<District_Ranking>>,"district/", District_key,"/rankings")
TBA_QUERY1(match_simple,Match_Simple,"match/", Match_key,"/simple")
TBA_QUERY1(match,Match,"match/", Match_key,"")
TBA_QUERY1(team_districts,std::vector<District_List>,"team/", Team_key,"/districts")
TBA_QUERY2(team_event_matches_keys,std::vector<Match_key>,"team/", Team_key, "/event/",Event_key ,"/matches/keys")
TBA_QUERY2(team_event_matches_simple,std::vector<Match_Simple>,"team/", Team_key, "/event/",Event_key ,"/matches/simple")

TBA_QUERY1(zebra_motionworks,Zebra,"match/",Match_key,"/zebra_motionworks")

}

#endif
