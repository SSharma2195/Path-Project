#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

/* 
Declaring a structure type Node. Which contain 3 variables 
*/
struct Node
{
	char name;
	int x;
	int y;
};

/*
Declaring a structure type Point, containing 3 variables
*/
struct Point 
{
	int x;
	int y;
	int ascii;
};

string currNod = "";
Point currPnt;

/*
Comparing 2 different nodes
*/
bool comparator(const Node& lhs, const Node& rhs) {
	return lhs.x < rhs.x;
}

bool hasPoint(vector<Point> points, int x, int y)
{
	for (Point pnt : points)
	{
		if (pnt.x == x && pnt.y == y)
		{
			currPnt = pnt;
			return true;
		}
	}
	return false;
}

bool isNode(vector<Node> nodes, int x, int y)
{
	for (Node nod : nodes)
	{
		if (nod.x == x && nod.y == y)
		{
			currNod = nod.name;
			return true;
		}
	}
	return false;
}

/* 
	Displaying a welcome screen. 
	Taking input from the user for the desired csv file to be opened and read. 
	Or randomly generate Nodes to plot a path.
	Has the maximum X and Y axis to plot the path.
*/
void simulateProgram() {
	int leastX = 1000000, maxY = -1000000;
	int maxX = -1000000, leastY = 1000000;
	vector<Node>* nodes = new vector<Node>();
	vector<Point>* points = new vector<Point>();
	char choice;
	string fname;
	cout << "Welcome to Delivery Route Planner \n";
	cout << "Author: Swastik Sharma (10670073)\n";
	cout << "SID: 10670073\n\n";
	cout << "Please choose to enter a filename to read from a text file input, or type Random to create random nodes. \n";		//Liberty for the user to select an input CSV file or let the program randomaly generate nodes
	cout << "Enter file name: ";																								
	cin >> fname;
	ifstream input;
	if (fname != "Random")
	{
		input.open(fname);					//Reading the CSV file
		string line;
		while (!input.eof()) {
			getline(input, line);
			stringstream ss(line);
			string substr;
			getline(ss, substr, ',');
			string name = substr;
			getline(ss, substr, ',');
			int x = stoi(substr);
			getline(ss, substr, ',');
			int y = stoi(substr);
			if (x < leastX)
				leastX = x;
			if (y > maxY)
				maxY = y;
			if (x > maxX)
				maxX = x;
			if (y < leastY)
				leastY = y;
			Node test = {
				name[0],x,y
			};
			nodes->push_back(test);
		}

		cout << endl;
		/*
			A message for the user if the file has been read successfully.
		*/
		if (input.eof()) {
			cout << "File data has been read sucessfully.\n\n";
		}
		else {
			cout << "Error in input file.\n\n";
			return;
		}
	}
	/*
		Randomly generated nodes.
	*/
	else {
		char arr[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
		for (int i = 0; i < 6; i++)
		{
			int x1 = (rand() % 100 + 1);
			int y1 = (rand() % 100 + 1);
			if (x1 < leastX)
				leastX = x1;
			if (x1 > maxX)
				maxX = x1;
			if (y1 < leastY)
				leastY = y1;
			if (y1 > maxY)
				maxY = y1;
			Node test = {
				arr[i],x1,y1
			};
			nodes->push_back(test);
		}
	}
	/*
		Options for user to either go bruteforce or choose nearest neighbour, for the path to be plot
		The program calculates and display the suggested shortest route that has been calculated.
		The program counts the total number of steps and displays them after plotting the Path.
		Program uses 3 different ASCII art on repeat to plot the path.
	*/
	cout << "Enter b(bruteforce), n(nearest neighbour): ";
	cin >> choice;
	if (choice == 'n')
		sort((*nodes).begin(), (*nodes).end(), &comparator);

	cout << "The route planner suggests the following route: \n";
	for (Node nod : *nodes)
	{
		cout << nod.name << "(" << nod.x << "," << nod.y << "), ";
	}
	cout << endl;

	int steps = 0;
	int temp = 176;
	for (int i = 0; i < nodes->size() - 1; i++)
	{
		int tempx1 = nodes->at(i).x;
		int tempy1 = nodes->at(i).y;
		int tempx2 = nodes->at(i + 1).x;
		int tempy2 = nodes->at(i + 1).y;
		while (tempx1 < tempx2)
		{
			steps++;
			tempx1++;
			Point pnt = {
				tempx1,tempy1,temp
			};
			points->push_back(pnt);
		}
		if (tempy1 < tempy2) {
			while (tempy1 < tempy2)
			{
				steps++;
				tempy1++;
				Point pnt = {
					tempx1,tempy1,temp
				};
				points->push_back(pnt);
			}
		}
		if (tempy2 < tempy1) {
			while (tempy2 < tempy1)
			{
				steps++;
				tempy1--;
				Point pnt = {
					tempx1,tempy1,temp
				};
				points->push_back(pnt);
			}
		}
		if (temp == 176)
			temp = 177;
		else if (temp == 177)
			temp = 178;
		else if (temp == 178)
			temp = 176;
	}
	input.close();
	for (int j = leastY - 10; j < maxY + 10; j++)
	{
		for (int i = leastX - 10; i < maxX + 10; i++)
		{
			if (isNode(*nodes, i, j))
			{
				cout << currNod;
			}
			else if (hasPoint(*points, i, j))
			{
				cout << (char)(currPnt.ascii);
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl << endl;
	cout << "Total number of steps: " << steps << endl;

	/*
		An option for the user, if they wish to save the path as .txt file, with their choice of given name.
	*/
	string outName;
	cout << "Enter a filename to save current path, or type n to continue without saving: ";
	cin >> outName;
	cout << endl;
	if (outName != "n")
	{
		ofstream out(outName);
		for (int j = leastY - 10; j < maxY + 10; j++)
		{
			for (int i = leastX - 10; i < maxX + 10; i++)
			{
				if (isNode(*nodes, i, j))
				{
					out << currNod;
				}
				else if (hasPoint(*points, i, j))
				{
					out << (char)(currPnt.ascii);
				}
				else
				{
					out << " ";
				}
			}
			out << endl;
		}
		out.close();
	}
}

/*
	Runs the main program and asks the user if they wish to run it again after each path that had been plotted. 
	User has the liberty to run this program as many times as they wish until unless they decide to lave.
*/

int main() {
	

	char playAgain = 'Y';
	do {
		simulateProgram();
		cout << "To play again, press Y or y, otherwise press N or n: ";
		cin >> playAgain;
		cout << "Thank you for using Delivery Route Planner";
		cout << endl;
	} while (playAgain == 'Y' || playAgain == 'y');

	return 0;
}
