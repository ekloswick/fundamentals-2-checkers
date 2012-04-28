all: main

main: piece.o checkers.o main.o
	g++ piece.o checkers.o main.o -o Checkers -Wall -Wextra

main.o: main.cpp
	g++ -c main.cpp -Wall -Wextra

piece.o: piece.cpp
	g++ -c piece.cpp -Wall -Wextra

checkers.o: checkers.cpp
	g++ -c checkers.cpp -Wall -Wextra

clean:
	rm *~ *.o Checkers
