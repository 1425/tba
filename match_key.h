#ifndef TBA_MATCH_KEY_H
#define TBA_MATCH_KEY_H

#include "year.h"

namespace tba{

class Match_key{
	std::string s;

	public:
	explicit Match_key(std::string);
	std::string const& get()const;
	Year year()const;

	auto operator<=>(Match_key const&)const=default;
};

std::ostream& operator<<(std::ostream&,Match_key const&);
Match_key decode(JSON_value,Match_key const*);
Match_key decode2(std::string_view,Match_key const*);
std::optional<Match_key> maybe_decode(JSON_value,Match_key const*);

}

#endif
