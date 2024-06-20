#ifndef TBA_UTIL_H
#define TBA_UTIL_H

#include<iostream>
#include<map>
#include<vector>
#include<variant>
#include<optional>
#include<sstream>

#define TBA_NYI { std::cout<<"NYI "<<__FILE__<<":"<<__LINE__<<"\n"; exit(1); }
#define TBA_PRINT(X) { std::cout<<""#X<<":"<<(X)<<"\n"; }

namespace tba{

template<typename A,typename B,typename C,typename D,typename E,typename F,typename G>
std::ostream& operator<<(std::ostream& o,std::tuple<A,B,C,D,E,F,G> const& a);

template<typename T>
std::ostream& operator<<(std::ostream& o,std::optional<T> const& a);

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

template<typename T,size_t N>
std::ostream& operator<<(std::ostream& o,std::array<T,N> const& a){
	o<<"[ ";
	for(auto const& elem:a){
		o<<elem<<" ";
	}
	return o<<"]";
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

template<typename Func,typename T>
auto mapf(Func f,std::vector<T> const& a){
	std::vector<decltype(f(a[0]))> r;
	for(auto elem:a){
		r|=f(elem);
	}
	return r;
}

template<typename T>
void print_lines(T t){
	for(auto elem:t){
		std::cout<<elem<<"\n";
	}
}

auto as_string(auto const& x){
	std::stringstream ss;
	ss<<x;
	return ss.str();
}

}

#endif
