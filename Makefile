Automate.o: Automate.cpp Automate.hpp
	g++ -g -Wall -c Automate.cpp -o Automate.o
prog: Parser.cpp Automate.o
	g++ -g -Wall Parser.cpp Automate.o -o prog
