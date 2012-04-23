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

  do {          //Select game type
    choice = 0;
    cout << "Choose one of the following options: " << endl;
    cout << "1: Human vs. Human game" << endl;
    cout << "2: AI vs. Human game" << endl;
    cout << "3: Example game: Enter name of a .txt file to play." << endl;
    cin >> choice;
  } while(choice != 1 && choice != 2 && choice != 3 );

  if(choice == 3) {      //if they chose example game
    ifstream myfile;     //Holds the actual file.txt
    cout << "Enter the name of the .txt you wish to play: " << endl;
    cout << "   Choices are: doublejump.txt, kingme.txt, and victory.txt" << endl;
    cin >> name;                //takes in file name input
    myfile.open(name.c_str());  //opens the file
    if(myfile.is_open()) {      //if the file opens
      while(myfile.good()) {    //and does not equal EOF
	int temp;               
	myfile >> temp;         //read in from the file
	cout << temp << " ";    //debugging
	moves.push_back(temp);  //and push coordinates onto vector moves
      }
      moves.pop_back();         //correcting an unknown problem where the last number was pushed on twice when reading the file...
      myfile.close();           //close file when done
    }
    else {                      //if file is not open
      cout << "ERROR: File failed to open" << endl;
      choice = 1;               //print error and make game human vs. human
    }
    cout << endl;
    for(int i = 0; i < moves.size(); i++) { //debugging
      cout << moves[i] << " ";
    }
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
  int winner;          //variable that keeps track of who won once game is over
  cout << endl << endl << "***** Welcome to Checkers ******" << endl << endl;
 
  while( (winner = checkForWin()) == 0 ) { //while nobody has won yet
    print(); //First, print the board
    countPieces();  //Then count the pieces of each type.
    getInput();     //get input from user or example text
    if(checkForJump()!=0) {  //if there are jumps on the board
      while(checkPieceJump(x, y)!=0) {  //while there is a jump available for a piece (which allows for double jumps)
	executeJump(); //make the jump
      }
    }
    else { //If checkForJump is false (there are no jumps on the board), move a piece by switching the piece and the blank
      executeMove(); //make the move
    }  
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
	if(board[i][j].getTeam() == -1) {  //and piece is an o
	  total++;                        //increment total
	}
      }
    }
  }
  ocount = total;
  cout << "ocount: " << ocount << endl;
}

//receives input from player or example text until they choose a good move
void checkers::getInput() {
  int errorCheck = 0;  //error check to see if piece selection input is valid
  int tempx;  //temporary holder for user's input coordinates
  int tempy;

  do {  //Use do-while so this happens at least once every turn, and repeats if there is an error in the input
    errorCheck = 0;  //initially make error false again
    if(turn == 1) {  //depending on whose turn it is, ask for input
      cout << "X, input coordinates of the piece you want to move. (row column): ";
    }
    else {
      cout << "O, input coordinates of the piece you want to move. (row column): ";
    }
    if(choice == 1 || (choice == 2 /*&& turn == 1*/)) { //debugging remove later //for user-user game or computer-user game
      cin >> tempx >> tempy;  //put the inputs into tempx and tempy
    }
    else if(choice == 3) { //for example game
      sleep(1);            //wait for one second before executing the move
      tempx = moves[0];    //put the first move coordinates into tempx and tempy
      tempy = moves[1];
      moves.erase(moves.begin()); //then pop them off moves
      moves.erase(moves.begin());
    }
    else {
      // Make the computer select a piece to move
    }
    //the following loop checks for possible bad inputs from the user, i.e. choosing a bad location, choosing not to jump when a jump was available, choosing a piece with no legal moves, or choosing the other player's piece
    if( (tempx >= 1 && tempx <= 8) && (tempy >= 1 && tempy <= 8) ) { //if the user chose a piece on the board
      x = tempx-1;  //subtract one from each to match coordinates with vector elements
      y = tempy-1;	
      if(checkForJump()!=0) {               //if there is a jump
	if(checkPieceJump(x, y) == 0) {  //and the piece selected cannot jump
	  errorCheck = 1;                //we have a problem
	  cout << "Error: selected piece cannot jump when a jump exists on the board. Please try again." << endl;
	}
      }	
      else if( (checkPieceMove(x, y)!=0) || (checkPieceJump(x, y)!=0) ) {  //if the selected piece has a legal move
	if(board[x][y].getTeam() != turn) {  //If the user inputs a piece that is not his
	  errorCheck = 1; //we have a problem
	  cout << "Error: Piece is not yours. Please try again." << endl;
	  print();
	}
	}
      else {  //if the selected piece has no legal move
	errorCheck = 1; //we have a problem
	cout << "Error: selected piece has no legal moves. Please try again." << endl;
	print();
	}
    }
    else { //if the user chose a bad location
      errorCheck = 1; //we have a problem
      cout << "Error: input invalid. Please try again." << endl;
      print();
    }
  } while(errorCheck == 1); //exits once the loop completes without finding an error

}

