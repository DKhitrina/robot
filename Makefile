Automate.o: Automate.cpp Automate.hpp
	g++ -g -Wall -c Automate.cpp -o Automate.o
Semantic.o: Semantic.cpp Semantic.hpp
	g++ -g -Wall -c Semantic.cpp -o Semantic.o
prog: Parser.cpp Automate.o Semantic.o
	g++ -g -Wall Parser.cpp Automate.o Semantic.o -o prog
