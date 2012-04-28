#ifndef	OVERNIGHTPACKAGE_H
#define OVERNIGHTPACKAGE_H
#include <iostream>
#include "Package.h"

class OvernightPackage : public Package {

 public:
  OvernightPackage(double e = 1.27); //initializes overnight package with extra cost per oz
  double CalculateCost();      //calculates cost specific to overnight package
  void setExtraCostPerOunce(double);
  double returnCost();

 private:
  double extraCostPerOunce;    //extra cost per oz of an overnight package
		
};

#endif
