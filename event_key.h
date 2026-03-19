#ifndef TBA_EVENT_KEY_H
#define TBA_EVENT_KEY_H

#include "simdjson.h"
#include "year.h"

namespace tba{

class Event_key{
	alignas(8) std::array<char,12> buf;

	public:
	explicit Event_key(std::string_view);
	explicit Event_key(const char*);

	std::string_view get()const;
	Year year()const;
	std::string code()const;

	std::strong_ordering operator<=>(Event_key const&)const;
	bool operator==(Event_key const&)const;
};

bool operator==(Event_key const&,const char *);
std::ostream& operator<<(std::ostream&,Event_key const&);
Event_key decode(JSON_value,Event_key const*);
Event_key decode(std::string_view,Event_key const*);
std::optional<Event_key> maybe_decode(JSON_value,Event_key const*);
Event_key rand(Event_key const*);

}

#endif
