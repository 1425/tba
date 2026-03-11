#ifndef DISTRICT_KEY_H
#define DISTRICT_KEY_H

#include "simdjson.h"

namespace tba{

class District_key{
	alignas(8) std::array<char,8> buf;

	public:
	explicit District_key(std::string const&);
	explicit District_key(const char *);

	std::string get()const;

	std::strong_ordering operator<=>(District_key const&)const;
	bool operator==(District_key const&)const;

	static std::optional<District_key> parse(std::string const&);
};

std::ostream& operator<<(std::ostream&,District_key const&);
bool operator==(District_key const&,std::string const&);
District_key decode(JSON_value,const District_key*);
std::optional<District_key> maybe_decode(JSON_value,District_key const*);

}

#endif
