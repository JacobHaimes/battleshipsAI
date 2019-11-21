/**
 * @brief MyPlayer AI for battleships
 * @file MyPlayer.cpp
 * @author Ben Byrd
 * @date April, 2018
 *
 * This Battleships AI is very simple and does nothing beyond playing
 * a legal game. However, that makes it a good starting point for writing
 * a more sophisticated AI.
 *
 * The constructor
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>



#include "MyPlayer.h"


/**
 * @brief Constructor that initializes any inter-round data structures.
 * @param boardSize Indication of the size of the board that is in use.
 *
 * The constructor runs when the AI is instantiated (the object gets created)
 * and is responsible for initializing everything that needs to be initialized
 * before any of the rounds happen. The constructor does not get called 
 * before rounds; newRound() gets called before every round.
 */
MyPlayer::MyPlayer( int boardSize )
    :PlayerV2(boardSize)
{
    // Could do any initialization of inter-round data structures here.
}

/**
 * @brief Destructor placeholder.
 * If your code does anything that requires cleanup when the object is
 * destroyed, do it here in the destructor.
 */
MyPlayer::~MyPlayer( ) {}

/*
 * Private internal function that initializes a MAX_BOARD_SIZE 2D array of char to water.
 */
void MyPlayer::initializeBoard() {
    for(int row=0; row<boardSize; row++) {
	for(int col=0; col<boardSize; col++) {
	    this->board[row][col] = WATER;
	    this->oppBoard[row][col] = WATER;
	}
    }
}


/**
 * @brief Specifies the AI's shot choice and returns the information to the caller.
 * @return Message The most important parts of the returned message are 
 * the row and column values. 
 *
 * See the Message class documentation for more information on the 
 * Message constructor.
 */
Message MyPlayer::getMove() {
    if(isFirstShot){
	scanRow = 0;//(boardSize/2)-4;
	scanCol = 2;//2;
	row = scanRow;
	col= scanCol;
	isFirstShot = false;
    }
   while(oppBoard[row][col]!=WATER){
       if(oppBoard[scanRow][scanCol]==HIT) {
	    killShip(scanRow, scanCol, row, col);
	}
	else if(oppBoard[scanRow][scanCol] == MISS) {
	    if (scanCol+3>=boardSize){
		scanCol = (scanCol+3 - boardSize);
	    }
	    else {
		scanCol+=3;
	    }
        if(scanRow+1>=boardSize){
		    scanRow = 0;
		}else {
		    scanRow++;
		} 

	    col = scanCol;
	    row = scanRow;
	}
	else {
	    while (oppBoard[scanRow][scanCol]==KILL){
		if (scanCol+2>=boardSize){
		}else {
		    scanCol+=2;
        }
		if(scanRow+1>=boardSize){
			scanRow = 0;
<<<<<<< .mine
		}else {
			scanRow++;
||||||| .r4
		    }else {
			scanRow++;
=======
>>>>>>> .r7
<<<<<<< .mine
		}    
||||||| .r4
		    }
		    scanCol = (scanCol+3 - boardSize);
		}else {
		    scanCol+=3;
		    
		}
=======
		    }
		    else {
		        scanRow++;
		    }
		    scanCol = (scanCol+3 - boardSize);
		}
		else {
		    scanCol+=3;
		}
>>>>>>> .r7
		col = scanCol;
		row = scanRow;
	    }
       }
    }

    Message result( SHOT, row, col, "Bang", None, 1 );
    return result;
}

void MyPlayer::killShip(int scanRow, int scanCol, int& row, int& col){
    for(int r=scanRow+1; r<boardSize; r++){
	if(oppBoard[r][scanCol]==WATER){
	    row =r;
	    col = scanCol;
	    return;
	}
	else if (oppBoard[r][scanCol]==MISS || oppBoard[r][scanCol]==KILL){
	    break; 
	}

    } 
    for(int r=scanRow-1; r>=0;--r){
	if(oppBoard[r][scanCol]==WATER){
	    row =r;
	    col = scanCol;
	    return;
	}
	else if (oppBoard[r][scanCol]==MISS || oppBoard[r][scanCol]==KILL){
	    break; 
	}
    }
    for(int c=scanCol+1; c<boardSize; c++){
	if(oppBoard[scanRow][c]==WATER){
	    col =c;
	    row = scanRow;
	    return;
	}
	else if (oppBoard[scanRow][c]==MISS || oppBoard[scanRow][c] == KILL){
	    break; 
	}

    } 
    for(int c=scanCol-1; c>=0;--c){
	if(oppBoard[scanRow][c]==WATER){
	    col =c;
	    row = scanRow;
	    return;
	}
	else if (oppBoard[scanRow][c]==MISS || oppBoard[scanRow][c] == KILL){
	    break; 
	}
    }
}

