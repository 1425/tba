#ifndef EVENT_INSIGHTS_H
#define EVENT_INSIGHTS_H

#include "macro.h"
#include "match_key.h"

namespace tba{

#define TBA_HIGH_SCORE(X)\
	X(int,high_score)\
	X(Match_key,match_key)\
	X(std::string,match_name)

struct High_score{
	TBA_HIGH_SCORE(TBA_INST)

	auto operator<=>(High_score const&)const=default;
};

std::ostream& operator<<(std::ostream&,High_score const&);
High_score decode(JSON_value,const High_score*);
std::optional<High_score> maybe_decode(JSON_value,High_score const*);

using D3=std::array<double,3>;
using I3=std::array<int,3>;
using IID=std::tuple<int,int,double>;

#define TBA_EVENT_INSIGHTS_2016_DETAIL(X)\
	X(IID,LowBar)\
	X(IID,A_ChevalDeFrise)\
	X(IID,A_Portcullis)\
	X(IID,B_Ramparts)\
	X(IID,B_Moat)\
	X(IID,C_SallyPort)\
	X(IID,C_Drawbridge)\
	X(IID,D_RoughTerrain)\
	X(IID,D_RockWall)\
	X(double,average_high_goals)\
	X(double,average_low_goals)\
	X(IID,breaches)\
	X(IID,scales)\
	X(IID,challenges)\
	X(IID,captures)\
	X(double,average_win_score)\
	X(double,average_score)\
	X(double,average_auto_score)\
	X(double,average_crossing_score)\
	X(double,average_boulder_score)\
	X(double,average_tower_score)\
	X(double,average_foul_score)\
	X(High_score,high_score)

TBA_MAKE_INST(Event_Insights_2016_Detail,TBA_EVENT_INSIGHTS_2016_DETAIL)

#define TBA_EVENT_INSIGHTS_2016(X)\
	X(std::optional<Event_Insights_2016_Detail>,qual)\
	X(std::optional<Event_Insights_2016_Detail>,playoff)

TBA_MAKE_INST(Event_Insights_2016,TBA_EVENT_INSIGHTS_2016)

#define TBA_EVENT_INSIGHTS_2017_DETAIL(X)\
	X(double,average_foul_score)\
	X(double,average_fuel_points)\
	X(double,average_fuel_points_auto)\
	X(double,average_fuel_points_teleop)\
	X(double,average_high_goals)\
	X(double,average_high_goals_auto)\
	X(double,average_high_goals_teleop)\
	X(double,average_low_goals)\
	X(double,average_low_goals_auto)\
	X(double,average_low_goals_teleop)\
	X(double,average_mobility_points_auto)\
	X(double,average_points_auto)\
	X(double,average_points_teleop)\
	X(double,average_rotor_points)\
	X(double,average_rotor_points_auto)\
	X(double,average_score)\
	X(double,average_takeoff_points_teleop)\
	X(double,average_win_margin)\
	X(double,average_win_score)\
	X(High_score,high_kpa)\
	X(High_score,high_score)\
	X(IID,kpa_achieved)\
	X(IID,mobility_counts)\
	X(IID,rotor_1_engaged)\
	X(IID,rotor_1_engaged_auto)\
	X(IID,rotor_2_engaged)\
	X(IID,rotor_2_engaged_auto)\
	X(IID,rotor_3_engaged)\
	X(IID,rotor_4_engaged)\
	X(IID,takeoff_counts)

TBA_MAKE_INST(Event_Insights_2017_Detail,TBA_EVENT_INSIGHTS_2017_DETAIL)

#define TBA_EVENT_INSIGHTS_2017(X)\
	X(std::optional<Event_Insights_2017_Detail>,qual)\
	X(std::optional<Event_Insights_2017_Detail>,playoff)

TBA_MAKE_INST(Event_Insights_2017,TBA_EVENT_INSIGHTS_2017)

using ISS=std::tuple<int,std::string,std::string>;

#define TBA_EVENT_INSIGHTS_2018_DETAIL(X)\
	X(IID,auto_quest_achieved)\
	X(double,average_boost_played)\
	X(double,average_endgame_points)\
	X(double,average_force_played)\
	X(double,average_foul_score)\
	X(double,average_points_auto)\
	X(double,average_points_teleop)\
	X(double,average_run_points_auto)\
	X(double,average_scale_ownership_points)\
	X(double,average_scale_ownership_points_auto)\
	X(double,average_scale_ownership_points_teleop)\
	X(double,average_score)\
	X(double,average_switch_ownership_points)\
	X(double,average_switch_ownership_points_auto)\
	X(double,average_switch_ownership_points_teleop)\
	X(double,average_vault_points)\
	X(double,average_win_margin)\
	X(double,average_win_score)\
	X(IID,boost_played_counts)\
	X(IID,climb_counts)\
	X(IID,face_the_boss_achieved)\
	X(IID,force_played_counts)\
	X(ISS,high_score)\
	X(IID,levitate_played_counts)\
	X(IID,run_counts_auto)\
	X(double,scale_neutral_percentage)\
	X(double,scale_neutral_percentage_auto)\
	X(double,scale_neutral_percentage_teleop)\
	X(IID,switch_owned_counts_auto)\
	X(IID,unicorn_matches)\
	X(double,winning_opp_switch_denial_percentage_teleop)\
	X(double,winning_own_switch_ownership_percentage)\
	X(double,winning_own_switch_ownership_percentage_auto)\
	X(double,winning_own_switch_ownership_percentage_teleop)\
	X(double,winning_scale_ownership_percentage)\
	X(double,winning_scale_ownership_percentage_auto)\
	X(double,winning_scale_ownership_percentage_teleop)

TBA_MAKE_INST(Event_Insights_2018_Detail,TBA_EVENT_INSIGHTS_2018_DETAIL)

#define TBA_EVENT_INSIGHTS_2018(X)\
	X(std::optional<Event_Insights_2018_Detail>,playoff)\
	X(std::optional<Event_Insights_2018_Detail>,qual)

TBA_MAKE_INST(Event_Insights_2018,TBA_EVENT_INSIGHTS_2018)

using D8=std::array<double,8>;
using D6=std::array<double,6>;

#define TBA_AVERAGE_ROCKET_COUNT(X)\
	X(double,lowLeftFar)\
	X(double,lowLeftNear)\
	X(double,lowRightNear)\
	X(double,midLeftFar)\
	X(double,midLeftNear)\
	X(double,midRightNear)\
	X(double,midRightFar)\
	X(double,topLeftFar)\
	X(double,topLeftNear)\
	X(double,topRightFar)\
	X(double,topRightNear)

TBA_MAKE_INST(Average_rocket_count,TBA_AVERAGE_ROCKET_COUNT)

#define TBA_EVENT_INSIGHTS_2019_DETAIL(X)\
	X(double,average_cargo_points)\
	X(D8,average_cargo_ship_cargo_count)\
	X(D6,average_cargo_ship_cargo_preload_count)\
	X(D8,average_cargo_ship_hatch_panel_count)\
	X(D6,average_cargo_ship_hatch_panel_preload_count)\
	X(double,average_foul_score)\
	X(double,average_hab_climb_teleop)\
	X(Average_rocket_count,average_rocket_cargo_count)\
	X(Average_rocket_count,average_rocket_hatch_panel_count)\
	X(double,average_sandstorm_bonus_auto)\
	X(double,average_score)\
	X(double,average_win_margin)\
	X(double,average_win_score)\
	X(IID,climb_rp_achieved)\
	X(IID,complete_1_rocket_count)\
	X(IID,complete_2_rockets_count)\
	X(IID,cross_hab_line_count)\
	X(IID,cross_hab_line_sandstorm_count)\
	X(ISS,high_score)\
	X(IID,level1_climb_count)\
	X(IID,level2_climb_count)\
	X(IID,level3_climb_count)\
	X(IID,rocket_rp_achieved)\
	X(IID,unicorn_matches)

TBA_MAKE_INST(Event_Insights_2019_Detail,TBA_EVENT_INSIGHTS_2019_DETAIL)

#define TBA_EVENT_INSIGHTS_2019(X)\
	X(std::optional<Event_Insights_2019_Detail>,playoff)\
	X(std::optional<Event_Insights_2019_Detail>,qual)

TBA_MAKE_INST(Event_Insights_2019,TBA_EVENT_INSIGHTS_2019)

#define TBA_EVENT_INSIGHTS_2020_DETAIL(X)\
	X(IID,achieve_stage1_count)\
	X(IID,achieve_stage2_count)\
	X(IID,achieve_stage3_count)\
	X(double,average_cell_count)\
	X(double,average_cell_count_auto)\
	X(double,average_cell_count_bottom)\
	X(double,average_cell_count_bottom_auto)\
	X(double,average_cell_count_bottom_teleop)\
	X(double,average_cell_count_inner)\
	X(double,average_cell_count_inner_auto)\
	X(double,average_cell_count_inner_teleop)\
	X(double,average_cell_count_outer)\
	X(double,average_cell_count_outer_auto)\
	X(double,average_cell_count_outer_teleop)\
	X(double,average_cell_points_auto)\
	X(double,average_cell_points_teleop)\
	X(double,average_cell_score)\
	X(double,average_control_panel_points)\
	X(double,average_endgame_points)\
	X(double,average_foul_score)\
	X(double,average_init_line_points_auto)\
	X(double,average_num_robots_hanging)\
	X(double,average_points_auto)\
	X(double,average_points_teleop)\
	X(double,average_score)\
	X(double,average_win_margin)\
	X(double,average_win_score)\
	X(IID,exit_init_line_count)\
	X(IID,generator_energized_rp_achieved)\
	X(IID,generator_level_count)\
	X(IID,generator_operational_rp_achieved)\
	X(IID,hang_count)\
	X(ISS,high_score)\
	X(IID,park_count)\
	X(IID,unicorn_matches)

TBA_MAKE_INST(Event_Insights_2020_Detail,TBA_EVENT_INSIGHTS_2020_DETAIL)

#define TBA_EVENT_INSIGHTS_2020(X)\
	X(std::optional<Event_Insights_2020_Detail>,playoff)\
	X(std::optional<Event_Insights_2020_Detail>,qual)

TBA_MAKE_INST(Event_Insights_2020,TBA_EVENT_INSIGHTS_2020)

#define TBA_EVENT_INSIGHTS_2022_DETAIL(X)\
	X(double,average_cargo_count)\
	X(double,average_cargo_count_auto)\
	X(double,average_cargo_count_teleop)\
	X(double,average_cargo_points)\
	X(double,average_cargo_points_auto)\
	X(double,average_cargo_points_teleop)\
	X(double,average_endgame_points)\
	X(double,average_foul_score)\
	X(double,average_lower_cargo_count)\
	X(double,average_lower_cargo_count_auto)\
	X(double,average_lower_cargo_count_teleop)\
	X(double,average_points_auto)\
	X(double,average_points_teleop)\
	X(double,average_score)\
	X(double,average_taxi_points)\
	X(double,average_upper_cargo_count)\
	X(double,average_upper_cargo_count_auto)\
	X(double,average_upper_cargo_count_teleop)\
	X(double,average_win_margin)\
	X(double,average_win_score)\
	X(IID,cargo_bonus_rp)\
	X(IID,hangar_bonus_rp)\
	X(IID,high_climb_count)\
	X(High_score,high_score)\
	X(IID,low_climb_count)\
	X(IID,mid_climb_count)\
	X(IID,quintet_count)\
	X(IID,taxi_count)\
	X(IID,traversal_climb_count)\
	X(IID,unicorn_matches)

TBA_MAKE_INST(Event_Insights_2022_Detail,TBA_EVENT_INSIGHTS_2022_DETAIL)

#define TBA_EVENT_INSIGHTS_2022(X)\
	X(Event_Insights_2022_Detail,playoff)\
	X(Event_Insights_2022_Detail,qual)

TBA_MAKE_INST(Event_Insights_2022,TBA_EVENT_INSIGHTS_2022)

#define TBA_EVENT_INSIGHTS_2023_DETAIL(X)\
	X(IID,activation_bonus_rp)\
	X(IID,auto_docked_count)\
	X(IID,auto_engaged_count)\
	X(double,average_charge_station_points_auto)\
	X(double,average_charge_station_points_teleop)\
	X(double,average_foul_score)\
	X(double,average_link_points)\
	X(double,average_mobility_points)\
	X(double,average_park_points)\
	X(double,average_piece_points_auto)\
	X(double,average_piece_points_teleop)\
	X(double,average_points_auto)\
	X(double,average_points_teleop)\
	X(double,average_score)\
	X(double,average_win_margin)\
	X(double,average_win_score)\
	X(IID,coopertition)\
	X(High_score,high_score)\
	X(IID,mobility_count)\
	X(IID,sustainability_bonus_rp)\
	X(IID,unicorn_matches)

TBA_MAKE_INST(Event_Insights_2023_Detail,TBA_EVENT_INSIGHTS_2023_DETAIL)

#define TBA_EVENT_INSIGHTS_2023(X)\
	X(std::optional<Event_Insights_2023_Detail>,playoff)\
	X(Event_Insights_2023_Detail,qual)

TBA_MAKE_INST(Event_Insights_2023,TBA_EVENT_INSIGHTS_2023)

#define TBA_EVENT_INSIGHTS_2024_DETAIL(X)\
	X(double,average_score)\
	X(double,average_win_margin)\
	X(IID,coopertition_count)\
	X(IID,ensemble_rp_count)\
	X(IID,four_rp_count)\
	X(High_score,high_score)\
	X(IID,melody_rp_count)\
	X(IID,six_rp_count)\

TBA_MAKE_INST(Event_Insights_2024_Detail,TBA_EVENT_INSIGHTS_2024_DETAIL)

#define TBA_EVENT_INSIGHTS_2024(X)\
	X(Event_Insights_2024_Detail,playoff)\
	X(Event_Insights_2024_Detail,qual)

TBA_MAKE_INST(Event_Insights_2024,TBA_EVENT_INSIGHTS_2024)

#define TBA_EVENT_INSIGHTS_2025_DETAIL(X)\
	X(IID,auto_rp_count)\
	X(double,average_score)\
	X(double,average_win_margin)\
	X(double,average_winning_score)\
	X(IID,barge_rp_count)\
	X(IID,coopertition_count)\
	X(IID,coral_rp_count)\
	X(High_score,high_score)\
	X(IID,nine_rp_count)\
	X(IID,six_rp_count)\

TBA_MAKE_INST(Event_Insights_2025_Detail,TBA_EVENT_INSIGHTS_2025_DETAIL)

#define TBA_EVENT_INSIGHTS_2025(X)\
	X(Event_Insights_2025_Detail,playoff)\
	X(Event_Insights_2025_Detail,qual)

TBA_MAKE_INST(Event_Insights_2025,TBA_EVENT_INSIGHTS_2025)

using Event_insights=std::variant<
	std::nullptr_t,
	Event_Insights_2017,
	Event_Insights_2016,
	Event_Insights_2018,
	Event_Insights_2019,
	Event_Insights_2020,
	Event_Insights_2022,
	Event_Insights_2023,
	Event_Insights_2024,
	Event_Insights_2025
>;

}

#endif
