#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <iostream>
using namespace std;

class BankAccount {

 public:
  BankAccount(double b = 10000, double r = 5, int h = 0);  //sets default bank account info
  ~BankAccount();
  void print();            //prints boat loan info
  void deposit(double);    //changes the balance by adding money
  void withdrawl(double);  //changes the balance by taking away money
  void buyBoat();          //changes hasBoat to 1
  
 protected:
  double balance;          //how much money you have
  double rate;             //interest rate
  int hasBoat;             //1 if you have a boat
  
};

#endif
