CXXFLAGS=-std=c++20 -Wall -Wextra -pedantic -Ofast

LIBS=-lcurl -lsqlite3 -lpthread

demo: demo.o curl.o db.o rapidjson.o data.o util.o
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

.PHONY: clean
clean:
	rm -f demo *.o
