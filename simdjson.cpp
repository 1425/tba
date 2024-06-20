#include "simdjson.h"
#include "util.h"

namespace tba{

Decode_error::Decode_error(const char *s,const char *value1,std::string what):
	path({s}),value(value1),description(what)
{}

Decode_error::Decode_error(const char *s,std::string value1,std::string what):
	path({s}),value(value1),description(what)
{}

std::ostream& operator<<(std::ostream& o,Decode_error const& a){
	o<<"Decode_error(\n";
	o<<"\tfrom:"<<a.value<<"\n";
	o<<"\tpath:"<<a.path<<"\n";
	o<<"\tdescription:"<<a.description<<"\n";
	return o<<")";
}

std::string decode(JSON_value in,std::string const*){
	if(in.type()!=simdjson::dom::element_type::STRING){
		throw Decode_error("string",as_string(in),"foo4");
	}

	try{

		std::string_view s=in.get_string();
		return std::string{s.begin(),s.end()};
	}catch(...){
		TBA_NYI
	}
}

int decode(JSON_value a,int const*){
	switch(a.type()){
		case simdjson::dom::element_type::INT64:
			return a.get_int64();
		case simdjson::dom::element_type::NULL_VALUE:
			throw Decode_error{"int",as_string(a),"wrong type, got null"};
		default:
			TBA_PRINT(a.type())
			TBA_NYI
	}
}

unsigned decode(JSON_value a,unsigned const*){
	switch(a.type()){
		case simdjson::dom::element_type::INT64:{
			int64_t r=a.get_int64();
			assert(r>=0);
			return r;
		}
		default:
			TBA_PRINT(a.type())
			TBA_NYI
	}
}

long decode(JSON_value a,long const*){
	switch(a.type()){
		case simdjson::dom::element_type::INT64:
			return a.get_int64();
		default:
			TBA_PRINT(a.type());
			TBA_NYI
	}
}

bool decode(JSON_value a,bool const*){
	switch(a.type()){
		case simdjson::dom::element_type::BOOL:
			return a.get_bool();
		default:
			TBA_PRINT(a.type());
			TBA_NYI
	}
}

double decode(JSON_value a,double const*){
	switch(a.type()){
		case simdjson::dom::element_type::DOUBLE:
			return a.get_double();
		case simdjson::dom::element_type::INT64:
			return a.get_int64();
		default:
			TBA_PRINT(a.type());
			TBA_NYI
	}

	(void)a;
	TBA_NYI/*if(!a.is_scalar()){
		TBA_NYI
	}
	return a.get_double();*/
}

std::nullptr_t decode(JSON_value,std::nullptr_t const*){
	TBA_NYI
}

std::nullptr_t decode(JSON_object in,std::nullptr_t const*){
	if(in.size()){
		throw Decode_error("nullptr_t",as_string(in),"non-empty object");
	}
	TBA_PRINT(in);
	TBA_NYI
}

std::string decode2(std::string_view,std::string const*){
	TBA_NYI
}

std::nullptr_t decode(std::nullptr_t,std::nullptr_t const*){
	return nullptr;
}

}
