#ifndef PIECE_H 
#define PIECE_H
#include <iostream>

using namespace std;

class piece {
 public:
  piece();
  ~piece();
  int getIsNull();      //Returns the int value of each variable
  int getTeam();        //Returns 1 if x, -1 if o, 0 if blank
  int getIsKing();      //Returns 1 if king, 0 if not
  char getRep();        //Returns the char representing the piece
  void setIsNull(int);  //Allows you to change the int value of a variable
  void setTeam(int);    //Sets the team
  void setIsKing(int);  //Sets a piece to king

 private:
  int isNull; //if space is on unplayable diagonal, isNull is true
  int team;   //Keeps track of color, 1 is x, -1 is o, 0 is blank
  int isKing; //starts off false, becomes true if piece goes to back row
  char rep;   //holds the team's character based on isNull, team, and isKing

};

#endif
