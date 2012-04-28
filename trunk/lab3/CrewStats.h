#ifndef CREWSTATS_H
#define CREWSTATS_H
#include <iostream>
#include "BankAccount.h"
using namespace std;

class CrewStats {

 public:
  CrewStats(int s = 20, int = 20, int ms = 0, int mf = 6);  //initializes happy crew
  ~CrewStats();
  int canhazmutiny(); //function which returns true if the crew will mutiny
  BankAccount bank(double balance = 5000.0,double rate = 5.0,int hasBoat = 1); //bank account with default info already set

 private:
  int sailors;      //all of the important information about your crew
  int parrots;
  int monthsOnSea;
  int monthsFood;

};

#endif