//executes move in play function
void checkers::executeMove() {
  int errorCheck2 = 0; //variable that checks if piece movement input is valid
  int tempa;  //briefly holds user's move coordinates
  int tempb;
  piece holder;  //piece to temporarily hold board piece values while switching

  do {
    errorCheck2 = 0;  //first make the errorCheck2 false
    cout << "Choose a square to move to (row column): " << endl;
    if(choice == 1 || (choice == 2 /*&& turn == 1 */)) { //remove later debugging //for user-user and user-computer games
      cin >> tempa >> tempb;
    }
    else if(choice == 3) { //for example game
      tempa = moves[0];  //put moves coordinates into tempa and tempb
      tempb = moves[1];
      moves.erase(moves.begin()); //pop those coordinates off moves
      moves.erase(moves.begin());
      if(moves.empty()) {  //if there are no more moves in line
	choice = 1;        //change the game type to human vs human
      }
    }
    else {
      //At in AIMove() later
    }
    if( (tempa >= 1 && tempa <= 8) && (tempb >= 1 && tempb <= 8) ) { //if the chosen move is on the board
      a = tempa-1;  //subtract one from each to match cooridinates with vector elements
      b = tempb-1;
      if(board[a][b].getTeam() == 0) {                              //if the space is blank
	if(board[x][y].getIsKing() == 1) {                          //if the piece is a king
	  if( (a == x-1 || a == x+1) && (b == y-1 || b == y+1) ) {  //if space is adjacent
	    holder = board[x][y];                                   //then execute switch
	    board[x][y] = board[a][b];
	    board[a][b] = holder;
	    makeKing(); //change pieces to kings if needed
	  }
	  else { //if the user picked a non-adjacent move
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
	    makeKing(); //change pieces to kings if needed
	  }
	  else { //if the user didn't chose a forward & adjacent move
	    errorCheck2 = 1;
	    cout << "Error: Space is not adjacent and forward of the selected piece.  Please try again." << endl;
	    print();
	  }
	}
      }
      else { //if the user chose a non-empty spot
	errorCheck2 = 1;
	cout << "Error: space is not empty.  Please try again." << endl;
	print();
      }
    }
    else { //if the user entered a bad location
      errorCheck2 = 1;
      cout << "Error: invalid input.  Please try again." << endl;
      print();
    }
  } while(errorCheck2 == 1); //repeat this loop until the user chooses a good move

}

