Automate.o: Automate.cpp Automate.hpp
	g++ -g -Wall -c Automate.cpp -o Automate.o
Syntax.o: Syntax.cpp Syntax.hpp
	g++ -g -Wall -c Syntax.cpp -o Syntax.o
prog: Parser.cpp Automate.o Syntax.o
	g++ -g -Wall Parser.cpp Automate.o Syntax.o -o prog
