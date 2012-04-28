#include <iostream>
#include "Package.h"
using namespace std;

Package::Package(string n, string a, string c, string s, int z, int r, int w) {
  name = n;     //set all package info to desired strings and ints
  address = a;
  city = c;
  state = s;
  zipcode = z;
  if (w > 0) { //checks for bad weight
    weight = w;
  }
  else {       //sets weight to 5 if given a bad value
    weight = 5;
  }
  if (r > 0) { //checks for bad rate
    rate = r;
  }
  else {       //sets rate to 3.21 if given bad value
    rate = 3.21;
  }
  int t = CalculateCost(); //t is a holder variable
  if (t > 0) { //checks for bad cost value
    cost = CalculateCost();
  }
  else {       //sets cost to 10.99 if given bad value 
    cost = 10.99;
  }
}

//Package::~Package() {

//}

double Package::CalculateCost() {
  double total = weight * rate; //total is a holder variable
  return total;
}

void Package::print() {         //prints desired information 
  cout << "Name: " << name << endl;
  cout << "Address: " << address << endl;
  cout << "City: " << city << endl;
  cout << "State: " << state << endl;
  cout << "Zip Code: " << zipcode << endl;
  cout << "Weight: " << weight << endl;
  cout << "Cost: " << cost << endl;
}
