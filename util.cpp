#include "util.h"
#include<numeric>

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

}