void checkers::executeJump() {
  int errorCheck3 = 0; //variable that checks if piece jump input is valid
  int tempa;  //briefly holds user's jump coordinates
  int tempb;
  piece holder;  //piece to temporarily hold board piece values while switching

  do {
    errorCheck3 = 0;
    cout << "Choose a square to jump to (row column): " << endl;
    if(choice == 1 || (choice == 2 /*&& turn == 1 */)) { //remove later
      cin >> tempa >> tempb;
    }
    else if(choice == 3) {
      tempa = moves[0];  //put moves coordinates into tempa and tempb
      tempb = moves[1];
      moves.erase(moves.begin()); //pop those coordinates off moves
      moves.erase(moves.begin());
      if(moves.empty()) {  //if there are no more moves
	choice = 1;        //change the game type to human vs human
      }
    }
    else {
      //At in AIJump() later
    }
    if( (tempa >= 1 && tempa <= 8) && (tempb >= 1 && tempb <= 8) ) {
      a = tempa-1;
      b = tempb-1;
      if(board[a][b].getTeam() == 0) {                                //if the space is blank
	if(board[(a+x)/2][(b+y)/2].getTeam() == -turn) {              //if the space in the middle has an opposing piece
	  if(board[x][y].getIsKing() == 1) {                          //if the piece is a king
	    if( (a == x-2 || a == x+2) && (b == y-2 || b == y+2) ) {  //if space to jump to is two away
	      holder = board[x][y];
	      board[x][y] = board[a][b];
	      board[a][b] = holder;
	      board[(a+x)/2][(b+y)/2].setTeam(0);	
	      x = a;
	      y = b;
	      makeKing(); //make pieces kings if needed
	    }
	    else {
	      errorCheck3 = 1;
	      cout << "Error: Invalid jump coordiates. Please try again." << endl;
	    }
	  }
	  else {   //if the piece is NOT a king
	    if( (a == x-2*turn) && (b == y-2 || b == y+2) ) {  //if space is on forward diagonal		  
	      holder = board[x][y];
	      board[x][y] = board[a][b];
	      board[a][b] = holder;
	      board[(a+x)/2][(b+y)/2].setTeam(0);
	      x = a;
	      y = b;
	      makeKing(); //make pieces kings if needed
	    }
	    else {
	      errorCheck3 = 1;
	      cout << "Error: Invalid jump coordinates. Please try again." << endl;
	    }
	  }
	}
	else {
	  errorCheck3 = 1;
	  cout << "Error: No piece is being jumped. Please try again." << endl;
	}
      }
      else {
	errorCheck3 = 1;
	cout << "Error: space is not empty. Please try again." << endl;	
      }
    }
    else {
      errorCheck3 = 1;
      cout << "Error: invalid input. Please try again." << endl;      
    }  
    print();
    countPieces();
  } while(errorCheck3 == 1);

}

//finds pieces in back row and kings them
void checkers::makeKing() {

  for(int i = 0; i < 8 ; i++) {
    if(board[0][i].getTeam() == 1) {
      board[0][i].setIsKing(1);
    }
    if(board[7][i].getTeam() == -1) {
      board[7][i].setIsKing(-1);
    }
  }

}

//returns turn if the piece associated with board[m][n] has a move, false if not
int checkers::checkPieceMove(int i, int j) {

  if(board[i][j].getIsNull() == 0) {      //if the location is not a null
    if(board[i][j].getTeam() == turn) {   //and if team of the piece == turn
      if(board[i][j].getIsKing() == 1) {  //nd if the piece is king
	
	for(int k = -1; k < 2; k=k+2) {   //Want values of -1 and 1 only (check behind and in front of the king for moves)	  
	  if(j-1 >= 0 && (i-k >= 0 && i-k < 8)) {  //use j-1 to check left of the king and use i-k to check both directions for king O's and X's
	    if(board[i-k][j-1].getTeam() == 0) {   //Check left diagonals for null spots 
	      return turn;                         //return true if there is a null there (so the piece can move there)
	    }
	  }
	  if(j+1 < 8 && (i-k >= 0 && i-k < 8)) {   //use j+1 to check right of the king and use i-k to check both directions for king O's and X's
	    if(board[i-k][j+1].getTeam() == 0) {   //Check right diagonals for null spots 
	      return turn;                         //return true if there is a null there (so the piece can move there)
	    }
	  }
	}
	
      }
      
      else {  //if the piece is not a king, check the diagonals for blank spaces
	//use (j-turn) to check correct direction for blanks depending on team
	if(j-1 >= 0 && (i-turn >= 0 && i-turn < 8)) { //for turn == -1 (team o)
	  if(board[i-turn][j-1].getTeam() == 0) { //if there is a null spot available for move
	    return turn;
	  }
	}
	if(j+1 < 8 && (i-turn >= 0 && i-turn < 8)) { //for turn == 1 (team x)
	  if(board[i-turn][j+1].getTeam() == 0) {  //if there is a null spot available for move
	    return turn;
	  }
	}
      }
     
    }
  }

  return 0;  //if it reaches here, there is no legal move, so return 0
}

