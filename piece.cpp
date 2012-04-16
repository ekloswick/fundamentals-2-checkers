#include "piece.h"

//constructor (to be changed in checkers.cpp)
piece::piece() {
  isNull = 0;  //initialize each piece to a playable piece
  team = 0;    //with no team
  isKing = 0;  //not a king
  rep = 'p';   //represented by 'p'
}

//blank deconstructor
piece::~piece() {

}

//returns 1 if the piece is unplayable, 0 if playable
int piece::getIsNull() {

  return isNull;
}  

//returns 1 for team x, -1 for team o, 0 if blank
int piece::getTeam() {

  return team;
}

//returns 1 if king, 0 if not
int piece::getIsKing() {

  return isKing;
}

//returns the character representing the piece
char piece::getRep() {
  
  return rep;
}

//if a==1, this sets the character representation to blank (not just unplayables)
void piece::setIsNull(int a) {

  isNull = a;
  if(isNull == 1) {
    rep = ' ';  //space is a null
  }
}

//sets the team
void piece::setTeam(int b) {

  if(isNull == 0) {  //if piece is not null
    team = b;        //set team to input value
  
    if(team == 0) {  //if the piece has no team
      rep = '-';     //piece is a dash
    }
    if(isKing == 0) {  //if piece is not a king 
      if(team == -1) { //and the team is o
	rep = 'o';     //represent the piece with an 'o'
      }
      else if (team == 1) { //if the team is x
	rep = 'x';          //represent the piece with an 'x'
      }
    }
    if (isKing == 1) { //if the piece is a king
      if(team == -1) { //and the team is o
	rep = 'O';     //represent the piece with an 'O'
      }
      else if (team == 1) { //if the team is x
	rep = 'X';          //represent the piece with an 'X'
      }
    }
  }
}

void piece::setIsKing(int c) {

  if(isNull == 0 && team != 0) {  //if piece is not null and not a blank
    isKing = c;  //set isKing equal to the input value
    
    if(isKing == 1) {   //if the piece is a king
      if(team == -1) {  //and the team is o
	rep = 'O';      //represent the piece with an 'O'
      }
      else if(team == 1) {  //if team is x
	rep = 'X';          //represent the piece with an 'X'
      }
    }
  }
}
