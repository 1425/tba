#include "simdjson.h"
#include "util.h"

namespace tba{

Decode_error::Decode_error(const char *s,const char *value1,std::string what):
	path({s}),value(value1),description(what)
{}

Decode_error::Decode_error(const char *s,std::string value1,std::string what):
	path({s}),value(value1),description(what)
{}

Decode_error::Decode_error(std::string a,std::string b,std::string c):
	path({a}),
	value(b),
	description(c)
{}

std::ostream& operator<<(std::ostream& o,Decode_error const& a){
	o<<"Decode_error(\n";
	o<<"\tfrom:"<<a.value<<"\n";
	o<<"\tpath:"<<a.path<<"\n";
	o<<"\tdescription:"<<a.description<<"\n";
	return o<<")";
}

std::optional<std::nullptr_t> maybe_decode(JSON_object in,std::nullptr_t const*){
	if(in.size()){
		return std::nullopt;
	}
	TBA_NYI
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
		case simdjson::dom::element_type::ARRAY:
			throw Decode_error{"array",as_string(a),"wrong type, got array"};
		case simdjson::dom::element_type::DOUBLE:
			//could see if it's a whole number and coerce it to be an int.
			throw Decode_error{"double",as_string(a),"wrong type, got double"};
		case simdjson::dom::element_type::BOOL:
			throw Decode_error{"bool",as_string(a),"wrong type, got bool"};
		default:
			TBA_PRINT(a.type())
			TBA_NYI
	}
}

std::optional<int> maybe_decode(JSON_value a,int const*){
	switch(a.type()){
		case simdjson::dom::element_type::INT64:
			return a.get_int64();
		case simdjson::dom::element_type::NULL_VALUE:
		case simdjson::dom::element_type::ARRAY:
			return std::nullopt;
		case simdjson::dom::element_type::DOUBLE:
			//could see if it's a whole number and coerce it to be an int.
			return std::nullopt;
		case simdjson::dom::element_type::BOOL:
			return std::nullopt;
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
		case simdjson::dom::element_type::INT64:
			throw Decode_error("int",as_string(a),"expected bool, got int");
		default:
			TBA_PRINT(a.type());
			TBA_PRINT(a);
			TBA_NYI
	}
}

std::optional<bool> maybe_decode(JSON_value in,bool const* x){
	try{
		return decode(in,x);
	}catch(...){
		return std::nullopt;
	}
}

std::optional<std::string> maybe_decode(JSON_value in,std::string const* x){
	try{
		return decode(in,x);
	}catch(...){
		return std::nullopt;
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

std::string decode2(std::string_view a,std::string const*){
	return std::string(a);
}

std::nullptr_t decode(std::nullptr_t,std::nullptr_t const*){
	return nullptr;
}

std::optional<bool> maybe_decode(std::nullptr_t,bool const*){
	return std::nullopt;
}

std::optional<int> maybe_decode(std::nullptr_t,int const*){
	return std::nullopt;
}

#define X(T) T decode(std::nullptr_t,T const*){ throw Decode_error("nullptr_t","null","Expected "#T); }
X(double)
X(std::string)
X(unsigned)
#undef X

}
