#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ModifiedPriorityQueue.h"
using namespace std;

struct point
{
	int x_coor;		//x coordinate of the point
	int id;			//the position of the building when it was read from the file
	string side;	//side of the building, generally left or right

	point::point(){}
	point::point(int x, int label, string sd)
	{
		  x_coor = x;
		  id = label; 
		  side = sd;
	}
};

void HeapSort( point * &points, int total_size)	//to sort an array of point struct, with respect to x_coor in ascending order
{
	point * heap = new point[total_size + 1];	//heap is the binary heap version of the array points
	for(int i = 0; i < total_size; i++)
	{
		heap[i + 1] = points[i];
	}

	int currentSize = total_size;				//currentSize will be used to relocating maximum elements to the end of the array

	for( int hole = total_size / 2; hole > 0; hole--)	//turn heap into maxheap
	{
		int child = 0;
		point temp = heap[ hole ]; 

		for( ; hole * 2 <= total_size; hole = child )	//perculate down
        {
            child = hole * 2;
			if( child != total_size && heap[ child + 1 ].x_coor > heap[ child ].x_coor )
                child++; 
			if( heap[ child ].x_coor > temp.x_coor )	//perculate down is needed
			{
                heap[ hole ] = heap[ child ];		
			}
            else
                break;
        }
		heap[ hole ] = temp;							//insert the element into the new position found by perculating down

	}

	for(int i = 0; i < total_size; i++)					//it would operate N deleteMax() operations
	{
		int child = 0;
		int hole = 1;
		point temp = heap[ hole ];
		if(heap[hole].x_coor > heap[currentSize].x_coor)	//this might not be the case if most of the max elements are moved to the end of the array
		{													
			heap[ hole ] = heap[ currentSize];
			heap[currentSize] = temp;
			temp = heap[hole];
		}

		currentSize--;
       
		for( ; hole * 2 <= currentSize; hole = child )		//perculate up
		{
			child = hole * 2;
			if( child != currentSize && heap[ child + 1 ].x_coor > heap[ child ].x_coor )
				child++; 
			if( heap[ child ].x_coor > temp.x_coor )		//perculate up is needed
				heap[ hole ] = heap[ child ]; 
			else
				break;
		}
		heap[ hole ] = temp;
	}

	for(int i = 1; i <= total_size; i++)				//put the values from sorted heap to the original array
	{
		points[i - 1] = heap[i];
	}

	delete []heap;
}

int main()
{
	fstream in;
	string fileName = "input.txt";
	string line;
	in.open(fileName.c_str());
	if(!(in.fail()))									//if the file can be opened
	{
		int num_of_buildings;
		getline(in, line);								//first line of the input.txt file
		istringstream values(line);
		values >> num_of_buildings;
		point * point_inputs = new point[num_of_buildings * 2];		//array to store the information about buildings as a point struct
		int * heights = new int[num_of_buildings];					//array to store heights of the buildings

		for(int i = 0; i < num_of_buildings * 2; i+=2)		//i's are incremented by 2 since each line stores x of left and right side
		{
			int height, x_left, x_right;
			getline(in, line);
			istringstream info(line);
			info >> x_left >> height >> x_right;
			point left_point(x_left, i/2 , "left");			//left side of the building
			point right_point(x_right, i/2 , "right");		//right side of the building
			point_inputs[i] = left_point;
			point_inputs[i+1] = right_point;
			heights[i/2] = height;							
		}

		HeapSort(point_inputs, num_of_buildings * 2);			//sort the array of points with respect to x_coor in ascending order
		ModifiedPriorityQueue buildings(num_of_buildings);		//the ModifiedPriorityQueue object to store the buildings we currently see
		int current_id = -1;
		int current_x_value = -1;
		int current_max_height = -1;

		point zeroth(0 , -1 , "zeroth");						//position of x before starting
		point current_point = zeroth;							//will iterate through point_inputs
		while(current_id < num_of_buildings *2)					//num_of_buildings *2 = size of point_inputs array
		{
			
			do
			{
				if(current_point.side == "left")				//if the side is left we currently start to see the building
				{
					sky_line tmp(heights[current_point.id], current_point.id);
					buildings.insert(tmp, current_point.id);
				}
				else if(current_point.side == "right")			//if the side is right we stopped seing the building
				{
					buildings.remove(current_point.id);
				}
				current_x_value = current_point.x_coor;
				current_id++;
				if(current_id != num_of_buildings * 2)
					current_point = point_inputs[current_id];
				else
					break;

			}while(current_x_value == current_point.x_coor);	//keep iterating through while consecutive elements in array have same x coordinates

			int maxHeight = buildings.GetMax();
			if(current_max_height != maxHeight)					//if the max height found so far is changed
			{
				cout << current_x_value << " " <<  maxHeight << endl;
				current_max_height = maxHeight;					//update the max height
			}
		}

		delete[] heights;			//delete the dynamically created arrays
		delete[] point_inputs;
	}

	return 0;
}