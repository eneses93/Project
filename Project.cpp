/*Nikola Slavov, 9/7/2015
This program will create a random 9x9 sudoku puzzle with only one possible solution.*/

//Including needed libraries:
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>

//Using the standart namespace:
using namespace std;

//Constants:
const int GRIDSIZE = 9;

//Each instance of the class represents a box in the puzzle:
class Box
{
public:
	vector<int> vecFailed;
	int varValue;
};

//Function prototypes:
void funPrint(const vector<Box> &vecBoxes);
void funUnitCheck(const vector<Box> &vecBoxes, int p, bool &c);
void funRowCheck(const vector<Box> &vecBoxes, int p, bool &c);
void funColumnCheck(const vector<Box> &vecBoxes, int p, bool &c);
void funAssign(Box &b);
void funCreate(vector <Box> &vecBoxes);
bool funCanBeSolved(const vector <Box> &vecBoxes);
void funDisSolve(vector <Box> &vecBoxes);

//Main function:
int main()
{
	int choice = 0;
	vector <Box> vecBoxes(GRIDSIZE*GRIDSIZE);
	srand(time(NULL));

	funCreate(vecBoxes);
	vector <Box> vecSolution = vecBoxes;

	funDisSolve(vecBoxes);

	cout << "Your puzzle is:" << endl;
	funPrint(vecBoxes);

	cout << "Enter 0 to exit or 1 to see the solution before you exit: ";
	cin >> choice;
	switch (choice)
	{
	case 0:
		break;
	case 1:
		cout << "The solution is: " << endl;
		funPrint(vecSolution);
	default:
		break;
	}

	system("pause");
	return 0;
}

//This function prints the contents of a Box vector in a sudoku-like format.
void funPrint(const vector<Box> &vecBoxes)
{
	for (int counter1 = 0; counter1 < GRIDSIZE; counter1++)
	{
		for (int counter2 = 0; counter2 < GRIDSIZE; counter2++)
		{
			if (counter2 != 3 && counter2 != 6)
				cout << setw(3) << vecBoxes[counter2 + GRIDSIZE*counter1].varValue;
			else
				cout << setw(4) << vecBoxes[counter2 + GRIDSIZE*counter1].varValue;
		}
		if (counter1 == 2 || counter1 == 5)
		{
			cout << endl;
		}
		cout << endl;
	}
}

