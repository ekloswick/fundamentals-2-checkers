#include <iostream>
#include "OvernightPackage.h"
#include "Package.h"
using namespace std;

OvernightPackage::OvernightPackage(double e) : Package("Dennis", "601 Maujer Street", "New York", "NY", 98765, 3.21, 7){
  extraCostPerOunce = e;     //sets the private variable to the desired value
  cost = CalculateCost();    //sets cost to the desired value
}

double OvernightPackage::CalculateCost() {
  cost = (rate + extraCostPerOunce) * weight; //calculates cost of an overnight package
  return cost;    //returns the value calculated
}

void OvernightPackage::setExtraCostPerOunce(double i) {
  extraCostPerOunce = i;
  cost = CalculateCost();
}

double OvernightPackage::returnCost() {
  cost = CalculateCost();
  return cost;
}
