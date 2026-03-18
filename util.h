#ifndef TBA_UTIL_H
#define TBA_UTIL_H

#include<iostream>
#include<map>
#include<vector>
#include<variant>
#include<optional>

#define TBA_NYI { std::cout<<"NYI "<<__FILE__<<":"<<__LINE__<<"\n"; exit(1); }
#define TBA_PRINT(X) { std::cout<<""#X<<":"<<(X)<<"\n"; }

#define RM_CONST(X) typename std::remove_cv<X>::type
#define RM_REF(X) typename std::remove_reference<X>::type
#define ELEM(X) RM_CONST(RM_REF(decltype(*std::begin(X))))

namespace tba{

template<typename A,typename B,typename C,typename D,typename E,typename F,typename G>
std::ostream& operator<<(std::ostream& o,std::tuple<A,B,C,D,E,F,G> const& a);

template<typename T,size_t N>
std::ostream& operator<<(std::ostream&,std::array<T,N> const&);

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
constexpr auto mapf(Func f,std::vector<T> const& a){
	std::vector<decltype(f(a[0]))> r;
	r.reserve(a.size());
	for(auto const& elem:a){
		r|=f(elem);
	}
	return r;
}

template<typename T>
void print_lines(T t){
	for(auto const& elem:t){
		std::cout<<elem<<"\n";
	}
}

nullptr_t rand(nullptr_t const*);
bool rand(bool const*);
short rand(short const*);
int rand(int const*);
long rand(long const*);
unsigned rand(unsigned const*);
double rand(double const*);
std::string rand(std::string const*);

template<
	typename A,typename B,typename C,typename D,
	typename E,typename F,typename G
> auto rand(std::tuple<A,B,C,D,E,F,G> const*){
	return std::make_tuple(
		rand((A*)0),
		rand((B*)0),
		rand((C*)0),
		rand((D*)0),
		rand((E*)0),
		rand((F*)0),
		rand((G*)0)
	);
}

template<
	typename A,typename B,typename C,typename D,
	typename E,typename F,typename G,typename H,
	typename I
> auto rand(std::tuple<A,B,C,D,E,F,G,H,I> const*){
	return std::make_tuple(
		rand((A*)0),
		rand((B*)0),
		rand((C*)0),
		rand((D*)0),
		rand((E*)0),
		rand((F*)0),
		rand((G*)0),
		rand((H*)0),
		rand((I*)0)
	);
}

template<typename A,typename B>
std::pair<A,B> rand(std::pair<A,B> const*){
	return std::make_pair(rand((A*)0),rand((B*)0));
}

template<typename T>
std::vector<T> rand(std::vector<T> const*){
	std::vector<T> r;
	size_t lim=std::rand()%10;
	for(size_t i=0;i<lim;i++){
		r|=rand((T*)0);
	}
	return r;
}

template<typename K,typename V>
std::map<K,V> rand(std::map<K,V> const*){
	TBA_NYI
}

template<typename T,size_t N>
std::array<T,N> rand(std::array<T,N> const*){
	TBA_NYI
}

template<typename A,typename B,typename C>
std::tuple<A,B,C> rand(std::tuple<A,B,C> const*){
	TBA_NYI
}

template<typename T>
std::optional<T> rand(std::optional<T> const*){
	if(std::rand()%2){
		return rand((T*)0);
	}
	return std::nullopt;
}

template<typename A,typename B>
std::variant<A,B> rand(std::variant<A,B> const*){
	TBA_NYI
}

template<typename T>
T choose(std::vector<T> const&);

template<typename T,size_t N>
T choose(std::array<T,N> const& a){
	static_assert(N!=0);
	return a[std::rand()%N];
}

}

#endif
