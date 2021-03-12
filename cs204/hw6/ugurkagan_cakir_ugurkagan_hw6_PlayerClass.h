#ifndef UGURKAGAN_CAKIR_UGURKAGAN_HW6_PLAYERCLASS_H
#define UGURKAGAN_CAKIR_UGURKAGAN_HW6_PLAYERCLASS_H
#include "ugurkagan_cakir_ugurkagan_hw6_BoardClass.h"

class Player
{
private:
	char identity;			//name of the player
	int rowCoordinate;		//current row coordinate
	int colCoordinate;		//current column coordinate
	int direction;			//1 for clockwise 0 for counter-clockwise
	Board & playboard;		//the board object that player plays on

public:
	Player(Board &, char, int);			//constructor with parameters
	void move(int);
	void claimOwnership();
	bool wins() const;
	int getRow() const;
	int getCol() const;

};
#endif