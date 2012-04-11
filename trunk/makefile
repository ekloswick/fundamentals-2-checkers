all: main

main: piece.o checkers.o main.o
	g++ piece.o checkers.o main.o -o main

main.o: main.cpp
	g++ -c main.cpp

piece.o: piece.cpp
	g++ -c piece.cpp

checkers.o: checkers.cpp
	g++ -c checkers.cpp

clean:
	rm *~ *.o main
