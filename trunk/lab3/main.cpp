/**********************************
Craig Cahillane and Rachael Creager
Lab #3
Part 1
14 February 2012
**********************************/

#include <iostream>
#include "BankAccount.h"
#include "BoatLoan.h"
#include "CrewStats.h"
using namespace std;

int main() {

  cout << "Welcome to the Pirate Bank!!!!!" << endl;

  BankAccount e;		//Default bank account is boring 
  BankAccount f(3000,5,1);	//Unable to make a boat with only 3000, returns error message

  CrewStats a;			//Default Crew is happy
  CrewStats b(100,1,10,1);	//Nondefault crew is probably gonna mutiny

  BoatLoan c;			//Default loan with no cannons
  BoatLoan d(100000,1,200,100); //Nondefault loan with cannons

  cout << "Crew A mutiny?" << endl; //Check if the default crew mutinies (they won't)
  a.canhazmutiny();
  cout << "Crew B mutiny?" << endl; //Check if the nondefault crew mutinies (they do)
  b.canhazmutiny();

  e.print();			//Print out the default bank account information
  f.print();			//Print out the nondefault bank account information

  c.print();			//Print out default boat loan information
  d.print();			//Print out nondefault boat loan information
  
  return 0;

}
