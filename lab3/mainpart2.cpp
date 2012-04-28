/**********************************
Craig Cahillane	and Rachael Creager
Lab #3
Part 2
14 February 2012
**********************************/

#include <iostream>
#include "Package.h"
#include "TwoDayPackage.h"
#include "OvernightPackage.h"
using namespace std;

int main () {

 
  cout << "Basic Package" << endl << endl;
  Package a;                //initializes a default package
  a.print();                //prints default package info

  TwoDayPackage b(50);      //initializes a derived class two day package variable with $50 flat rate
  cout << "Two Day Package" << endl << endl;
  b.print();                //prints derived class info using print function from base class Package

  cout << "Overnight Package" << endl << endl;
  OvernightPackage c(1.23); //initializes a derived class overnight package variable with 1.23 extra cost per oz
  c.print();                //prints derived class, same as above

  double TwoDayTotalCost = 0;  //holds the total cost of all the two day package shipping costs

  TwoDayPackage ** arr1;       //this is a pointer to a pointer to an array of two day packages
  arr1 = new TwoDayPackage *[3]; //allocate memory to array
  for(int i = 0; i < 3; i++) {
    arr1[i] = new TwoDayPackage; //allocate memory to object
    arr1[i]->setFlatRate(i+13);  //change the rate for each package
    arr1[i]->print();            //print information for each two day package
    TwoDayTotalCost = TwoDayTotalCost + arr1[i]->returnCost(); //add the cost of each package to the total
    cout << endl;
  }
  
  cout << "The total cost of shipping 3 two-day packages is: $" << TwoDayTotalCost << endl << endl; //prints total cost

  delete[] arr1; //delete memory

  double OvernightTotalCost = 0;  //holds the total cost of all the overnight package shipping costs

  OvernightPackage ** arr2;       //this is a pointer to a pointer to an array of overnight packages
  arr2 = new OvernightPackage *[4]; //allocate memory to array
  for(int i = 0; i < 4; i++) {
    arr2[i] = new OvernightPackage; //allocate memory to object
    arr2[i]->setExtraCostPerOunce(1.23+i);  //change the rate for each package
    arr2[i]->print();            //print information for each two day package
    OvernightTotalCost = OvernightTotalCost + arr2[i]->returnCost(); //add the cost of each package to the total
    cout << endl;
  }
  
  cout << "The total cost of shipping 4 overnight packages is: $" << OvernightTotalCost << endl << endl; //prints total cost

  delete[] arr2; //delete memory

  return 0;

}
