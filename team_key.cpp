#include "team_key.h"

namespace tba{
	
Team_key::Team_key(std::string const& s){
	auto ok=(
		s.size()>=3 &&
		s[0]=='f' &&
		s[1]=='r' &&
		s[2]=='c' &&
		s.size()-3<buf.size()
	);
	if(!ok){
		throw std::invalid_argument("Team_key: "+s);
	}

	//making sure that the string is not just null terminated, but any
	//later char is set to 0.
	bzero(&buf[0],buf.size());
	memcpy(&buf[0],s.c_str()+3,s.size()-3);
}

Team_key::Team_key(std::string_view s){
	assert(s.size()>=3);
	assert(s[0]=='f');
	assert(s[1]=='r');
	assert(s[2]=='c');
	assert(s.size()-3<buf.size());

	//making sure that the string is not just null terminated, but any
	//later char is set to 0.
	bzero(&buf[0],buf.size());
	memcpy(&buf[0],s.data()+3,s.size()-3);
}

Team_key::Team_key(const char *s){
	assert(s);
	*this=Team_key(std::string_view(s));
}

Team_key::Team_key(int x){
	std::stringstream ss;
	ss<<"frc"<<x;
	*this=Team_key(ss.str());
}

std::string Team_key::str()const{
	return "frc"+std::string(&(buf[0]));
	//return s;
}

uint64_t Team_key::data()const{
	return *(uint64_t*)(&buf[0]);
}

std::strong_ordering Team_key::operator<=>(Team_key const& a)const{
	//Not allowed by some older compilers, so leave this out.
	//static_assert(buf.size()==8);

	auto x=*(uint64_t*)(&buf[0]);
	auto y=*(uint64_t*)(&a.buf[0]);

	return x<=>y;
}

bool Team_key::operator==(Team_key const& a)const{
	return (*this<=>a)==std::strong_ordering::equal;
}

std::ostream& operator<<(std::ostream& o,Team_key const& a){
	//return o<<"Team_key("<<a.str()<<")";
	return o<<a.str();
}

Team_key decode(JSON_value in,const Team_key*){
	if(in.type()==simdjson::dom::element_type::STRING){
		return Team_key{in.get_string()};
	}
	return Team_key{decode(in,(std::string*)0)};
}

Team_key decode2(std::string_view in,Team_key const*){
	return Team_key{std::string(in)};
}

}

size_t std::hash<tba::Team_key>::operator()(tba::Team_key a){
	return a.data();
}
