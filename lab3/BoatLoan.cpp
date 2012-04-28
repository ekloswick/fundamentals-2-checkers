#include <iostream>
#include "BoatLoan.h"
using namespace std;

BoatLoan::BoatLoan(int a, int c, int l, int h) {
  if (a > 0 && c > 0 && l >0 && h >0) {  //checks for bad loan input & sets variables if they're alright
  loanAmount = a;
  hasCannons = c;
  boatLength = l;
  boatHeight = h;
  } else {   //if any of the inputs are bad...
    cout << "You can't make a boat like that." << endl; //error message
    loanAmount = 5000;   //sets default values
    hasCannons = 0;
    boatLength = 100;
    boatHeight = 50;
  }
}

BoatLoan::~BoatLoan() {

}

void BoatLoan::print() {   //prints all of the boat loan essentials
  cout << "Your loan amount is: " << loanAmount << endl;
  if (hasCannons == 1) {   //tells you if the boat has cannons
    cout << "Your boat has cannons." << endl;
  } else {
    cout << "Your boat has no cannons." << endl;
  }
  cout << "Your boat is " << boatLength << " feet long." << endl;
  cout << "Your boat is " << boatHeight << " feet tall." << endl;
}
