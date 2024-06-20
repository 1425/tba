CXXFLAGS=-std=c++20 -Wall -Wextra -pedantic -Ofast

LIBS=-lcurl -lsqlite3 -lpthread -lsimdjson

demo: demo.o curl.o db.o data.o util.o simdjson.o
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

.PHONY: clean
clean:
	rm -f demo *.o
