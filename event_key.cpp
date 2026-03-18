#include "event_key.h"
#include "year.h"
#include "util.h"

namespace tba{

Event_key::Event_key(std::string_view s){
	if(s.size()<6) throw std::invalid_argument{std::string()+"Event_key:"+std::string(s)};
	//starts with a year then has at least 2 more chars.
	if(!s.starts_with("202121")){
		Year{atoi(s.data())};
	}
	if(s.size()>=buf.size()){
		throw std::invalid_argument("Event_key");
		/*TBA_PRINT(s);
		TBA_PRINT(s.size())
		TBA_PRINT(buf.size())*/
	}
	assert(s.size()<buf.size());
	bzero(&buf[0],buf.size());
	memcpy(&buf[0],s.data(),s.size());
}

Event_key::Event_key(const char *s){
	assert(s);
	*this=Event_key(std::string_view(s));
}

std::strong_ordering Event_key::operator<=>(Event_key const& a)const{
	//Not understood by some older compilers, so leave this out.
	//static_assert(buf.size()==12);
	
	auto f=[](auto const& x){ return *(uint64_t*)&x[0]; };
	auto c=f(buf)<=>f(a.buf);
	if(c!=std::strong_ordering::equal){
		return c;
	}
	auto g=[](auto const& x){ return *(uint32_t*)&x[8]; };
	return g(buf)<=>g(a.buf);
}

bool Event_key::operator==(Event_key const& a)const{
	return (*this<=>a)==0;
}

std::string_view Event_key::get()const{
	return std::string_view(&buf[0]);
}

Event_key rand(Event_key const*){
	std::stringstream ss;
	ss<<rand((Year*)0);
	for(auto _:range(5)){
		ss<<char('a'+std::rand()%26);
	}
	return Event_key(ss.str());
}

bool operator==(Event_key const& a,const char *s){
	if(!s) return 0;
	return a.get()==s;
}

std::ostream& operator<<(std::ostream& o,Event_key const& a){
	return o<<a.get();
}

Event_key decode(JSON_value in,const Event_key*){
	//return Event_key{decode(in,(std::string*)nullptr)};
	if(in.type()!=simdjson::dom::element_type::STRING){
		throw "expected str";
	}
	return Event_key{in.get_string()};
}

Event_key decode(std::string_view s,Event_key const*){
	return Event_key(s);
}

}