//This function checks if a particular element in the passed vector
//is equal to elements that are in its unit, but not in its row or column.
void funUnitCheck(const vector<Box> &vecBoxes, int p, bool &c)
{
	//There are 9 positions in a unit where the current box may be, this tree of ifs finds which one we are at and acts accordingly
	//If it's in row 1, 4, or 7
	if (p / 9 == 0 || p / 9 == 3 || p / 9 == 6)
	{
		//If it's in column 1, 4, or 7(Top left)
		if (p % 9 == 0 || p % 9 == 3 || p % 9 == 6)
		{
			//Check these boxes, realtive to the current one:
			if (vecBoxes[p].varValue == vecBoxes[p + 10].varValue ||
				vecBoxes[p].varValue == vecBoxes[p + 11].varValue ||
				vecBoxes[p].varValue == vecBoxes[p + 19].varValue ||
				vecBoxes[p].varValue == vecBoxes[p + 20].varValue)
				c = 0;
		}
		//If it's in column 2, 5, or 8(Top center)
		else if (p % 9 == 1 || p % 9 == 4 || p % 9 == 7)
		{
			//Check these boxes, realtive to the current one:
			if (vecBoxes[p].varValue == vecBoxes[p + 8].varValue ||
				vecBoxes[p].varValue == vecBoxes[p + 10].varValue ||
				vecBoxes[p].varValue == vecBoxes[p + 17].varValue ||
				vecBoxes[p].varValue == vecBoxes[p + 19].varValue)
				c = 0;
		}
		//If it's in column 3, 6, or 9(Top right)
		else if (p % 9 == 2 || p % 9 == 5 || p % 9 == 8)
		{
			//Check these boxes, realtive to the current one:
			if (vecBoxes[p].varValue == vecBoxes[p + 7].varValue ||
				vecBoxes[p].varValue == vecBoxes[p + 8].varValue ||
				vecBoxes[p].varValue == vecBoxes[p + 16].varValue ||
				vecBoxes[p].varValue == vecBoxes[p + 17].varValue)
				c = 0;
		}
	}
	//If it's in row 2, 5, or 8
	else if (p / 9 == 1 || p / 9 == 4 || p / 9 == 7)
	{
		//If it's in column 1, 4, or 7(Middle left)
		if (p % 9 == 0 || p % 9 == 3 || p % 9 == 6)
		{
			//Check these boxes, realtive to the current one:
			if (vecBoxes[p].varValue == vecBoxes[p - 8].varValue ||
				vecBoxes[p].varValue == vecBoxes[p - 7].varValue ||
				vecBoxes[p].varValue == vecBoxes[p + 10].varValue ||
				vecBoxes[p].varValue == vecBoxes[p + 11].varValue)
				c = 0;
		}
		//If it's in column 2, 5, or 8(Middle center)
		else if (p % 9 == 1 || p % 9 == 4 || p % 9 == 7)
		{
			//Check these boxes, realtive to the current one:
			if (vecBoxes[p].varValue == vecBoxes[p - 10].varValue ||
				vecBoxes[p].varValue == vecBoxes[p - 8].varValue ||
				vecBoxes[p].varValue == vecBoxes[p + 8].varValue ||
				vecBoxes[p].varValue == vecBoxes[p + 10].varValue)
				c = 0;
		}
		//If it's in column 3, 6, or 9(Middle right)
		else if (p % 9 == 2 || p % 9 == 5 || p % 9 == 8)
		{
			//Check these boxes, realtive to the current one:
			if (vecBoxes[p].varValue == vecBoxes[p - 11].varValue ||
				vecBoxes[p].varValue == vecBoxes[p - 10].varValue ||
				vecBoxes[p].varValue == vecBoxes[p + 7].varValue ||
				vecBoxes[p].varValue == vecBoxes[p + 8].varValue)
				c = 0;
		}
	}
	//If it's in row 3, 6, or 9
	else if (p / 9 == 2 || p / 9 == 5 || p / 9 == 8)
	{
		//If it's in column 1, 4, or 7(Bottom left)
		if (p % 9 == 0 || p % 9 == 3 || p % 9 == 6)
		{
			//Check these boxes, realtive to the current one:
			if (vecBoxes[p].varValue == vecBoxes[p - 17].varValue ||
				vecBoxes[p].varValue == vecBoxes[p - 16].varValue ||
				vecBoxes[p].varValue == vecBoxes[p - 8].varValue ||
				vecBoxes[p].varValue == vecBoxes[p - 7].varValue)
				c = 0;
		}
		//If it's in column 2, 5, or 8(Bottom center)
		else if (p % 9 == 1 || p % 9 == 4 || p % 9 == 7)
		{
			//Check these boxes, realtive to the current one:
			if (vecBoxes[p].varValue == vecBoxes[p - 19].varValue ||
				vecBoxes[p].varValue == vecBoxes[p - 17].varValue ||
				vecBoxes[p].varValue == vecBoxes[p - 10].varValue ||
				vecBoxes[p].varValue == vecBoxes[p - 8].varValue)
				c = 0;
		}
		//If it's in column 3, 6, or 9(Bottom right)
		else if (p % 9 == 2 || p % 9 == 5 || p % 9 == 8)
		{
			//Check these boxes, realtive to the current one:
			if (vecBoxes[p].varValue == vecBoxes[p - 20].varValue ||
				vecBoxes[p].varValue == vecBoxes[p - 19].varValue ||
				vecBoxes[p].varValue == vecBoxes[p - 11].varValue ||
				vecBoxes[p].varValue == vecBoxes[p - 10].varValue)
				c = 0;
		}
	}
}

//This function checks if a particular element in the passed vector
//is equal to elements that are in its row.
void funRowCheck(const vector<Box> &vecBoxes, int p, bool &c)
{
	//The counter is the column we're looking at
	for (int counter = 0; counter < 9; counter++)
	{
		//If we're not looking at the column of the given element
		if (counter != p % 9)
		{
			//Check if the element in the same row as the given element has the same value
			if (vecBoxes[(p / 9) * 9 + counter].varValue == vecBoxes[p].varValue)
			{
				c = 0;
				break;
			}
		}
	}
}

//This function checks if a particular element in the passed vector
//is equal to elements that are in its column.
void funColumnCheck(const vector<Box> &vecBoxes, int p, bool &c)
{
	//The counter is the row we're looking at
	for (int counter = 0; counter < 9; counter++)
	{
		//If we're not looking at the row of the given element
		if (counter != p / 9)
		{
			//Check if the element in the same column as the given element has the same value
			if (vecBoxes[(p % 9) + counter * 9].varValue == vecBoxes[p].varValue)
			{
				c = 0;
				break;
			}
		}
	}
}

//This function assigns a random number to the given position in the vector
//and makes sure the value is not one that has failed before.
void funAssign(Box &b)
{
	bool varOk = 1;
	do
	{
		varOk = 1;
		b.varValue = rand() % 9 + 1;
		for (unsigned int counter = 0; counter < b.vecFailed.size(); counter++)
		{
			if (b.varValue == b.vecFailed[counter])
			{
				varOk = 0;
				break;
			}
		}
	} while (!varOk);
}

