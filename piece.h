#ifndef PIECE_H 
#define PIECE_H
#include <iostream>

using namespace std;

class piece {
 public:
  piece();
  ~piece();
  int getIsNull();   //Returns the int value of each variable
  int getTeam();
  int getIsKing();
  void setIsNull(int);  //Allows you to change the int value of a variable
  void setTeam(int);
  void setIsKing(int);

 private:
  int isNull; //if space is on unplayable diagonal, isNull is true
  int team;   //Keeps track of color, 1 is x, -1 is o, 0 is blank
  int isKing; //starts off false, becomes true if piece goes to back row
  

};

#endif
