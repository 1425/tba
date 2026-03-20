#include "year.h"

namespace tba{

Year::Year(int i1):i(i1){
	if(!valid()){
		std::ostringstream ss;
		ss<<"year:"<<i;
		throw std::invalid_argument{ss.str()};
	}
}

Year& Year::operator=(int x){
	i=x;
	if(!valid()){
		throw std::invalid_argument("year out of range");
	}
	return *this;
}

bool Year::valid()const{
	return i>=1992 && i<2092;
}

Year rand(Year const*){
	return Year(1992+::rand()%100);
}

short Year::get()const{
	return i;
}

bool Year::operator==(Year const& a)const{
	return i==a.i;
}

bool Year::operator==(int a)const{
	return i==a;
}

bool Year::operator>=(int a)const{
	return i>=a;
}

bool Year::operator<(int a)const{
	return i<a;
}

std::ostream& operator<<(std::ostream& o,Year a){
	return o<<a.get();
}

Year& operator++(Year& a){
	a.i++;
	if(!a.valid()){
		a.i--;
		throw std::range_error{"Year too high"};
	}
	return a;
}

Year& Year::operator--(){
	i--;
	if(!valid()){
		i++;
		throw std::range_error{"Year too low"};
	}
	return *this;
}

Year operator++(Year& a,int){
	auto r=a;
	++a;
	return r;
}

Year operator-(Year a,int b){
	return Year{a.get()-b};
}

Year operator+(Year a,int b){
	return Year{a.get()+b};
}

Year decode(JSON_value in,const Year*){
	return Year{decode(in,(int*)nullptr)};
}

Year decode(std::string_view a,Year const*){
	return Year(stoi(std::string(a)));
}

std::string operator+(std::string const& a,Year b){
	std::stringstream ss;
	ss<<a<<b;
	return ss.str();
}

}

short std::hash<tba::Year>::operator()(tba::Year a){
	return a.get();
}