/**
 * @brief Tells the AI that a new round is beginning.
 * The AI show reinitialize any intra-round data structures.
 */
void MyPlayer::newRound() {
    /* DumbPlayer is too simple to do any inter-round learning. Smarter players 
     * reinitialize any round-specific data structures here.
     */
    this->lastRow = 0;
    this->lastCol = -1;
    this->numShipsPlaced = 0;

    this->initializeBoard();

    this->isFirstShot = true;
}

/**
 * @brief Gets the AI's ship placement choice. This is then returned to the caller.
 * @param length The length of the ship to be placed.
 * @return Message The most important parts of the returned message are 
 * the direction, row, and column values. 
 *
 * The parameters returned via the message are:
 * 1. the operation: must be PLACE_SHIP 
 * 2. ship top row value
 * 3. ship top col value
 * 4. a string for the ship name
 * 5. direction Horizontal/Vertical (see defines.h)
 * 6. ship length (should match the length passed to placeShip)
 */
Message MyPlayer::placeShip(int length) {
    char shipName[10];
    // Create ship names each time called: Ship0, Ship1, Ship2, ...
    snprintf(shipName, sizeof shipName, "Ship%d", numShipsPlaced);
    //Stuff I've added
    if(numShipsPlaced==0&&length==3){
	Message response( PLACE_SHIP, boardSize-1, 0, shipName, Horizontal, length);
	markShip(Horizontal, boardSize-length, 0, length);
	numShipsPlaced++;
	return response;
    }
    else {
	while (true){
	    Direction dir = Direction(((rand()%2)+1));
	    int row = rand()%boardSize;
	    int col = rand()%boardSize;
	    if(isLegal(dir,row,col,length)){ //NEED TO CREATE isLegal FUNCTION!!!
	        markShip(dir,row,col,length);
	        Message response( PLACE_SHIP, row, col, shipName, dir, length);
	        numShipsPlaced++;
	        return response;
            }
	}
    }
    // parameters = mesg type (PLACE_SHIP), row, col, a string, direction (Horizontal/Vertical)
    //Message response( PLACE_SHIP, numShipsPlaced, 0, shipName, dir, length );

//    return response;
}

//markShip Function marks the board where a ship is placed

void MyPlayer::markShip (Direction dir, int row, int col, int len){
    if(dir == Vertical){
	for (int i=row; i<row+len; i++){
	    board[i][col]=SHIP;
	}
    }
    if(dir == Horizontal){
	for (int i=col; i<col+len; i++){
	board[row][i]=SHIP;
	}
    }
}


//isLegal Function needs to check if a ship placement is legal--Hopefully this works...

bool MyPlayer::isLegal(Direction dir,int row, int col, int len){
    if(row >= boardSize || row < 0 || col >= boardSize || col < 0){
	return false;
    }
    if(row+len-1 >= boardSize || row+len-1 < 0 || col+len-1 >= boardSize || col+len-1 <0){
	return false;
    }
    if(dir == Vertical){
	for (int i=row; i<row+len; i++){
	    if (board[i][col]!=WATER){
		return false;
	    }
	}
    }

    if(dir == Horizontal){
	for (int i=col; i<col+len; i++){
	    if (board[row][i]!=WATER){
		return false;
	    }
	}
    }
    return true;
}


/**
 * @brief Updates the AI with the results of its shots and where the opponent is shooting.
 * @param msg Message specifying what happened + row/col as appropriate.
 */
void MyPlayer::update(Message msg) {
    switch(msg.getMessageType()) {
	case HIT:
	case KILL: 
	case MISS:
	    oppBoard[msg.getRow()][msg.getCol()] = msg.getMessageType();
	    break;
	case WIN:
	    break;
	case LOSE:
	    break;
	case TIE:
	    break;
	case OPPONENT_SHOT:
	    // TODO: get rid of the cout, but replace in your AI with code that does something
	    // useful with the information about where the opponent is shooting.
	    //cout << gotoRowCol(20, 30) << "DumbPl: opponent shot at "<< msg.getRow() << ", " << msg.getCol() << flush;
	    break;
    }
}