//Assigns values to the members of the vector, which don't conflict with Sudoku rules.
void funCreate(vector <Box> &vecBoxes)
{
	bool varValid = 0;
	for (int counter = 0; counter < (GRIDSIZE*GRIDSIZE); counter++)
	{
		//Keeps reassigning a random value to the current box until it does not conflict with the rules:
		do
		{
			//If all nine values have failed for this box, it should go to the previous box
			if (vecBoxes[counter].vecFailed.size() == 9)
			{
				vecBoxes[counter].vecFailed.clear();
				vecBoxes[counter].varValue = 0;
				counter = counter - 1;
				vecBoxes[counter].vecFailed.push_back(vecBoxes[counter].varValue);
				varValid = 0;
				continue;
			}
			funAssign(vecBoxes[counter]);
			varValid = 1;
			funRowCheck(vecBoxes, counter, varValid);
			if (varValid)
				funColumnCheck(vecBoxes, counter, varValid);
			if (varValid)
				funUnitCheck(vecBoxes, counter, varValid);
			if (!varValid)
				vecBoxes[counter].vecFailed.push_back(vecBoxes[counter].varValue);
		} while (!varValid);
	}
	for (int counter = 0; counter < (GRIDSIZE*GRIDSIZE); counter++)
	{
		vecBoxes[counter].vecFailed.clear();
	}
}

//Checks if a given unsolved puzzle actually has a solution.
bool funCanBeSolved(const vector <Box> &vecEmpty)
{
	bool varValid = 0;
	vector <Box> vecTemp = vecEmpty;

	//If a box is initially empty, put a zero in its vecFailed
	for (int counter = 0; counter < 81; counter++)
		if (vecTemp[counter].varValue == 0)
			vecTemp[counter].vecFailed.push_back(0);
		else
			vecTemp[counter].vecFailed.clear();

	for (int counter = 0; counter < (GRIDSIZE*GRIDSIZE); counter++)
	{
		if (vecTemp[counter].vecFailed.size() != 0)
		{
			//Keeps reassigning a random value to the current box until it does not conflict with the rules:
			do
			{
				//If all nine values have failed for this box, it should go to the previous box
				if (vecTemp[counter].vecFailed.size() == 10)
				{
					vecTemp[counter].vecFailed.clear();
					vecTemp[counter].vecFailed.push_back(0);
					vecTemp[counter].varValue = 0;
					do
					{
						counter = counter - 1;
						if (counter == -1)
						{
							for (int counter2 = 0; counter2 < (GRIDSIZE*GRIDSIZE); counter2++)
							{
								vecTemp[counter2].vecFailed.clear();
							}

							return 0;
						}
					} while (vecTemp[counter].vecFailed.size() == 0);
					vecTemp[counter].vecFailed.push_back(vecTemp[counter].varValue);
					varValid = 0;
					continue;
				}
				funAssign(vecTemp[counter]);
				varValid = 1;
				funRowCheck(vecTemp, counter, varValid);
				if (varValid)
				{
					funColumnCheck(vecTemp, counter, varValid);
				}
				if (varValid)
				{
					funUnitCheck(vecTemp, counter, varValid);
				}
				if (!varValid)
					vecTemp[counter].vecFailed.push_back(vecTemp[counter].varValue);
			} while (!varValid);
		}
	}
	return 1;
}

//Takes a solved puzzle and randomly empties boxes in it, while making sure it still has only one possible solution.
void funDisSolve(vector <Box> &vecBoxes)
{
	bool varValid = 0;
	int varRandom = rand() % 9 + 1;

	//These two vectors will hold the locations of boxes which are emptied and boxes for which it has been determined that they can't change.
	vector <int> vecEmpties;
	vector <int> vecStatics;

	int varLocation = 0;
	int varTempValue = 0;
	unsigned int counter = 0;

	varLocation = rand() % 80 + 0;
	vecBoxes[varLocation].varValue = 0;
	vecEmpties.push_back(varLocation);
	do
		varLocation = rand() % 80 + 0;
	while (varLocation == vecEmpties[0]);
	vecStatics.push_back(varLocation);

	//For speed, it should stop when about half the cells are empty.
	while (vecEmpties.size() < (40 + varRandom))
	{
		varLocation = rand() % 81 + 0;
		for (counter = 0; counter < vecEmpties.size(); counter++)
		{
			if (vecEmpties[counter] == varLocation)
			{
				counter++;
				break;
			}
		}
		counter--;
		if (vecEmpties[counter] == varLocation)
			continue;

		for (counter = 0; counter < vecStatics.size(); counter++)
		{
			if (vecStatics[counter] == varLocation)
			{
				counter++;
				break;
			}
		}
		counter--;
		if (vecStatics[counter] == varLocation)
			continue;

		varTempValue = vecBoxes[varLocation].varValue;
		for (counter = 1; counter < 10; counter++)
			if (counter != varTempValue)
			{
				vecBoxes[varLocation].varValue = counter;
				varValid = 1;
				funRowCheck(vecBoxes, varLocation, varValid);
				if (varValid)
					funColumnCheck(vecBoxes, varLocation, varValid);
				if (varValid)
					funUnitCheck(vecBoxes, varLocation, varValid);
				if (varValid && funCanBeSolved(vecBoxes))
				{
					vecBoxes[varLocation].varValue = varTempValue;
					break;
				}
			}
		if (vecBoxes[varLocation].varValue == varTempValue)
		{
			vecStatics.push_back(varLocation);
		}
		else
		{
			vecBoxes[varLocation].varValue = 0;
			vecEmpties.push_back(varLocation);
		}
	}
}
