#ifndef BOATLOAN_H
#define BOATLOAN_H
#include <iostream>
#include "BankAccount.h"
using namespace std;

class BoatLoan {

 public:
  BoatLoan(int a = 5000.0, int c = 0, int l = 100, int h = 50); //sets default values for a boat loan
  ~BoatLoan();
  void print();    //prints basic loan info
  BankAccount bank(double balance = 5000.0,double rate = 5.0,int hasBoat = 1); //includes default bank account info

 private:
  int loanAmount;  //information for a boat loan
  int hasCannons;
  int boatLength;
  int boatHeight;
  
};

#endif
