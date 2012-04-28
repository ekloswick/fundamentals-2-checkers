#include <iostream>
#include "BankAccount.h"
using namespace std;

BankAccount::BankAccount(double b, double r, int h) {
  if (b > 0 && r > 0) {   //checks for good balance and rate
    balance = b;
    rate = r;
    hasBoat = h;
  } else {                //if the inputs are bad, set to default values
    balance = 10000;
    rate = 5;
    hasBoat = 0;
  }
}

BankAccount::~BankAccount() {

}

void BankAccount::print() {   //prints all of your basic bank account info
  cout << "Your balance is: " << balance << endl;
  cout << "Your interest rate is: " << rate << endl;
  if (hasBoat == 0) {        //tells you if you have a boat or not
    cout << "You don't have a boat, loser." << endl;
  }
  else {
    cout << "You have a boat, nice job." << endl;
  } 
  return;
}

void BankAccount::deposit(double d) {
  balance=balance+d;         //adds d to your balance
  return;
}

void BankAccount::withdrawl(double w) {
  if(w > balance) {          //checks if you're trying to overdraw
    cout << "You don't have enough money, cheapskate." << endl;
    return;
  }
  else {                     //if you have enough money, takes it away from your balance
    balance=balance-w;
  }
  return;
}

void BankAccount::buyBoat() {
  if (balance>=5000) {       //if you have enough money to buy a boat, takes $5000 from your balance and gives you a boat
    hasBoat=1;
    balance=balance-5000;
  } else {
    cout << "You are too poor sorry." << endl;  //if you can't afford a boat, prints error message
  }
  return;
}
