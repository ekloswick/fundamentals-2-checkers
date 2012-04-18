#include "checkers.h"
#include "piece.h"

//constructor
checkers::checkers() {
  //initializes turn to 1 (player x starts)
  turn = 1;

  //construct a new board, x's = 1, o's = -1
  vector <piece> temp;            //temporary holding vector
  for(int i = 0; i < 8; i++) {    //each row
    piece holder[8];              //temporary holder array of 8 pieces (0-7)
    for(int j = 0; j < 8; j++) {  //fill each row with a column
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

  countPieces();

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
  piece holder;        //Holds a board piece for switching
  int winner;          //variable that keeps track of who won once game is over
  int errorCheck = 0;  //variable that checks if piece selection input is valid
  int errorCheck2 = 0; //variable that checks if piece movement input is valid
  int tempx;           //temporarily holds the user input for piece selection
  int tempy;
  int tempa;           //temporarily holds the user input for piece movement
  int tempb;
  int x;               //holds the actual coordinates of the user input.  (Basically, tempx-1 and tempy-1 since array elements start at 0)
  int y;
  int a;
  int b;


  cout << endl << endl << "***** Welcome to Checkers ******" << endl << endl;

  while( (winner = checkForWin()) == 0 ) { //while nobody has won yet

    print(); //First, print the board
    countPieces();  //Then count the pieces of each type.

    //Next, get inputs
    do {  //Use do-while so this happens at least once every turn, and repeats if there is an error in the input
      errorCheck = 0;  //make error false again
      if(turn == 1) {
	cout << "X, input coordinates of the piece you want to move. (row column): ";
      }
      else {
	cout << "O, input coordinates of the piece you want to move. (row column): ";
      }
      cin >> tempx >> tempy;  //put the inputs into tempx and tempy
      //cout << "x = " << tempx-1 << endl << "y = " << tempy-1 << endl;
      //big if statement below checks if input is okay, that is, if that digit is between 1 and 8.
      if( (tempx >= 1 && tempx <= 8) && (tempy >= 1 && tempy <= 8) ) {
	x = tempx-1;  //subtract one from each to match cooridinates with vector elements
	y = tempy-1;	
	if(board[x][y].getTeam() != turn) {  //If the user inputs a piece that is not his
	  errorCheck = 1;
	  cout << "Error: Piece is not yours. Please try again." << endl;
	  print();
	}
      }
      else {
	errorCheck = 1;
	cout << "Error: input invalid. Please try again." << endl;
	print();
      }
    } while(errorCheck == 1);
    

    while(checkForJump()) {  //while there is a jump available (including double jumps)

      /* Implement forced jump code */

    }

    //Next, move a piece as long as there is not a jump you must take by switching the piece and the blank
    do {
      errorCheck2 = 0;  //first make the errorCheck2 false
      cout << "Choose a square to move to (row column): " << endl;
      cin >> tempa >> tempb;
      //cout << "a = " << tempa-1 << endl << "b = " << tempb-1 << endl;
      if( (tempa >= 1 && tempa <= 8) && (tempb >= 1 && tempb <= 8) ) {
	a = tempa-1;  //subtract one from each to match cooridinates with vector elements
	b = tempb-1;
	if(board[a][b].getTeam() == 0) {         //if the space is blank
	  if(board[x][y].getIsKing() == 1) {   //if the piece is a king
	    if( (a == x-1 || a == x+1) && (b == y-1 || b == y+1) ) {  //if space is adjacent
	      holder = board[x][y];           //then execute switch
	      board[x][y] = board[a][b];
	      board[a][b] = holder;
	    }
	    else {
	      errorCheck2 = 1;
	      cout << "Error: Space is not adjacent to piece selected.  Please try again." << endl;
	      print();
	    }
	  }
	  else {  //else is piece is not a king
	    if( (a == x-turn) && (b == y-1 || b == y+1) ) {  //if space is on forward diagonal
	      holder = board[x][y];           //then execute switch
	      board[x][y] = board[a][b];
	      board[a][b] = holder;
	    }
	    else {
	      errorCheck2 = 1;
	      cout << "Error: Space is not adjacent and forward of the selected piece.  Please try again." << endl;
	      print();
	    }
	  }
	}
	else {
	  errorCheck2 = 1;
	  cout << "Error: space is not empty.  Please try again." << endl;
	  print();
	}
      }
      else {
	errorCheck2 = 1;
	cout << "Error: invalid input.  Please try again." << endl;
	print();
      }
    } while(errorCheck2 == 1);


    turn *= -1;   //Switch whose turn it is

  } //END OF WHILE LOOP


  if(winner == 1) { //if x wins
    cout << endl << "***** X wins! ******" << endl << endl;
  }
  else { //if o wins
    cout << endl << "***** O wins! ******" << endl << endl;
  }
  cout << "Thank you for playing!" << endl;
}

//count the pieces of each type on the board
void checkers::countPieces() {

  int total = 0;
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      if(board[i][j].getIsNull() == 0) {  //if piece is not null
	if(board[i][j].getTeam() == 1) {  //and piece is an x
	  total++;                        //increment total
	}
      }
    }
  }
  xcount = total;
  cout << "xcount: " << xcount << endl;
  total = 0;
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      if(board[i][j].getIsNull() == 0) {  //if piece is not null
	if(board[i][j].getTeam() == -1) {  //and piece is an x
	  total++;                        //increment total
	}
      }
    }
  }
  ocount = total;
  cout << "ocount: " << ocount << endl;
}

