#ifndef TBA_UTIL_H
#define TBA_UTIL_H

#include<iostream>
#include<map>
#include<vector>
#include<variant>

#define TBA_NYI { std::cout<<"NYI "<<__FILE__<<":"<<__LINE__<<"\n"; exit(1); }

namespace tba{

std::ostream& operator<<(std::ostream&,nullptr_t);

template<typename A,typename B>
std::ostream& operator<<(std::ostream& o,std::pair<A,B> const& p){
	return o<<"("<<p.first<<","<<p.second<<")";
}

template<typename A,typename B>
std::ostream& operator<<(std::ostream& o,std::map<A,B> const& a){
	o<<"{";
	for(auto elem:a) o<<elem;
	return o<<"}";
}

template<typename T>
std::ostream& operator<<(std::ostream& o,std::vector<T> const& a){
	o<<"[ ";
	for(auto elem:a) o<<elem<<" ";
	return o<<"]";
}

template<typename T>
std::ostream& operator<<(std::ostream& o,std::optional<T> const& a){
	if(a) return o<<*a;
	return o<<"NULL";
}

template<typename T>
std::vector<T>& operator|=(std::vector<T> &a,T t){
	a.push_back(t);
	return a;
}

template<typename T>
std::vector<T>& operator|=(std::vector<T> &a,std::vector<T> b){
	for(auto elem:b){
		a|=elem;
	}
	return a;
}

template<typename... A>
std::ostream& operator<<(std::ostream& o,std::variant<A...> const& a){
	std::visit([&](auto &&elem){ o<<elem; },a);
	return o;
}

template<typename A,typename B,typename C>
std::ostream& operator<<(std::ostream& o,std::tuple<A,B,C> const& a){
	return o<<"("<<std::get<0>(a)<<","<<std::get<1>(a)<<","<<std::get<2>(a)<<")";
}

template<typename A,typename B,typename C,typename D,typename E,typename F,typename G>
std::ostream& operator<<(std::ostream& o,std::tuple<A,B,C,D,E,F,G> const& a){
	o<<"(";
	o<<std::get<0>(a)<<",";
	o<<std::get<1>(a)<<",";
	o<<std::get<2>(a)<<",";
	o<<std::get<3>(a)<<",";
	o<<std::get<4>(a)<<",";
	o<<std::get<5>(a)<<",";
	o<<std::get<6>(a);
	return o<<")";
}

std::vector<size_t> range(size_t);
std::vector<int> range(int,int);

}

#endif
