#ifndef UGURKAGAN_CAKIR_UGURKAGAN_HW6_BOARDCLASS_H
#define UGURKAGAN_CAKIR_UGURKAGAN_HW6_BOARDCLASS_H

class Board
{
private:
	char theBoard[2][6];	//the board object that the game is playing on

public:
	Board();							//default constructor			
	void displayBoard() const;			
	char getOwner(int, int) const;		
	void setOwner(int, int, char);		
	bool isFull() const;				
	int countOwnedCells(char) const;	

};

#endif