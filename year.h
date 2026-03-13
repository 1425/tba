#ifndef TBA_YEAR_H
#define TBA_YEAR_H

#include "simdjson.h"

namespace tba{

class Year{
	//An integer that is between 1992 and 2092.
	short i;

	bool valid()const;

	public:
	explicit Year(int);
	Year& operator=(Year const&)=default;
	Year& operator=(int);

	short get()const;

	Year& operator--();

	auto operator<=>(Year const&)const=default;
	friend Year& operator++(Year&);

	bool operator==(Year const&)const;
	bool operator==(int)const;
	bool operator>=(int)const;
	bool operator<(int)const;
};

std::ostream& operator<<(std::ostream& o,Year);
Year& operator++(Year&);
Year operator++(Year&,int);
Year operator-(Year,int);
Year operator+(Year,int);
Year decode(JSON_value,const Year*);
Year decode(std::string_view,Year const*);
std::optional<Year> maybe_decode(JSON_value,Year const*);
Year rand(Year const*);

}

template<>
struct std::hash<tba::Year>{
	static short operator()(tba::Year);
};

#endif
