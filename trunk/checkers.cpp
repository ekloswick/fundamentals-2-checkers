#include "checkers.h"
#include "piece.h"

checkers::checkers() {
  //Initialize turn
  turn = 1;

  //construct a new board, x's = 1, o's = -1
  vector <piece> temp;
  for(int i = 0; i < 8; i++) {      //each column
    piece holder[8];                //Declare an array of 8 pieces (0-7)
    for(int j = 0; j < 8; j++) {    //each row
      if( (i+j) % 2 == 0) {         // if the coordinate's sum is even
        holder[j].setIsNull(1);     //make that space null
      }
      else {
	if(i <= 2) {
	  holder[j].setTeam(-1);    //make team o's
	}
	else if (i >= 5) {
	  holder[j].setTeam(1);     //make team x's
	}
	else {
	  holder[j].setTeam(0);     //make blanks
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
  int winner;  //variable that keeps track of who won once game is over
  cout << endl << endl << "***** Welcome to Checkers ******" << endl << endl;



  while( (winner = checkForWin()) == 0 ) {
    //First, print the board
    print();
    while(checkForJump()) {  //while loop to allow for double jumps
      /* Implement forced jump code */
    }
    //Next, select a piece to move, as long as there is not a jump you must take

  }
  if(winner == 1) {
    cout << endl << "***** X wins! ******" << endl << endl;
  }
  else {
    cout << endl << "***** O wins! ******" << endl << endl;
  }
}

int checkers::checkForJump() {

  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      if(board[i][j].getIsNull() == 0) {  //if the space is not null 
	if(board[i][j].getTeam() == turn) {   //if team of a piece == turn

	  if(board[i][j].getIsKing() == 1) {  //if the piece is king
	    for(int k = -1; k < 2; k=k+2) {  //Want values of -1 and 1 only

	      if(i-2 >= 0 && (j-2*k >= 0 && j-2*k < 8)) {
	      //use j-turn to check correct direction for blanks
		if(board[i-1][j-k].getTeam() == -turn) {  //opposing piece adjacent
		  if(board[i-2][j-2*k].getTeam() == 0) {  //blank space behind it
		    return turn;  //return true (1 or -1)
		  }
		}
	      }
	      if(i+2 < 8 && (j-2*k >= 0 && j-2*k < 8)) {
		if(board[i+1][j-k].getTeam() == -turn) {  
		  if(board[i+2][j-2*k].getTeam() == 0) {
		    return turn;  //return true (1 or -1)
		  }
		}
	      }
	    }

	  }
	  else {  //check the forward diagonals for opposing pieces to jump
	    if(i-2 >= 0 && (j-2*turn >= 0 && j-2*turn < 8)) {
	      //use j-turn to check correct direction for blanks
	      if(board[i-1][j-turn].getTeam() == -turn) {  //opposing piece adjacent
		if(board[i-2][j-2*turn].getTeam() == 0) {  //blank space behind it
		  return turn;  //return true (1 or -1)
		}
	      }
	    }
	    if(i+2 < 8 && (j-2*turn >= 0 && j-2*turn < 8)) {
	      if(board[i+1][j-turn].getTeam() == -turn) {  
		if(board[i+2][j-2*turn].getTeam() == 0) {
		  return turn;  //return true (1 or -1)
		}
	      }
	    }
	  }

	}	


      }
    }
  }

  return 0;
}

int checkers::checkForWin() {
  //First, check whole board for pieces of current player's type
  int count = 0;
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      if(board[i][j].getIsNull() == 0) {  //if the space is not null 
	if(board[i][j].getTeam() != turn) { //if team of the piece != turn
	  count++;  //increment count
	}
      }
    }
  }
  if(count == 32) {  //if no piece remains of that type
    return(-turn);  //Then the opposite team wins!
  }

  //Next, check if there are no legal moves left for the current player
  for(int i = 0; i < 8; i++) {    //column coordinate
    for(int j = 0; j < 8; j++) {  //row coordinate  (check both ways
      if(board[i][j].getIsNull() == 0) { 
	if(board[i][j].getTeam() == turn) {   //if team of the piece == turn

	  if(board[i][j].getIsKing() == 1) {  //if the piece is king
	    return 0;                         //the game is not over
	  }
	  else {  //check the diagonals for blank spaces or jumps
	    if(i-1 >= 0 && (j-turn >= 0 && j-turn < 8)) {
	      //use j-turn to check correct direction for blanks
	      if(board[i-1][j-turn].getTeam() == 0) {  
		return 0;
	      }
	    }
	    if(i+1 < 8 && (j-turn >= 0 && j-turn < 8)) {
	      if(board[i+1][j-turn].getTeam() == 0) {  
		return 0;
	      }
	    }
	  }

	}
      }
    }
  }

  if(checkForJump()) {  //if there is a jump available
    return 0;  //The game is not over
  }

  //If it reaches this point, no legal moves were available, so the opposite team wins 
  return -turn;
}
