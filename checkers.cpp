#include "checkers.h"
#include "piece.h"

//constructor
checkers::checkers() {

  //seed random numbers
  srand(time(0));

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
  //countPieces(); //debugging
  cout << endl << endl << "     ***** Welcome to Checkers! *****" << endl << endl << endl;

  do {          //Select game type
    choice = 0;
    cout << "Choose one of the following options: " << endl;
    cout << "1: Human vs. Human game" << endl;
    cout << "2: AI vs. Human game" << endl;
    cout << "3: Example game: Enter name of a .txt file to play." << endl;
    cout << "4: Instructions" << endl;
    cin >> choice;
    if (choice == 4) {
      ifstream myfile;
      string line;
      myfile.open("instructions.txt");
      if(myfile.is_open()) {
	while(myfile.good()) {
	  getline(myfile,line);
	  cout << line << endl;
	}
	
	myfile.close();
      }
      else {
	cout << "ERROR: Instructions failed to open" << endl;
      }
      choice = 0;
    }
  } while(choice != 1 && choice != 2 && choice != 3 );

  if(choice == 3) {             //if they chose example game
    ifstream myfile;            //Holds the actual file.txt
    cout << "Enter the name of the .txt you wish to play: " << endl;
    cout << "   Choices are: doublejump.txt, kingme.txt, diamond.txt, and victory.txt" << endl;
    cin >> name;                //takes in file name input
    myfile.open(name.c_str());  //opens the file
    if(myfile.is_open()) {      //if the file opens
      while(myfile.good()) {    //and does not equal EOF
	int temp;               
	myfile >> temp;         //read in from the file
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
    //for(unsigned int i = 0; i < moves.size(); i++) { //debugging
    //  cout << moves[i] << " ";
    //}
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
  int winner;                              //variable that keeps track of who won once game is over
  cout << endl << endl << "***** Game Start ******" << endl << endl;


  while( (winner = checkForWin()) == 0 ) { //while nobody has won yet
    print();                                 //First, print the board
    countPieces();                           //Then count the pieces of each type.
    getInput();                            //get input from user or example text
    if(checkForJump()!=0) {                //if there are jumps on the board
      while(checkPieceJump(x, y)!=0) {     //while there is a jump available for a piece (this allows for double jumps)
	executeJump();                     //make the jump
	if(checkPieceJump(x, y) != 0) {
	  print();                           //print for each consecutive jump
	  countPieces();                     //count pieces
	}
      }
    }
    else {                                 //If checkForJump is false (there are no jumps on the board), move a piece by switching the piece and the blank
      executeMove();                       //make the move
    }  
    turn *= -1;                            //Switch whose turn it is once their turn ends
  } //END OF WHILE LOOP

  if(winner == 1) {                        //if x wins
    cout << endl << "***** X wins! ******" << endl << endl;
  }
  else {                                   //if o wins
    cout << endl << "***** O wins! ******" << endl << endl;
  }
  cout << "Thank you for playing!" << endl;
  board.clear();
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
  cout << "x count: " << xcount << endl;
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
  cout << "o count: " << ocount << endl;
}

//receives input from player or example text until they choose a good move
void checkers::getInput() {
  int errorCheck = 0;                                //error check to see if piece selection input is valid
  int tempx;                                         //temporary holder for user's input coordinates
  int tempy;

  do {                                               //Use do-while so this happens at least once every turn, and repeats if there is an error in the input
    errorCheck = 0;                                  //initially make error false again
    if(choice == 1 || (choice == 2 && turn == 1)) {  //for user-user game or computer-user game when it's the user's turn
      if(turn == 1) {                                //depending on whose turn it is, ask for input
	cout << "X, input coordinates of the piece you want to move. (row column): ";
      }
      else {
	cout << "O, input coordinates of the piece you want to move. (row column): ";
      }                                              
      cin >> tempx >> tempy;                         //put the inputs into tempx and tempy
    }
    else if(choice == 3) {                           //for example game
      //sleep(1);                                    //wait for one second before executing the move  //debugging
      tempx = moves[0];                              //put the first move coordinates into tempx and tempy
      tempy = moves[1];
      moves.erase(moves.begin());                    //then pop them off moves
      moves.erase(moves.begin());
    }
    else if(choice == 2 && turn == -1) {             //for an AI game when it's the AI's turn
      //sleep(1);
      fill_AI_vars();                                //fill the AI's possible moves and chosen move
      tempx = AI_move[0]+1;                          //read in the AI's choise
      tempy = AI_move[1]+1;
    }

    /***** The following loop checks for possible bad inputs from the user, i.e. choosing a bad location, choosing not to jump when a jump was available, choosing a piece with no legal moves, or choosing the other player's piece *****/
    if( (tempx >= 1 && tempx <= 8) && (tempy >= 1 && tempy <= 8) ) {       //if the user chose a piece on the board
      x = tempx-1;                                                         //subtract one from each to match coordinates with vector elements
      y = tempy-1;	
      if(checkForJump()!=0) {                                              //if there is a jump
	if(checkPieceJump(x, y) == 0) {                                    //and the piece selected cannot jump
	  errorCheck = 1;                                                  //we have a problem
	  cout << "Error: selected piece cannot jump when a jump exists on the board. Please try again." << endl;
	}
      }	
      else if( (checkPieceMove(x, y)!=0) || (checkPieceJump(x, y)!=0) ) {  //if the selected piece has a legal move
	if(board[x][y].getTeam() != turn) {                                //If the user inputs a piece that is not his
	  errorCheck = 1;                                                  //we have a problem
	  cout << "Error: Piece is not yours. Please try again." << endl;
	  print();
	}
      }
      else {                                                               //if the selected piece has no legal move
	errorCheck = 1;                                                    //we have a problem
	cout << "Error: selected piece has no legal moves. Please try again." << endl;
	print();
      }
    }
    else {                                                                 //if the user chose a bad location
      errorCheck = 1;                                                      //we have a problem
      cout << "Error: input invalid. Please try again." << endl;
      print();
    }
  } while(errorCheck == 1); //makes move once the loop completes without finding an error

}

//executes move in play function
void checkers::executeMove() {
  int errorCheck2 = 0;                                     //variable that checks if piece movement input is valid
  int tempa;                                               //briefly holds user's move coordinates
  int tempb;
  piece holder;                                            //piece to temporarily hold board piece values while switching

  do {
    errorCheck2 = 0;                                       //first make the errorCheck2 false
    if(choice == 1 || (choice == 2 && turn == 1)) {
      cout << "Choose a square to move to (row column): "; //for user-user and user-computer games when it's the user's turn
      cin >> tempa >> tempb;
    }
    else if(choice == 3) {                                 //for example game
      sleep(1);                                            //wait for one second before executing the move
      tempa = moves[0];                                    //put moves coordinates into tempa and tempb
      tempb = moves[1];
      moves.erase(moves.begin());                          //pop those coordinates off moves
      moves.erase(moves.begin());
      if(moves.empty()) {                                  //if there are no more moves in line
	choice = 1;                                        //change the game type to human vs human
      }
    }
    else if (choice == 2 && turn == -1) {                  //for an AI game when it's the AI's turn
      sleep(1);
      tempa = AI_move[2]+1;                                //read in the AI's move location
      tempb = AI_move[3]+1;                                //add one since one is subtracted when reading into a and b.
    }
    if( (tempa >= 1 && tempa <= 8) && (tempb >= 1 && tempb <= 8) ) { //if the chosen move is on the board
      a = tempa-1;                                                   //subtract one from each to match cooridinates with vector elements
      b = tempb-1;
      if(board[a][b].getTeam() == 0) {                               //if the space is blank
	if(board[x][y].getIsKing() == 1) {                           //if the piece is a king
	  if( (a == x-1 || a == x+1) && (b == y-1 || b == y+1) ) {   //if space is adjacent
	    holder = board[x][y];                                    //then execute piece switch
	    board[x][y] = board[a][b];
	    board[a][b] = holder;
	    makeKing();                                              //change pieces to kings if needed	    
	  }
	  else {                                                     //if the user picked a non-adjacent move
	    errorCheck2 = 1;
	    cout << "Error: Space is not adjacent to piece selected.  Please try again." << endl;
	  }
	}
	else {                                             //else is piece is not a king
	  if( (a == x-turn) && (b == y-1 || b == y+1) ) {  //if space is on forward diagonal
	    holder = board[x][y];                          //then execute switch
	    board[x][y] = board[a][b];
	    board[a][b] = holder;
	    makeKing();                                    //change piece to king if needed
	  }
	  else {                                           //if the user didn't chose a forward & adjacent move
	    errorCheck2 = 1;
	    cout << "Error: Space is not adjacent and forward of the selected piece.  Please try again." << endl;
	  }
	}
      }
      else {                   //if the user chose a non-empty spot
	errorCheck2 = 1;
	cout << "Error: Space is not empty.  Please try again." << endl;
      }
    }
    else {                     //if the user entered a bad location
      errorCheck2 = 1;
      cout << "Error: Invalid input.  Please try again." << endl;
    }

  } while(errorCheck2 == 1);   //repeat this loop until the user chooses a good move

}

void checkers::executeJump() {
  int errorCheck3 = 0;            //variable that checks if piece jump input is valid
  int tempa;                      //briefly holds user's jump coordinates
  int tempb;
  piece holder;                   //piece to temporarily hold board piece values while switching

  do {
    errorCheck3 = 0;
    if(choice == 1 || (choice == 2 && turn == 1)) {
      cout << "Choose a square to jump to (row column): ";
      cin >> tempa >> tempb;
    }
    else if (choice == 3) {
      sleep(1);                   //wait for one second before executing the move
      tempa = moves[0];           //put moves coordinates into tempa and tempb
      tempb = moves[1];
      moves.erase(moves.begin()); //pop those coordinates off moves
      moves.erase(moves.begin());
      if(moves.empty()) {         //if there are no more moves
	choice = 1;               //change the game type to human vs human
      }
    }
    else if (choice == 2 && turn == -1){ //for AI game when it's the AI's turn
      sleep(1);
      tempa = AI_move[2]+1;              //read in the AI's jump choice
      tempb = AI_move[3]+1;
    }

    if( (tempa >= 1 && tempa <= 8) && (tempb >= 1 && tempb <= 8) ) {
      a = tempa-1;
      b = tempb-1;
      if(board[a][b].getTeam() == 0) {                                //if the space is blank
	if(board[(a+x)/2][(b+y)/2].getTeam() == -turn) {              //if the space in the middle has an opposing piece
	  if(board[x][y].getIsKing() == 1) {                          //if the piece is a king
	    if( (a == x-2 || a == x+2) && (b == y-2 || b == y+2) ) {  //if space to jump to is two away
	      holder = board[x][y];                                   //use holder piece to switch start position and end position
	      board[x][y] = board[a][b];
	      board[a][b] = holder;
	      board[(a+x)/2][(b+y)/2].setTeam(0); //since this piece was jumped, its team allegiance goes to 0
	      x = a;
	      y = b;
	      makeKing();                    //make pieces kings if needed
	      if (checkPieceJump(x,y)!=0) {
	        AI_next_jump(x,y);           //you need to recalculate this for AI doublejumps!
	      }
	    }
	    else {
	      errorCheck3 = 1;
	      cout << "Error: Invalid jump coordiates. Please try again." << endl;
	    }
	  }
	  else {   //if the piece is NOT a king
	    if( (a == x-2*turn) && (b == y-2 || b == y+2) ) {  //if space is on forward diagonal		  
	      holder = board[x][y];               //use holder piece to switch start position and end position
	      board[x][y] = board[a][b];
	      board[a][b] = holder;
	      board[(a+x)/2][(b+y)/2].setTeam(0); //set jumped piece to nobody's team
	      x = a;
	      y = b;
	      makeKing();                         //make pieces kings if needed
	      if (checkPieceJump(x,y)!=0) {
	        AI_next_jump(x,y);                //once again, needed for AI doublejumps!
	      }
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

  } while(errorCheck3 == 1);

}

//finds pieces in back row and kings them
void checkers::makeKing() {

  for(int i = 0; i < 8 ; i++) {
    if(board[0][i].getTeam() == 1) {
      board[0][i].setIsKing(1);
    }
    if(board[7][i].getTeam() == -1) {
      board[7][i].setIsKing(1);
    }
  }

}

void checkers::AI_next_jump(int i, int j) { 

  vector <int> temp;         //holding vector
  AI_move.clear();           //clear private vectors of previously stored moves
  AI_possible_moves.clear();
  temp.clear();
  
  //cout << endl;  //debugging

  if(board[i][j].getIsNull() == 0) {
    if(board[i][j].getTeam() == -1) {
      
      if(board[i][j].getIsKing() == 1) {  //if the piece is king
	for(int k = -1; k < 2; k=k+2) {   //Want values of -1 and 1 only (check behind and in front of the king for jumps)
	  
	  if(j-2 >= 0 && (i-k*2 >= 0 && i-k*2 < 8)) {   //if the jump spot is on the board to the left of the king
	    if(board[i-k][j-1].getTeam() == 1) {    //and if there is an opposing piece adjacent to the king 
	      if(board[i-2*k][j-2].getTeam() == 0) {    //and there is a blank space behind it 
		//cout << "found jump from " << i << " " << j << " to " << i-2*k << " " << j-2 << endl; //debugging
		temp.clear();
		temp.push_back(i);     //push back start location and end location into temporary vector
		temp.push_back(j);
		temp.push_back(i-2*k);
		temp.push_back(j-2);
		AI_possible_moves.push_back(temp); //add the potential move to the 2D vector
	      }
	    }
	  }
	  if(j+2 < 8 && (i-2*k >= 0 && i-2*k < 8)) {    //if the jump spot is on the board to the right of the king
	    if(board[i-k][j+1].getTeam() == 1) {  //and if there is an opposing piece adjancent to the king 
	      if(board[i-k*2][j+2].getTeam() == 0) {    //and there is a blank space behind it
		//cout << "found jump from " << i << " " << j << " to " << i-2*k << " " << j+2 << endl; //debugging
		temp.clear();
		temp.push_back(i);     //push back start and end location into temporary vector
		temp.push_back(j);
		temp.push_back(i-2*k);
		temp.push_back(j+2);
		AI_possible_moves.push_back(temp); //add the potential move to the 2D vector
	      }
	    }
	  }
	  
	}
      }
      else {  //if the piece isn't a king, check the forward diagonals for pieces to jump
	if(j+2 < 8 && (i+2 >= 0 && i+2 < 8)) {	
	  if(board[i+1][j+1].getTeam() == 1) {  //if turn == -1 (team o) and if there is an opposing piece adjacent
	    if(board[i+2][j+2].getTeam() == 0) {  //and there is a blank space behind it
	      //cout << "found jump from " << i << " " << j << " to " << i+2 << " " << j+2 << endl; //debugging
	      temp.clear();
	      temp.push_back(i);       //push start and end location into temp vector
	      temp.push_back(j);
	      temp.push_back(i+2);
	      temp.push_back(j+2);
	      AI_possible_moves.push_back(temp); //add potential move to 2D vector
	    }
	  }
	}
	if(j-2 >= 0 && (i+2 >= 0 && i+2 < 8)) { 	  
	  if(board[i+1][j-1].getTeam() == 1) {
	    if(board[i+2][j-2].getTeam() == 0) {
	      //cout << "found jump from " << i << " " << j << " to " << i+2 << " " << j-2 << endl; //debugging
	      temp.clear();
	      temp.push_back(i);      //push start and end location into temp vector
	      temp.push_back(j);
	      temp.push_back(i+2);
	      temp.push_back(j-2);
	      AI_possible_moves.push_back(temp);  //add potential move to 2D vector
	    }
	  }
	}
      }
    }
  }

  if (!AI_possible_moves.empty()) {
    //cout << "The number of possible jumps is " << AI_possible_moves.size() << endl; //debugging
    int random = ((double)rand()/(double)RAND_MAX) * (AI_possible_moves.size());    //chooses a number between 0 and AI_possible_moves.size
    AI_move = AI_possible_moves[random];    //set the chosen move vector equal to the randomly chosen vector
    return; 
  }

}

void checkers::fill_AI_vars() {

  vector <int> temp;         //holding vector
  AI_possible_moves.clear(); //clear everything to be safe
  AI_move.clear();
  temp.clear();

  //cout << endl; //debugging formatting

  for (int i = 0; i < 8; i++) {   //check the whole board
    for(int j = 0; j < 8; j++) {
      if(board[i][j].getIsNull() == 0) {
	if (checkPieceJump(i,j) == -1) { //if a spot is found where the AI has a jump

	  if(board[i][j].getIsKing() == 1) {  //if the piece is king
	    for(int k = -1; k < 2; k=k+2) {   //Want values of -1 and 1 only (check behind and in front of the king for jumps)
	      
	      if(j-2 >= 0 && (i-k*2 >= 0 && i-k*2 < 8)) {   //if the jump spot is on the board to the left of the king
		if(board[i-k][j-1].getTeam() == 1) {    //and if there is an opposing piece adjacent to the king 
		  if(board[i-2*k][j-2].getTeam() == 0) {    //and there is a blank space behind it 
		    //cout << "found jump from " << i << " " << j << " to " << i-2*k << " " << j-2 << endl;  //debugging
		    temp.clear();
		    temp.push_back(i);     //push back start and end location into temp vector
		    temp.push_back(j);
		    temp.push_back(i-2*k);
		    temp.push_back(j-2);
		    AI_possible_moves.push_back(temp); //add the temp vector to the 2D vector
		  }
		}
	      }
	      if(j+2 < 8 && (i-2*k >= 0 && i-2*k < 8)) {    //if the jump spot is on the board to the right of the king
		if(board[i-k][j+1].getTeam() == 1) {  //and if there is an opposing piece adjancent to the king 
		  if(board[i-k*2][j+2].getTeam() == 0) {    //and there is a blank space behind it
		    //cout << "found jump from " << i << " " << j << " to " << i-2*k << " " << j+2 << endl; //debugging
		    temp.clear();
		    temp.push_back(i);       //push back start and end location into temp vector
		    temp.push_back(j);
		    temp.push_back(i-2*k);
		    temp.push_back(j+2);
		    AI_possible_moves.push_back(temp); //add the temp vector to the 2D vector
		  }
		}
	      }
	      
	    }
	  }
	  else {  //if the piece isn't a king, check the forward diagonals for pieces to jump
	    
	    if(j+2 < 8 && (i+2 >= 0 && i+2 < 8)) {   
	      if(board[i+1][j+1].getTeam() == 1) {  //if an enemy piece is adjacent
		if(board[i+2][j+2].getTeam() == 0) {  //and there is a blank space behind it
		  //cout << "found jump from " << i << " " << j << " to " << i+2 << " " << j+2 << endl; //debugging
		  temp.clear();
		  temp.push_back(i);      //push back start and end location into temp vector
		  temp.push_back(j);
		  temp.push_back(i+2);
		  temp.push_back(j+2);
		  AI_possible_moves.push_back(temp); //add the temp vector to the 2D vector
		}
	      }
	    }
	    if(j-2 >= 0 && (i+2 >= 0 && i+2 < 8)) {
	      if(board[i+1][j-1].getTeam() == 1) {
		if(board[i+2][j-2].getTeam() == 0) {
		  //cout << "found jump from " << i << " " << j << " to " << i+2 << " " << j-2 << endl; //debugging
		  temp.clear();
		  temp.push_back(i);     //push back start and end location into temp vector
		  temp.push_back(j);
		  temp.push_back(i+2);
		  temp.push_back(j-2);
		  AI_possible_moves.push_back(temp); //add the temp vector to the 2D vector
		}
	      }
	    } 
	   
	  }
	    
	}
      }
    }
  }

  //at this point, the function has found all possible jumps. If the 2D vector isn't empty, that means there are jumps available, so the function should choose one of those and return
  if (!AI_possible_moves.empty()) {
    //cout << "the number of possible jumps is " << AI_possible_moves.size() << endl; //debugging
    int random = ((double)rand()/(double)RAND_MAX) * (AI_possible_moves.size());  //choose the random number
    AI_move = AI_possible_moves[random]; //and set the chosen move to that random move
    return;  //return since AI has properly chosen a jump (don't want to investigate moves!)
  }
  
  //Now, if the code reaches here we must check for AI moves
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      if(board[i][j].getIsNull() == 0) {      //if the location is not a null
	if(board[i][j].getTeam() == -1) {     //and if team of the piece == turn
	  if(board[i][j].getIsKing() == 1) {  //and if the piece is king
	    
	    for(int k = -1; k < 2; k=k+2) {   //Want values of -1 and 1 only (check behind and in front of the king for moves)	  
	      if(j-1 >= 0 && (i-k >= 0 && i-k < 8)) {  //use j-1 to check left of the king and use i-k to check both directions for king O's and X's
		if(board[i-k][j-1].getTeam() == 0) {   //Check left diagonals for null spots 
		  temp.clear();
		  //cout << "found move from " << i << " " << j << " to " << i-k << " " << j-1 << endl; //debugging
		  temp.push_back(i);
		  temp.push_back(j);
		  temp.push_back(i-k);
		  temp.push_back(j-1);
		  AI_possible_moves.push_back(temp);
		}
	      }
	      if(j+1 < 8 && (i-k >= 0 && i-k < 8)) {   //use j+1 to check right of the king and use i-k to check both directions for king O's and X's
		if(board[i-k][j+1].getTeam() == 0) {   //Check right diagonals for null spots 
		  temp.clear();
		  //cout << "found move from " << i << " " << j << " to " << i-k << " " << j+1 << endl; //debugging
		  temp.push_back(i);
		  temp.push_back(j);
		  temp.push_back(i-k);
		  temp.push_back(j+1);
		  AI_possible_moves.push_back(temp);
		}
	      }
	    }
	    
	  }
	  
	  else {  //if the piece is not a king, check the diagonals for blank spaces
	    //use (j-turn) to check correct direction for blanks depending on team
	    if(j-1 >= 0 && (i+1 >= 0 && i+1 < 8)) { //for turn == -1 (team o)
	      if(board[i+1][j-1].getTeam() == 0) { //if there is a null spot available for move
		temp.clear();
		//cout << "found move from " << i << " " << j << " to " << i+1 << " " << j-1 << endl; //debugging
		temp.push_back(i);
		temp.push_back(j);
		temp.push_back(i+1);
		temp.push_back(j-1);
		AI_possible_moves.push_back(temp);
	      }
	    }
	    if(j+1 < 8 && (i+1 >= 0 && i+1 < 8)) { //for turn == 1 (team x)
	      if(board[i+1][j+1].getTeam() == 0) {  //if there is a null spot available for move
		temp.clear();
		//cout << "found move from " << i << " " << j << " to " << i+1 << " " << j+1 << endl; //debugging
		temp.push_back(i);
		temp.push_back(j);
		temp.push_back(i+1);
		temp.push_back(j+1);
		AI_possible_moves.push_back(temp);
	      }
	    }
	  }
	  
	}
      }
    }
  }
  
  //cout << "the number of possible moves is " << AI_possible_moves.size() << endl;  //debugging
  int random = ((double)rand()/(double)RAND_MAX) * (AI_possible_moves.size());
  AI_move = AI_possible_moves[random];
  return;
  
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
	    if(board[i-k][j+1].getTeam() == -turn) {  //and if there is an opposing piece adjancent to the king 
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
      if (checkPieceMove(i,j) == turn ) {  //if the current player has a move available
	return checkPieceMove(i,j);        //return the turn of the current player
      }
    }
  }
  return 0; 
}

//returns 1 if x can jump, -1 if o can jump, 0 if no jumps available for current player
int checkers::checkForJump() {

  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {           //check the whole board
      if (checkPieceJump(i,j) == turn ) {  //if the current player has a jump available
	return checkPieceJump(i,j);        //return the turn of the current player
      }
    }
  }
  return 0; //if the current player has no moves on the board, return 0
}

//return 1 if x wins, -1 if o wins, 0 if nobody has won
int checkers::checkForWin() {
  //First, check whole board for pieces of current player's type
  //cout << "First" << endl; //debugging

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
  //cout << "Before checkForMove" << endl; //debugging

  if(checkForMove()!=0) {  //If checkFor Move is true (if the current player has a move available on the board)
    return 0;           //There is a legal move: game is not over
  }

  //cout << "Before checkForJump" << endl;  //debugging

  if(checkForJump()!=0) {  //if there is a jump available for the current player
    return 0;           //The game is not over
  }

  //If it reaches this point, current player had no legal moves available, so the opposite team wins 
  return (-turn);
}
