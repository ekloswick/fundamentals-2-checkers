#ifndef CHECKERS_H
#define CHECKERS_H

#include <iostream>
#include <vector>
#include <cctype>  //to use isdigit in input checking
#include "piece.h"

using namespace std;

class checkers {
 public:
  checkers();
  ~checkers();
  void print();        //prints the current state of the board
  void play();         //play checkers!
  void countPieces();   //counts the number of x's and o's
  int checkForMove();  //returns 1 if x can move, -1 if o can move, 0 if no moves available for current player
  int checkForJump();  //returns 1 if x can jump, -1 if o can jump, 0 if no jumps available for current player
  int checkForWin();   //returns 1 if x wins, -1 if o wins, 0 if nobody has won

 private:
  int turn;            //1 if x's turn, -1 if o's turn
  int xcount;          //Keeps track of number of x's on board
  int ocount;          //Keeps track of number of o's on board
  vector <vector <piece> > board; //Fill a 2D board with type piece
};

#endif
