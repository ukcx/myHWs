#include "ugurkagan_cakir_ugurkagan_hw6_PlayerClass.h"

//constructor with parameters takes identity, direction and the board object that will player play on
//playboard is a reference variable it should use a already existed Board object
Player::Player(Board & board, char id, int dir)
	:playboard(board), identity(id), direction(dir)
{
	colCoordinate = 0;
	rowCoordinate = 0;
}

//moves the player along the playboard
//row and column coordinates are updated according to amount of move
void Player::move(int amountToMove) 
{
	if(amountToMove > 0)
	{
		while(amountToMove != 0) 
		{
			if(direction == 1 && rowCoordinate == 0) //clockwise & upper row
			{
				if(colCoordinate == 5)	//top right corner of the board
					rowCoordinate += 1;
				else
					colCoordinate += 1;
			}
			else if(direction == 1 && rowCoordinate == 1) //clockwise & lower row
			{
				if(colCoordinate == 0)	//bottom left corner of the board
					rowCoordinate -= 1;
				else
					colCoordinate -= 1;
			}
			else if(direction == 0 && rowCoordinate == 0) //counter-clockwise & upper row
			{
				if(colCoordinate == 0)	//top left corner of the board
					rowCoordinate += 1;
				else
					colCoordinate -= 1;
			}
			else if(direction == 0 && rowCoordinate == 1) //counter-clockwise & lower row
			{
				if(colCoordinate == 5)	//bottom right corner of the board
					rowCoordinate -= 1;
				else
					colCoordinate += 1;
			}

			amountToMove -= 1;
		}
	}
}

//claim a cell in the playboard for the player
void Player::claimOwnership() 
{
	if(playboard.getOwner(rowCoordinate, colCoordinate) == '-')
		playboard.setOwner(rowCoordinate, colCoordinate, identity);
}

//if a Player is filled more than half of the playboard, it wins
bool Player::wins() const
{
	if(playboard.countOwnedCells(identity) >= 7)
		return true;
	else
		return false;
}

//return the row coordinate in the board that player is on at that moment 
int Player::getRow() const 
{
	return rowCoordinate;
}

//return the column coordinate in the board that player is on at that moment 
int Player::getCol() const
{
	return colCoordinate;
}