#ifndef TBA_MATCH_SCORE_BREAKDOWN_2014_H
#define TBA_MATCH_SCORE_BREAKDOWN_2014_H

namespace tba{

#define TBA_MATCH_SCORE_BREAKDOWN_2014_ALLIANCE(X)\
	X(short,assist,assist)\
	X(short,auto_pts,auto)\
	X(short,teleop_goal_and_foul,teleop_goal+foul)\
	X(short,truss_and_catch,truss+catch)

struct Match_Score_Breakdown_2014_Alliance{
	#define X(A,B,C) A B;
	TBA_MATCH_SCORE_BREAKDOWN_2014_ALLIANCE(X)
	#undef X

	auto operator<=>(Match_Score_Breakdown_2014_Alliance const&)const=default;
};

std::ostream& operator<<(std::ostream&,Match_Score_Breakdown_2014_Alliance const&);
Match_Score_Breakdown_2014_Alliance decode(JSON_value,const Match_Score_Breakdown_2014_Alliance*);
std::optional<Match_Score_Breakdown_2014_Alliance> maybe_decode(JSON_value,Match_Score_Breakdown_2014_Alliance const*);
Match_Score_Breakdown_2014_Alliance rand(Match_Score_Breakdown_2014_Alliance const*);

#define TBA_MATCH_SCORE_BREAKDOWN_2014(X)\
	X(Match_Score_Breakdown_2014_Alliance,blue)\
	X(Match_Score_Breakdown_2014_Alliance,red)

TBA_MAKE_INST(Match_Score_Breakdown_2014,TBA_MATCH_SCORE_BREAKDOWN_2014)

}

#endif
