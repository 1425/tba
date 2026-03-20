#ifndef TBA_TEAM_KEY_H
#define TBA_TEAM_KEY_H

#include "simdjson.h"

namespace tba{

class Team_key{
	alignas(8) std::array<char,8> buf;

	public:
	explicit Team_key(std::string const&);
	explicit Team_key(std::string_view);
	explicit Team_key(const char*);
	explicit Team_key(int);

	std::string str()const;
	uint64_t data()const;
	std::string_view raw()const;

	std::strong_ordering operator<=>(Team_key const&)const;
	bool operator==(Team_key const&)const;
};

std::ostream& operator<<(std::ostream&,Team_key const&);
Team_key decode(JSON_value,Team_key const*);
Team_key decode2(std::string_view,Team_key const*);
std::optional<Team_key> maybe_decode(JSON_value,Team_key const*);
Team_key rand(Team_key const*);
std::string operator+(Team_key const&,const char*);

}

template<>
struct std::hash<tba::Team_key>{
	static uint64_t operator()(tba::Team_key);
};

#endif
