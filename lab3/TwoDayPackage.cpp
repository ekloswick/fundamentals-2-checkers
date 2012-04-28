#include <iostream>
#include "TwoDayPackage.h"
#include "Package.h"
using namespace std;

TwoDayPackage::TwoDayPackage(int f) : Package("Rachael", "BP 309", "Michiana", "In", 54321, 3.21, 7) {
  flatrate = f;           //first, the function takes in the initialized values for the package in the line above, then sets the flatrate to f
  cost = CalculateCost(); //sets cost to the double returned by calculatecost
}

//TwoDayPackage::~TwoDayPackage() { //Professor Emrich told us to take this out

//}

double TwoDayPackage::CalculateCost() {  //Returns the cost of a two day package
  cost = 3.21 * weight + flatrate;
  return cost;                     //returns a double
}

void TwoDayPackage::setFlatRate(const double f) {  //sets the flat rate of a package
  if (f > 0) {
    flatrate = f;
  } else {
    flatrate = 20;
  }
  cost = CalculateCost();  //recalculate the cost of shipping with the new flatrate
}

double TwoDayPackage::returnCost() {
  cost = CalculateCost(); //calculate the cost of shipping and return
  return cost;
}
