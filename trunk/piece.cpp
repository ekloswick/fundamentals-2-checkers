#include "piece.h"

piece::piece() {
  isNull = 0;
  team = 0;
  isKing = 0;
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

void piece::setIsNull(int a) {

  isNull = a;
}

void piece::setTeam(int b) {

  team = b;
}

void piece::setIsKing(int c) {

  isKing = c;
}
