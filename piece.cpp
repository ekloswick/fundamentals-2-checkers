#include "piece.h"

piece::piece() {
  isNull = 0;  //initialize each piece value
  team = 0;
  isKing = 0;
  rep = 'p';
}

piece::~piece() {

}

int piece::getIsNull() {

  return isNull;
}  

int piece::getTeam() {

  return team;
}

int piece::getIsKing() {

  return isKing;
}

char piece::getRep() {
  
  return rep;
}

void piece::setIsNull(int a) {

  isNull = a;
  if(isNull == 1) {
    rep = ' ';  //space is a null
  }
}

void piece::setTeam(int b) {

  if(isNull == 0) {  //if piece is not null
    team = b;  //set team 
  
    if(team == 0) {
      rep = '-';  //piece is a dash
    }
    if(isKing == 0) {  //if piece is not a king either
      if(team == -1) { //set o's to negative one
	rep = 'o';
      }
      else if (team == 1) {
	rep = 'x';
      }
    }
  }

}

void piece::setIsKing(int c) {

  if(isNull == 0 && team != 0) {  //if piece is not null and not a blank
    isKing = c;
    
    if(isKing == 1) {  //if the piece is a king
      if(team == -1) {  //if team is o's
	rep = 'O';
      }
      else if(team == 1) {  //if team is x's
	rep = 'X';
      }
    }
  }
}
