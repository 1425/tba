#ifndef MACRO_H
#define MACRO_H

#define TBA_INST(A,B) A B;

#define TBA_MAKE_INST(NAME,ITEMS)\
	struct NAME{ \
		ITEMS(TBA_INST) \
		auto operator<=>(NAME const&)const=default;\
	};\
	std::ostream& operator<<(std::ostream&,NAME const&);\
	NAME decode(tba::JSON_value,const NAME*);\
	NAME decode(tba::JSON_object,const NAME*);\
	NAME decode(tba::JSON_array,const NAME*);\
	NAME decode(std::nullptr_t,NAME const*);\
	std::optional<NAME> maybe_decode(tba::JSON_value,const NAME*);\
	std::optional<NAME> maybe_decode(tba::JSON_object,const NAME*);\
	std::optional<NAME> maybe_decode(tba::JSON_array,const NAME*);\
	std::optional<NAME> maybe_decode(std::nullptr_t,NAME const*);\

#define TBA_SINGLE_ARG(A,B) A,B

#define TBA_DECODE_FAIL(NAME) \
	std::optional<NAME> maybe_decode(JSON_value in,NAME const*){\
		try{\
			return decode(in,(NAME*)nullptr);\
		}catch(...){\
			return std::nullopt;\
		}\
	}\
	std::optional<NAME> maybe_decode(std::nullptr_t,NAME const*){\
		return std::nullopt;\
	}


#define TBA_PRINT_ITEM(A,B) o<<""#B<<":"<<a.B<<" ";

#define TBA_DECODE_B1(A,B) std::optional<A> VAR_##B;

#define TBA_DECODE_B2(A,B) \
	else if(k==""#B){\
		try{\
			VAR_##B=decode(p.value,(A*)nullptr);\
		}catch(Decode_error e){\
			e.path.push_back(""#B);\
			throw e;\
		}\
	}

#define TBA_DECODE_B3(A,B) [&](){\
	if(VAR_##B){ \
		return *VAR_##B;\
	}\
	try{\
		return decode(nullptr,(A*)0);\
	}catch(Decode_error a){\
		a.path.push_back(""#B);\
		throw a;\
	}\
}(),

#define TBA_DECODE_B(NAME,ITEMS) \
	NAME decode(JSON_object in,const NAME*){\
		ITEMS(TBA_DECODE_B1)\
		for(auto p:in){\
			std::string_view k=p.key;\
			(void)k;\
			try{\
				if(0){} ITEMS(TBA_DECODE_B2)\
			}catch(Decode_error e){\
				e.path.push_back(""#NAME);\
				throw e;\
			}\
		}\
		return NAME{ITEMS(TBA_DECODE_B3)};\
	}

#define TBA_INST_PRINT(NAME,ITEMS)\
	std::ostream& operator<<(std::ostream& o,NAME const& a){\
		(void)a;\
		o<<""#NAME<<"(";\
		ITEMS(TBA_PRINT_ITEM)\
		return o<<")";\
	}\

#define TBA_MAYBE_DECODE_NULL(A,B)\
	if(!VAR_##B){\
		VAR_##B=maybe_decode(nullptr,(A*)0);\
		if(!VAR_##B) return std::nullopt;\
	}

#define TBA_MAYBE_DECODE_LAST(A,B) [&](){\
		assert(VAR_##B);\
		return *VAR_##B;\
	}(),

#define TBA_MAYBE_DECODE_INNER(A,B) \
	if(k==""#B){\
		VAR_##B=maybe_decode(p.value,(A*)nullptr); \
		if(!VAR_##B) return std::nullopt;\
		any=1;\
	}

#define TBA_MAYBE_DECODE(NAME,ITEMS)\
	std::optional<NAME> maybe_decode(JSON_object in,NAME const*){\
		try{\
			ITEMS(TBA_DECODE_B1)\
			for(auto p:in){\
				bool any=0;\
				std::string_view k=p.key;\
				(void)k;\
				ITEMS(TBA_MAYBE_DECODE_INNER)\
				if(!any){\
				}\
			}\
			ITEMS(TBA_MAYBE_DECODE_NULL)\
			return NAME{ITEMS(TBA_MAYBE_DECODE_LAST)};\
		}catch(...){\
			assert(0);\
		}\
	}\
	std::optional<NAME> maybe_decode(JSON_value in,NAME const* x){\
		if(in.type()!=simdjson::dom::element_type::OBJECT){\
			return std::nullopt;\
		}\
		return maybe_decode(in.get_object(),x);\
	}\
	std::optional<NAME> maybe_decode(std::nullptr_t in,NAME const* x){\
		try{\
			return decode(in,x);\
		}catch(...){\
			return std::nullopt;\
		}\
	}


#define TBA_MAKE_IMPL(NAME,ITEMS)\
	TBA_INST_PRINT(NAME,ITEMS)\
	TBA_DECODE_B(NAME,ITEMS)\
	NAME decode(JSON_array,const NAME*){\
		std::cout<<"hello2\n";\
		TBA_NYI\
	}\
	NAME decode(JSON_value in,NAME const* x){\
		if(in.type()!=simdjson::dom::element_type::OBJECT){\
			throw Decode_error{""#NAME,as_string(in),"expected object"};\
		}\
		return decode(in.get_object(),x);\
	}\
	NAME decode(std::nullptr_t,NAME const*){\
		throw Decode_error{""#NAME,"null","exprected object"};\
	}\
	TBA_MAYBE_DECODE(NAME,ITEMS)


#endif
