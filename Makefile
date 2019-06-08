test_ldsketch: main.cpp dyn_tbl.cpp dyn_tbl.hpp LDSketch.cpp LDSketch.hpp extract.cpp extract.h
	g++ -std=c++11 -Wall -o test_ldsketch main.cpp dyn_tbl.cpp LDSketch.cpp extract.cpp

clean:
	rm -rf test_ldsketch
