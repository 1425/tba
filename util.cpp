#include "util.h"
#include<numeric>
#include "simdjson.h"

namespace tba{

std::vector<size_t> range(size_t lim){
	std::vector<size_t> r(lim);
	std::iota(begin(r),end(r),0);
	return r;
}

std::vector<int> range(int start,int lim){
	std::vector<int> r(lim-start);
	std::iota(begin(r),end(r),start);
	return r;
}

std::ostream& operator<<(std::ostream& o,std::nullptr_t){
	return o<<"NULL";
}

double rand(double const*){
	return std::rand();
}

short rand(short const*){
	return std::rand();
}

int rand(int const*){
	return std::rand();
}

long rand(long const*){
	return std::rand();
}

unsigned rand(unsigned const*){
	TBA_NYI
}

bool rand(bool const*){
	return std::rand()%2;
}

std::nullptr_t rand(std::nullptr_t const*){
	TBA_NYI
}

std::string rand(std::string const*){
	return "foo"+as_string(std::rand());
}

}
