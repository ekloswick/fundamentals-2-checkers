#ifndef	TWODAYPACKAGE_H
#define	TWODAYPACKAGE_H
#include <iostream>
#include <string>
#include "Package.h"

class TwoDayPackage : public Package {

 public:
  TwoDayPackage(int f = 20); //set initial flatrate to 20
  //~TwoDayPackage();
  double CalculateCost();    //calculates the cost of a two day package
  void setFlatRate(const double);
  double returnCost();
 private:
  int flatrate;              //the flatrate for shipping a two day package
};

#endif