//returns 1 if x can move, -1 if o can move, and 0 is no moves available
int checkers::checkForMove() {

  //I did below this, but this is merely checking for regular legal moves
  for(int i = 0; i < 8; i++) {    //column coordinate
    for(int j = 0; j < 8; j++) {  //row coordinate  (check both ways
      if(board[i][j].getIsNull() == 0) { 
	if(board[i][j].getTeam() == turn) {   //if team of the piece == turn

	  if(board[i][j].getIsKing() == 1) {  //if the piece is king
	    for(int k = -1; k < 2; k=k+2) {   //Want values of -1 and 1 only (check behind and in front of the king for jumps)

	      if(j-1 >= 0 && (i-k >= 0 && i-k < 8)) {  //use i-k to check both directions for king O's and X's
		if(board[i-k][j-1].getTeam() == 0) {   //Check left diagonals
		  return turn;                         //return true
		}
	      }
	      if(j+1 < 8 && (i-k >= 0 && i-k < 8)) {
		if(board[i-k][j+1].getTeam() == 0) {   //Check right diagonals
		  return turn;                         //return true
		}
	      }

	    }	   
	  }
	  else {  //check the diagonals for blank spaces or jumps
	    if(j-1 >= 0 && (i-turn >= 0 && i-turn < 8)) {
	      //use j-turn to check correct direction for blanks
	      if(board[i-turn][j-1].getTeam() == 0) { 
		return turn;
	      }
	    }
	    if(j+1 < 8 && (i-turn >= 0 && i-turn < 8)) {
	      if(board[i-turn][j+1].getTeam() == 0) {  
		return turn;
	      }
	    }
	  }

	}
      }
    }
  }

}

 

//returns 1 if x can jump, -1 if o can jump, 0 if no jumps available for current player
int checkers::checkForJump() {

  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {              //check the whole board
      if(board[i][j].getIsNull() == 0) {      //if the space is playable
	if(board[i][j].getTeam() == turn) {   //if team of a piece == turn (the piece belongs to the current player)

	  if(board[i][j].getIsKing() == 1) {  //if the piece is king
	    for(int k = -1; k < 2; k=k+2) {   //Want values of -1 and 1 only (check behind and in front of the king for jumps)

	      if(j-2 >= 0 && (i-k*2 >= 0 && i-k*2 < 8)) {
		if(board[i-k*2][j-1].getTeam() == -turn) {  //if there is an opposing piece adjacent to the king
		  if(board[i-2*k][j-2].getTeam() == 0) {  // and there is a blank space behind it
		    return turn;  //return 1 if x can play, -1 if o can play
		  }
		}
	      }
	      if(j+2 < 8 && (i-2*k >= 0 && i-2*k < 8)) { 
		//This is edge checking, to make sure there exists a spot on the board j-2*k.
		if(board[i-k][j+1].getTeam() == -turn) {  //if there is an opposing piece adjancent to the king
		  if(board[i-k*2][j+2].getTeam() == 0) {  //and there is a blank space behind it
		    return turn;  //return 1 if x can play, -1 if o can play
		  }
		}
	      }

	    }
	  }
	  else {  //check the forward diagonals for pieces to jump
	    if(j-2 >= 0 && (i-2*turn >= 0 && i-2*turn < 8)) {
	      //use j-turn to check correct direction for blanks
	      if(board[i-turn][j-1].getTeam() == -turn) {  //if there is an opposing piece adjacent
		if(board[i-2*turn][j-2].getTeam() == 0) {  //and there is a blank space behind it
		  return turn;  //return 1 if x can play, -1 if o can play
		}
	      }
	    }
	    if(j+2 < 8 && (i-2*turn >= 0 && i-2*turn < 8)) {
	      if(board[i-turn][j+1].getTeam() == -turn) {  //if there is an opposing piece adjacent
		if(board[i-2*turn][j+2].getTeam() == 0) {  //and there is a blank space behind it
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
  cout << "First" << endl;

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

  //Next, check if there are no legal moves left for the current player
  cout << "Before checkForMove" << endl;

  if(checkForMove()) {  //If checkFor Move is true
    return 0;           //There is a legal move: game is not over
  }

  cout << "Before checkForJump" << endl;

  if(checkForJump()) {  //if there is a jump available
    return 0;           //The game is not over
  }

  //If it reaches this point, current player had no legal moves available, so the opposite team wins 
  return -turn;
}
