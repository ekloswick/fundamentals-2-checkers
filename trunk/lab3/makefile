all: main mainpart2 

main: main.o BankAccount.o BoatLoan.o CrewStats.o
	g++ main.o BankAccount.o BoatLoan.o CrewStats.o -o main

main.o: main.cpp
	g++ -c main.cpp

BankAccount.o: BankAccount.cpp
	g++ -c BankAccount.cpp

BoatLoan.o: BoatLoan.cpp
	g++ -c BoatLoan.cpp

CrewStats.o: CrewStats.cpp
	g++ -c CrewStats.cpp

mainpart2: mainpart2.o Package.o TwoDayPackage.o OvernightPackage.o
	g++ mainpart2.o Package.o TwoDayPackage.o OvernightPackage.o -o mainpart2

mainpart2.o: mainpart2.cpp
	g++ -c mainpart2.cpp

Package.o: Package.cpp
	g++ -c Package.cpp

TwoDayPackage.o: TwoDayPackage.cpp
	g++ -c TwoDayPackage.cpp

OvernightPackage.o: OvernightPackage.cpp
	g++ -c OvernightPackage.cpp

clean: 
	rm *.o *~ main mainpart2