//returns turn if the piece associated with board[m][n] has a jump, false if not
int checkers::checkPieceJump(int i, int j) {

  if(board[i][j].getIsNull() == 0) {      //if the space is playable
    if(board[i][j].getTeam() == turn) {   //if team of a piece == turn (the piece belongs to the current player)
      
      
      if(board[i][j].getIsKing() == 1) {  //if the piece is king
	for(int k = -1; k < 2; k=k+2) {   //Want values of -1 and 1 only (check behind and in front of the king for jumps)
	  
	  if(j-2 >= 0 && (i-k*2 >= 0 && i-k*2 < 8)) {   //if the jump spot is on the board to the left of the king
	    if(board[i-k][j-1].getTeam() == -turn) {  //and if there is an opposing piece adjacent to the king 
	      if(board[i-2*k][j-2].getTeam() == 0) {    //and there is a blank space behind it 
		return turn;  //return 1 if x can play, -1 if o can play
	      }
	    }
	  }
	  if(j+2 < 8 && (i-2*k >= 0 && i-2*k < 8)) {    //if the jump spot is on the board to the right of the king
	    if(board[i-k*2][j+1].getTeam() == -turn) {  //and if there is an opposing piece adjancent to the king //CRAIG there was no *2 on the k for this, so i added it
	      if(board[i-k*2][j+2].getTeam() == 0) {    //and there is a blank space behind it
		    return turn;  //return 1 if x can play, -1 if o can play
	      }
	    }
	  }
	  
	}
      }
      else {  //if the piece isn't a king, check the forward diagonals for pieces to jump
	if(j-2 >= 0 && (i-2*turn >= 0 && i-2*turn < 8)) { 
	  //use (j-turn) to check correct direction for blanks
	  if(board[i-turn][j-1].getTeam() == -turn) {  //if turn == 1 (team x) and if there is an opposing piece adjacent
	    if(board[i-2*turn][j-2].getTeam() == 0) {  //and there is a blank space behind it
	      return turn;  //return 1 if x can play, -1 if o can play
	    }
	  }
	}
	if(j+2 < 8 && (i-2*turn >= 0 && i-2*turn < 8)) {
	  if(board[i-turn][j+1].getTeam() == -turn) {  //if turn == -1 (team o) and if there is an opposing piece adjacent
	    if(board[i-2*turn][j+2].getTeam() == 0) {  //and there is a blank space behind it
	      return turn;  //return 1 if x can play, -1 if o can play
	    }
	  }
	}
      }
      
    }	
  }
  
  return 0;  // if it reaches here, there is no legal jump for this piece
      
}

//returns 1 if x can move, -1 if o can move, and 0 is no moves available for current player on entire board
int checkers::checkForMove() {

  for(int i = 0; i < 8; i++) {    //column coordinate
    for(int j = 0; j < 8; j++) {  //row coordinate  (check both ways)
      if (checkPieceMove(i,j) == turn ) {
	return checkPieceMove(i,j);
      }
    }
  }
  return 0; //if there are no moves left for that turn

      //}
      //}
      /*
      if(board[i][j].getIsNull() == 0) {      //if the piece is not a null
	if(board[i][j].getTeam() == turn) {   //if team of the piece == turn

	  if(board[i][j].getIsKing() == 1) {  //if the piece is king
	    for(int k = -1; k < 2; k=k+2) {   //Want values of -1 and 1 only (check behind and in front of the king for jumps)

	      if(j-1 >= 0 && (i-k >= 0 && i-k < 8)) {  //use i-k to check both directions for king O's and X's
		if(board[i-k][j-1].getTeam() == 0) {   //Check left diagonals
		  return turn;                         //return turn
		}
	      }
	      if(j+1 < 8 && (i-k >= 0 && i-k < 8)) {
		if(board[i-k][j+1].getTeam() == 0) {   //Check right diagonals
		  return turn;                         //return turn
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

  return 0;  //if it reaches here, there is no legal move
      */
}

//returns 1 if x can jump, -1 if o can jump, 0 if no jumps available for current player
int checkers::checkForJump() {

  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {              //check the whole board
      if (checkPieceJump(i,j) == turn ) {
	return checkPieceJump(i,j);
      }
    }
  }
  return 0; //if there are no moves left for that turn

      //checkPieceJump(i,j);
      //}
      //}
      /*
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
      */
}

//return 1 if x wins, -1 if o wins, 0 if nobody has won
int checkers::checkForWin() {
  //First, check whole board for pieces of current player's type
  cout << "First" << endl; //debugging

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
  cout << "Before checkForMove" << endl; //debugging

  if(checkForMove()!=0) {  //If checkFor Move is true (if the current player has a move available on the board)
    return 0;           //There is a legal move: game is not over
  }

  cout << "Before checkForJump" << endl;

  if(checkForJump()!=0) {  //if there is a jump available for the current player
    return 0;           //The game is not over
  }

  //If it reaches this point, current player had no legal moves available, so the opposite team wins 
  return -turn;
}
