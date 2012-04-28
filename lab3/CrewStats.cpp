#include <iostream>
#include "CrewStats.h"
using namespace std;

CrewStats::CrewStats(int s, int p, int ms, int mf) {
  if (s >= 0 && p >= 0 && ms >= 0 && mf >= 0) { //checks for bad input
    sailors = s;      //if all inputs are good, sets info as desired
    parrots = p;
    monthsOnSea = ms;
    monthsFood = mf;
  } else {
    cout << "Poor crew choice matey." << endl;  //error message
    sailors = 20;     //if the initial inputs were bad, sets variables to defaul values
    parrots = 20;
    monthsOnSea = 0;
    monthsFood = 6;
  }
}

CrewStats::~CrewStats() {

}

int CrewStats::canhazmutiny() {
  int happiness = 0;     //total happiness
  happiness = monthsFood - monthsOnSea + (parrots/5);  //the fail-proof method for measuring happiness
  if (monthsFood == 0) {
    happiness = 0;       //a starving crew is automatically miserable
  }
  if (happiness <= 5) {
    cout << "The crew mutinied, what a bad captain you are." << endl; //if happiness is too low, prints message and returns 1
    return 1;
  } else { 
    cout << "Nice job, no mutiny." << endl;  //if the crew is happy enough, prints good message and returns 0
    return 0;
  }
}
