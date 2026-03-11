#CXXFLAGS=-std=c++20 -Wall -Wextra -pedantic -Ofast -fdiagnostics-color=always
CXXFLAGS=-std=c++23 -Wall -Wextra -pedantic -Og -g -fdiagnostics-color=always
#CXXFLAGS=-std=c++23 -Os

LIBS=-lcurl -lsqlite3 -lpthread -lsimdjson

OBJS=\
     demo.o\
     curl.o\
     db.o\
     data.o\
     util.o\
     simdjson.o\
     year.o\

demo: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

.PHONY: clean
clean:
	rm -f demo *.o
