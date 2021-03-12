#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct student				//this struct holds the id, name and grade of a student
{
	string id;
	string name;
	double grade;
};

int counting_zero(const vector<student> & myVec)
{
	int counter = 0;						//counts the students that have 0 grade
	int size = myVec.size();
	for(int i = 0; i < size; i++)
	{
		if ( myVec[i].grade == 0)
			counter++;
	}
	return counter;
}

string last_name(const string & name)
{
	string word, last_name;					//inputs full name and returns only the last name
	istringstream cstring(name);
	while (cstring >> word)
	{
		last_name = word;
	}
	return last_name;
}

void sorting_vector(vector<student> & myVec, int size)
{
	for(int j = 0; j < size - 1; j++)			//this function sorts the vector according to grades
	{
		double max_so_far = myVec[j].grade;
		for(int k = j + 1; k < size; k++)
		{
			if(myVec[k].grade > max_so_far)
			{
				student temp;
				max_so_far = myVec[k].grade;
				temp = myVec[j];
				myVec[j] = myVec[k];
				myVec[k] = temp;
			}
			else if(myVec[k].grade == max_so_far)
			{
				string r = myVec[j].name;
				string s = myVec[k].name;
				string last_name_j = last_name(r);
				string last_name_k = last_name(s);
				if (last_name_k < last_name_j)
				{
					student temp;
					temp = myVec[j];
					myVec[j] = myVec[k];
					myVec[k] = temp;
				}
			}
		}
	}
}

void display_vector(const vector<student> & myVec, int rank)
{
	int size = myVec.size();				//displays appropriate message according to given rank input
	if (rank > 0 && rank <= size)				
	{
		cout << rank << ", " << myVec[rank-1].id << ", " << myVec[rank-1].name << ", " << myVec[rank-1].grade << endl;
	}
	else if (rank == 0)
	{
		cout << "Exiting..." << endl;
	}
	else
	{
		cout << "Rank needs to be greater than 0 and smaller than " << size + 1 << "!" << endl;
	}
}
int main()
{

	string file1, file2;
	ifstream in, input;
	

	cout << "Please enter a filename for Students Grades Results: ";
	cin >> file1;
	in.open(file1.c_str());
	if (in.fail())
		cout << "Can not find the requested file. Terminating application ..." <<endl;
	else
	{
		cout << "Please enter a filename for Students Names : ";
		cin >> file2;
		input.open(file2.c_str());
		if (input.fail())
			cout << "Can not find the requested file. Terminating application ..."<< endl;
		else               //both files opened successfully
		{
			string line1,line2;	
			int size = 0;
			vector<student> students;
			double weight;
			while(getline(input, line1))		//every line in student file
			{
				size++;
				string word, name;
				student one_student;
				string id;
				istringstream astring(line1);
				astring >> id >> name;
				while (astring >> word)		//whole name
					name += " " + word;
				one_student.id = id;
				one_student.name = name;
				one_student.grade = 0;
				students.push_back(one_student);
			}
			while(getline(in, line2))          //every line in grades file
			{	
				double exam_note, weighted_exam_note;
				string  num;	
				if (line2 == "***HOMEWORK***")
				{
					weight = 0.1;
				}
				else if (line2 == "***MIDTERM***")			//weight changes according to assignment type 
				{
					weight = 0.2;
				}
				else if (line2 == "***FINAL***")
				{
					weight = 0.3;
				}
				else if (line2 == "");
				else
				{
					bool flag = true;
					istringstream bstring(line2);
					bstring >> num >> exam_note;
					weighted_exam_note = exam_note * weight;  
					for(int i = 0; i < size && flag; i++)
					{
						if (students[i].id == num)
						{							
							students[i].grade += weighted_exam_note;
							flag = false; 
						}
					}
				}
			}
			int zero_grade = counting_zero(students);
			sorting_vector(students, size);

			for(int m = 0; m < zero_grade; m++)
				students.pop_back();			//removes students that have 0 grade
			
			int rank;
			
			do
			{
				cout << "Enter the rank you want to query (enter 0 to exit): ";
				cin >> rank;
				display_vector(students, rank);
			}while (rank != 0);
		
		}

	}
	
	return 0;
}