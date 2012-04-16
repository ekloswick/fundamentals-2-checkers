#include "checkers.h"
#include "piece.h"

//constructor
checkers::checkers() {
  //initializes turn to 1 (player x starts)
  turn = 1;

  //construct a new board, x's = 1, o's = -1
  vector <piece> temp;            //temporary holding vector
  for(int i = 0; i < 8; i++) {    //each column
    piece holder[8];              //temporary holder array of 8 pieces (0-7)
    for(int j = 0; j < 8; j++) {  //loop through each row
      if( (i+j) % 2 == 0) {       //if the coordinate's sum is even
        holder[j].setIsNull(1);   //make that space unplayable
      }
      else {                      //if the spot is playable
	if(i <= 2) {              //for the top of the board
	  holder[j].setTeam(-1);  //make the pieces team o's
	}
	else if (i >= 5) {        //for the bottom of the board
	  holder[j].setTeam(1);   //make the pieces team x's
	}
	else {                    //in the middle of the board
	  holder[j].setTeam(0);   //make blanks belonging to neither team
	}
      }
      temp.push_back(holder[j]);  //push back your array of pieces into temp
    }
    board.push_back(temp);        //push temp into your board
    temp.clear();                 //and clear the temp vector before next iteration
  }

}

//blank deconstructor
checkers::~checkers() {
}

//prints the current state of the board
void checkers::print() {

  cout << endl << " ";    //print a blank in upper left corner for alignment
  for(int k = 0; k < 8; k++) {  //print row of numbers (1-8) at top of board
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

//play checkers!
void checkers::play() {
  int winner;  //variable that keeps track of who won once game is over
  cout << endl << endl << "***** Welcome to Checkers ******" << endl << endl;

  while( (winner = checkForWin()) == 0 ) { //while nobody has won yet
    print(); //First, print the board
    while(checkForJump()) {  //while there is a jump available (including double jumps)
      /* Implement forced jump code */
    }
    //Next, select a piece to move, as long as there is not a jump you must take

  }

  if(winner == 1) { //if x wins
    cout << endl << "***** X wins! ******" << endl << endl;
  }
  else { //if o wins
    cout << endl << "***** O wins! ******" << endl << endl;
  }
  cout << "Thank you for playing!" << endl;
}

//returns 1 if x can move, -1 if o can move, 0 if no moves available for current player
int checkers::checkForJump() {

  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {              //check the whole board
      if(board[i][j].getIsNull() == 0) {      //if the space is playable
	if(board[i][j].getTeam() == turn) {   //if team of a piece == turn (the piece belongs to the current player)

	  if(board[i][j].getIsKing() == 1) {  //if the piece is king
	    for(int k = -1; k < 2; k=k+2) {   //Want values of -1 and 1 only (check behind and in front of the king for jumps)

	      if(i-2 >= 0 && (j-2*k >= 0 && j-2*k < 8)) {
	      //use j-turn to check correct direction for blanks ***CRAIG what does this mean?***
		if(board[i-1][j-k].getTeam() == -turn) {  //if there is an opposing piece adjacent to the king
		  if(board[i-2][j-2*k].getTeam() == 0) {  // and there is a blank space behind it
		    return turn;  //return 1 if x can play, -1 if o can play
		  }
		}
	      }
	      if(i+2 < 8 && (j-2*k >= 0 && j-2*k < 8)) { //***CRAIG what does this mean?***
		if(board[i+1][j-k].getTeam() == -turn) {  //if there is an opposing piece adjancent to the king
		  if(board[i+2][j-2*k].getTeam() == 0) {  //and there is a blank space behind it
		    return turn;  //return 1 if x can play, -1 if o can play
		  }
		}
	      }
	    }
	  }
	  else {  //check the forward diagonals for opposing pieces to jump
	    if(i-2 >= 0 && (j-2*turn >= 0 && j-2*turn < 8)) {
	      //use j-turn to check correct direction for blanks
	      if(board[i-1][j-turn].getTeam() == -turn) {  //if there is an opposing piece adjacent
		if(board[i-2][j-2*turn].getTeam() == 0) {  //and there is a blank space behind it
		  return turn;  //return 1 if x can play, -1 if o can play
		}
	      }
	    }
	    if(i+2 < 8 && (j-2*turn >= 0 && j-2*turn < 8)) {
	      if(board[i+1][j-turn].getTeam() == -turn) {  //if there is an opposing piece adjacent
		if(board[i+2][j-2*turn].getTeam() == 0) {  //and there is a blank space behind it
		  return turn;  //return 1 if x can play, -1 if o can play
		}
	      }
	    }
	  }
	}	
      }
    }
  }

  return 0; //if current player has no moves, return 0
}

//return 1 if x wins, -1 if o wins, 0 if nobody has won
int checkers::checkForWin() {
  //First, check whole board for pieces of current player's type
  int count = 0; //counter variable
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      if(board[i][j].getIsNull() == 0) {    //if the space is not null 
	if(board[i][j].getTeam() != turn) { //and if team of the piece != turn (if the piece does not belong to the current player
	  count++;  //increment count
	}
      }
    }
  }
  if(count == 32) { //if no piece remains of that type (all available spots do not belong to the current player)
    return(-turn);  //Then the opposite team wins!
  }

  //Next, check if there are no legal moves left for the current player ***CRAIG why don't you call check for jump instead?***
  for(int i = 0; i < 8; i++) {    //column coordinate
    for(int j = 0; j < 8; j++) {  //row coordinate  (check both ways
      if(board[i][j].getIsNull() == 0) { 
	if(board[i][j].getTeam() == turn) {   //if team of the piece == turn
	  //***CRAIG the code below is confusing. Please clarify***
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
    return 0;           //The game is not over
  }

  //If it reaches this point, current player had no legal moves available, so the opposite team wins 
  return -turn;
}
