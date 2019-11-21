/**
 * @author Stefan Brandle, Jonathan Geisler
 * @date September, 2004
 *
 * Please type in your name[s] here:
 *
 */

#ifndef MYPLAYERV2_H		// Double inclusion protection
#define MYPLAYERV2_H

using namespace std;

#include "PlayerV2.h"
#include "Message.h"
#include "defines.h"

// DumbPlayer inherits from/extends PlayerV2

class MyPlayer: public PlayerV2 {
    public:
	MyPlayer( int boardSize );
	~MyPlayer();
	void newRound();
	Message placeShip(int length);
	Message getMove();
	void update(Message msg);

    private:
	void initializeBoard();
	bool isFirstShot;
	int firstRow;
	int numRow;
	int scanRow;
	int scanCol;
	int shotRow;
	int shotCol;
        int lastRow;
        int lastCol;
	int row;
	int col;
	int numShipsPlaced;
        char oppBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
        char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];  
    bool isLegal(Direction dir, int row, int col, int len);
	void markShip (Direction dir, int row, int col, int len);
	void killShip(int scanRow, int scanCol, int& row, int&col);
};
    
#endif
