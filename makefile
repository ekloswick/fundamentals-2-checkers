all: main

main: checkers.o main.o
        g++ checkers.o main.o -o main

main.o: main.cpp
        g++ -c main.cpp

checkers.o: checkers.cpp
        g++ -c checkers.cpp

clean:
        rm *~ *.o main
