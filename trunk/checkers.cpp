#include "checkers.h"
#include "piece.h"

checkers::checkers() {
  //construct a new board, X's = 1, O's = -1

  int holder;
  vector<piece> temp;
  for(int i = 0; i < 8; i++) {      //each column
    for(int j = 0; j < 8; j++) {    //each row
      if(i < 3) { // if the top three rows
        piece = -1;  //place the O's
      }
      else if(i > 4) {
        piece = 1;   //place the X's
      }
      else {
        piece = 0;
      }
      
      if(i % 2 == 0) {    //If row is even
        if(j % 2 == 1) {  //Then place pieces only if column is odd
          temp.push_back(piece);
        }
        else {
          temp.push_back(0);
        }
      }
      else {    //If row is odd
        if(j % 2 == 0) {
          temp.push_back(piece);
        }
        else {
          temp.push_back(0);
        }
      }
    }
    board.push_back(temp);
    temp.clear();
  }

}

checkers::~checkers() {
}

void checkers::print() {

  char c;
  cout << endl << " ";
  for(int k = 0; k < 8; k++) {
    cout << " " << k+1;
  }
  for(int i = 0; i < 8; i++) {      
    cout << endl << i+1;
      
    for(int j = 0; j < 8; j++) {
      if(board[i][j] == 1) {
        c = 'x';
      }
      if(board[i][j] == -1) {
        c = 'o';
      }
      if(board[i][j] == 2) {
        c = 'X';
      }
      if(board[i][j] == -2) {   
        c = 'O';
      }
      if(board[i][j] == 0) {
        c = ' ';
      }
      cout << " " << c;
    }
  }
  cout << endl << endl;
}

void checkers::play() {


}

int checkers::checkForWin() {


  return 0;
}

int checkers::checkForJump() {


  return 0;
}
