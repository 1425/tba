#include "district_key.h"
#include "year.h"

namespace tba{

District_key::District_key(std::string const& s){
	Year{atoi(s.c_str())};//check that starts with a year
	//then a 2-3 letter code.
	if( !(s.size()>=6 && s.size()<=7) ){
		throw std::invalid_argument{[&](){
			std::ostringstream ss;
			ss<<"Expected District_key, found:"<<s;
			return ss.str();
		}()};
	}

	assert(s.size()<buf.size());

	bzero(&buf[0],buf.size());
	memcpy(&buf[0],s.c_str(),s.size());
}

District_key::District_key(const char *s){
	if(!s){
		throw std::invalid_argument("null");
	}
	*this=District_key(std::string(s));
}

std::optional<District_key> District_key::parse(std::string const& s){
	//obviously not an efficient way to do this.
	try{
		return District_key(s);
	}catch(...){
		return std::nullopt;
	}
}

std::string District_key::get()const{
	return std::string(&buf[0]);
}

std::string District_key::location_part()const{
	auto s=get();
	return s.substr(4,s.size());
}

std::strong_ordering District_key::operator<=>(District_key const& a)const{
	//This is not understood by clang++ 20.1.8 or g++ 15
	//so leave it out.
	//static_assert(buf.size()==8);
	
	auto x=*(uint64_t*)&buf[0];
	auto y=*(uint64_t*)&a.buf[0];

	return x<=>y;
}

bool District_key::operator==(District_key const& a)const{
	return (*this<=>a)==std::strong_ordering::equal;
}

std::ostream& operator<<(std::ostream& o,District_key const& a){
	return o<<a.get();
}

bool operator==(District_key const& a,std::string const& b){
	return a.get()==b;
}

District_key decode(JSON_value in,const District_key *){
	return District_key{decode(in,(std::string*)nullptr)};
}

}
