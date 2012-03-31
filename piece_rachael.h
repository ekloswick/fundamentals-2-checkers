#ifndef C4COL_H
#define C4COL_H
#include <iostream>
#include <vector>
using namespace std;

class piece {
 protected:
  int isKing; //1 if King, 0 if not
  int whosePiece; //1 if X, -1 if O, 0 if nobody
 public:
  void kingMe; //turns a piece into a king
  void isJumped; //eliminates a piece from the board
};

#endif
