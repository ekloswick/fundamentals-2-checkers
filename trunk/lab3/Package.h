#ifndef PACKAGE_H
#define PACKAGE_H
#include <iostream>
#include <string>
using namespace std;


class Package {

 public:
  Package(string n = "Alvin", string a = "309 Breen Phillips Hall", string c = "South Bend", string s = "IN", int z = 46556, int r = 3.21, int w = 5);  //initialized with default values
  //~Package();
  double CalculateCost(); //calculates the basic cost of shipping a package
  void print();           //prints address info, weight, and cost
 protected:
  string name;          //address information
  string address;
  string city;
  string state;
  int zipcode;
  int weight;		//in ounces
  double rate;          //this rate applies to all packages
  double cost;		//depends on weight

};

#endif
