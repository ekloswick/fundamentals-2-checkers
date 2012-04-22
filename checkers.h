#ifndef CHECKERS_H
#define CHECKERS_H

#include <iostream>
#include <fstream> //to use file input
#include <vector>
#include <string>  
#include <ctime>
#include "piece.h"

using namespace std;

class checkers {
 public:
  checkers();
  ~checkers();
  void print();                      //prints the current state of the board
  void play();                       //play checkers!
  void countPieces();                //counts the number of x's and o's
  void getInput();                   //receives input from player
  void executeMove();                //executes move in play function
  void executeJump();                //executes jump in play function
  void makeKing();                   //finds pieces in back row and kings them
  int checkPieceMove(int i, int j);  //returns true if the piece associated with board[m][n] has a move, false if not
  int checkPieceJump(int i, int j);  //returns true if the piece associated with board[m][n] has a jump, false if not
  int checkForMove();                //returns 1 if x can move, -1 if o can move, 0 if no moves available for current player
  int checkForJump();                //returns 1 if x can jump, -1 if o can jump, 0 if no jumps available for current player
  int checkForWin();                 //returns 1 if x wins, -1 if o wins, 0 if nobody has won
  

 private:
  int turn;            //1 if x's turn, -1 if o's turn
  int choice;          //Holds the user's game type choice
  string name;         //Holds the name of the example.txt used to start a game
  int xcount;          //Keeps track of number of x's on board
  int ocount;          //Keeps track of number of o's on board
  int x;               //holds the board coordinates of the user input. 
  int y;
  int a;               //holds the board coordinates of user's move/jump input
  int b;
  vector<int> moves;        //holds move coordinates from input files
  vector <vector <piece> > board; //Fill a 2D board with type piece
};

#endif
