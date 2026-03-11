#CXXFLAGS=-std=c++20 -Wall -Wextra -pedantic -Ofast -fdiagnostics-color=always
CXXFLAGS=-std=c++23 -Wall -Wextra -pedantic -Og -g -fdiagnostics-color=always
#CXXFLAGS=-std=c++23 -Os

LIBS=-lcurl -lsqlite3 -lpthread -lsimdjson

OBJS=\
     team_key.o\
     match_key.o\
     event_key.o\
     district_key.o\
     demo.o\
     curl.o\
     db.o\
     data.o\
     util.o\
     simdjson.o\
     year.o\
     event_insights.o\

demo: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

.PHONY: clean
clean:
	rm -f demo *.o
