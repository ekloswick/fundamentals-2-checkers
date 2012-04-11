#ifndef CHECKERS_H
#define CHECKERS_H

#include <iostream>
#include <vector>
#include "piece.h"

using namespace std;

class checkers {
 public:
  checkers();
  ~checkers();
  void print();
  void play();
  int checkForWin();
  int checkForJumps();

 private:
  vector <vector <piece> > board; //Fill a 2D board with type piece
};

#endif
