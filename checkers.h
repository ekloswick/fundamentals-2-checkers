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
  void print();        //prints the current state of the board
  void play();         //play checkers!
  int checkForJump();  //returns 1 if x can move, -1 if o can move, 0 if no moves available for current player
  int checkForWin();   //returns 1 if x wins, -1 if o wins, 0 if nobody has won

 private:
  int turn;            //1 if x's turn, -1 if o's turn
  vector <vector <piece> > board; //Fill a 2D board with type piece
};

#endif
