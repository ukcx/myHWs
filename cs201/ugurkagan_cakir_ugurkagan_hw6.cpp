#include "randgen.h"
#include "MiniFW_Modified.h"
#include "Robots_Modified.h"
#include "strutils.h"

using namespace std;

bool isEmpty()					//checks if the all environment empty or not
{
	bool empty = false;
	if(GetThingCount(0, 0, 7, 7) == 0)
				empty = true;
	return empty;
}
void move_monster(Robot & monster)		//moves monster robots
{
	RandGen ran;
	Direction way = Direction(ran.RandInt(0,3));
	monster.TurnFace(way);
	monster.Move();
	
	if(!(monster.isAlive()))
		{
			monster.Resurrect();
		}
	monster.PickAllThings();


}
void move_user(Robot & user_robot)			//moves player robot
{
	Direction dir;
	if(IsPressed(256 + VK_UP))		//uparrow
	{
		dir = north;
		user_robot.TurnFace(dir);
		user_robot.Move();
	}
	else if(IsPressed(256 + VK_DOWN))	//downarrow
	{
		dir = south;
		user_robot.TurnFace(dir);
		user_robot.Move();
	}
	else if(IsPressed(256 + VK_RIGHT))   //rightarrow
	{
		dir = east;
		user_robot.TurnFace(dir);
		user_robot.Move();
	}
	else if(IsPressed(256 + VK_LEFT))	//leftarrow
	{
		dir = west;
		user_robot.TurnFace(dir);
		user_robot.Move();
	}
}

Robot winner(Robot user, Robot mon_1, Robot mon_2, Robot mon_3)
{
	int max = 0;				//returns winner robot
	int id;
	if(user.GetBagCount() > max)
	{
		max = user.GetBagCount();
		id = 0;
	}
	if(mon_1.GetBagCount() > max)
	{
		max = mon_1.GetBagCount();
		id = 1;
	}	
	if(mon_2.GetBagCount() > max)
	{
		max = mon_2.GetBagCount();
		id = 2;
	}
	if(mon_3.GetBagCount() > max)
	{
		max = mon_3.GetBagCount();
		id = 3;
	}

	if(id == 0)
		return user;
	else if (id == 1)			//id's for returning right robot
		return mon_1;
	else if (id == 2)
		return mon_2;
	else
		return mon_3;

}
int main()
{
	Robot user(5, 2), monster_1(0, 0), monster_2(0, 7), monster_3(7, 7);
	string name1 = "", name2 = "", name3 = "", name4 = "";
	user.SetColor(blue);
	monster_1.SetColor(red);
	monster_2.SetColor(red);
	monster_3.SetColor(red);
	GetInput("Please enter the name of the player robot: ", name1);
	GetInput("Please enter the name of the monster robot 1: ", name2);		//get the name of the robots
	GetInput("Please enter the name of the monster robot 2: ", name3);
	GetInput("Please enter the name of the monster robot 3: ", name4);

	RandGen rand;
	int i=0;
	while(i < 20)
	{
		int x = rand.RandInt(0,7);
		int y = rand.RandInt(0,7);
		if(GetCellCount(x, y) == 0)							//filling the cells randomly
		{
			int num_of_things = rand.RandInt(1,10);
			PutThings(x, y, num_of_things);
			i++;
		}
	}

	user.SetName(name1);						//names are set
	monster_1.SetName(name2);
	monster_2.SetName(name3);
	monster_3.SetName(name4);



		int lives = 3;

		while(!isEmpty() && lives > 0)			//while not out of lives and at least a cell is full it continues
		{
			move_monster(monster_1);
			if(!isEmpty())
				move_monster(monster_2);
			if(!isEmpty())
				move_monster(monster_3);
			if(!isEmpty())
			{
				move_user(user);
				if(user.isAlive())
				{
					user.PickAllThings();
				}
				else
				{
					lives--;				//number of lives
					ShowMessage("You have " + itoa(lives) + " lives left");
					user.Resurrect();
					if (lives == 0)
						ShowMessage(user.GetName() + " is out of lives, you just lost the game.");


				}
			}
		}
		
		
		string winner_name = winner(user, monster_1, monster_2, monster_3).GetName();		//name of the winner robot
		
		if (winner_name == user.GetName())
			ShowMessage("Congratulations. "+ user.GetName() + " has won the game.");
		else
			ShowMessage( winner_name + " has won the game.");



	return 0;
}