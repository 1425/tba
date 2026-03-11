#include "match_key.h"

namespace tba{

Match_key::Match_key(std::string s1):s(std::move(s1)){
	//format: event_key / "_" / level / (maybe set # and 'm') / match #
	auto check=[&](bool b){
		if(b) return;
		throw std::invalid_argument{[&](){
			std::ostringstream ss;
			ss<<"Expected Match_key, found:"<<s;
			return ss.str();
		}()};
	};

	Year{atoi(s.c_str())};
	size_t at=4;
	while(at<s.size() && s[at]!='_') at++;

	check(s[at]=='_');
	at++;

	at+=2;//skip match type, which is 2 chars long.
	check(at<s.size());

	/*while(at<s.size()){
		check(isdigit(s[at]));
		at++;
	}*/
}

std::string const& Match_key::get()const{ return s; }

Year Match_key::year()const{
	return Year(atoi(s.c_str()));
}

Match_key decode(JSON_value in,const Match_key*){
	return Match_key{decode(in,(std::string*)nullptr)};
}

Match_key decode2(std::string_view a,Match_key const*){
	return Match_key{std::string(a)};
}

std::ostream& operator<<(std::ostream& o,Match_key const& a){
	return o<<a.get();
}

}
