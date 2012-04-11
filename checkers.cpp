#include "checkers.h"
#include "piece.h"

checkers::checkers() {
  //construct a new board, X's = 1, O's = -1

  vector <piece> temp;
  for(int i = 0; i < 8; i++) {      //each column
    piece holder[8];     //Declare an array of 8 pieces (0-7)
    for(int j = 0; j < 8; j++) {    //each row
      if( (i+j) % 2 == 0) { // if the coordinate's sum is even
        holder[j].setIsNull(1);  //make that space null
      }
      else {
	if(i <= 2) {
	  holder[j].setTeam(-1);  //make team o's
	}
	else if (i >= 5) {
	  holder[j].setTeam(1);   //make team x's
	}
	else {
	  holder[j].setTeam(0);   //make blanks
	}
      }
      temp.push_back(holder[j]);
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
  for(int k = 0; k < 8; k++) {  //print row of numbers (1-8)
    cout << " " << k+1;
  }
  for(int i = 0; i < 8; i++) {      
    cout << endl << i+1;       //print number at the beginning of each row
      
    for(int j = 0; j < 8; j++) {
      cout << " " << board[i][j].getRep();  //print the representative piece for each board spot
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
