#include "bellmanUpdate.h"

bellmanUpdate::bellmanUpdate()
{
	for (int k = 0; k < 20; k++)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == winRow && j == winCol)
					utilities[k][i][j] = 1;
				else if (i == loseRow && j == loseCol)
					utilities[k][i][j] = -1;
				else if ((i != wallRow || j != wallCol) && k == 0)
					utilities[k][i][j] = 0;
			}
		}
	}
	calculateUtilities();
}
void bellmanUpdate::calculateUtilities()
{
	double maxAction;
	for (int k = 1; k < 20; k++)
		for (int i = initialRow; i >= 0; i--)
			for (int j = initialCol; j < 4; j++)
			{
				if (i == winRow && j == winCol)
					utilities[k][i][j] = 1;
				else if (i == loseRow && j == loseCol)
					utilities[k][i][j] = -1;
				else if (i != wallRow || j != wallCol)
				{
					maxAction = max({ utilitiesOfGoingUp(i, j, k - 1), utilitiesOfGoingLeft(i, j, k - 1), utilitiesOfGoingDown(i, j, k - 1), utilitiesOfGoingRight(i, j, k - 1) });
					utilities[k][i][j] = reward + discountFactor * maxAction;
				}
			}
}
double bellmanUpdate::utilitiesOfGoingUp(int row, int col, int iterate)
{
	double utility = 0;
	if (isLegal(row - 1, col) == true)
		utility += probabilityUp * utilities[iterate][row - 1][col];
	else
		utility += probabilityUp * utilities[iterate][row][col];
	if (isLegal(row, col + 1) == true)
		utility += probabilityLeftRight * utilities[iterate][row][col + 1];
	else
		utility += probabilityLeftRight * utilities[iterate][row][col];
	if (isLegal(row, col - 1) == true)
		utility += probabilityLeftRight * utilities[iterate][row][col];
	else
		utility += probabilityLeftRight * utilities[iterate][row][col];
	return utility;
}
double bellmanUpdate::utilitiesOfGoingDown(int row, int col, int iterate)
{
	double utility = 0;
	if (isLegal(row + 1, col) == true)
		utility += (probabilityUp + probabilityLeftRight) * utilities[iterate][row + 1][col];
	else
		utility += (probabilityUp + probabilityLeftRight) * utilities[iterate][row][col];
	if (isLegal(row, col + 1) == true)
		utility += probabilityLeftRight * utilities[iterate][row][col + 1];
	else
		utility += probabilityLeftRight * utilities[iterate][row][col];
	return utility;
}
double bellmanUpdate::utilitiesOfGoingLeft(int row, int col, int iterate)
{
	double utility = 0;
	if (isLegal(row, col - 1) == true)
		utility += (probabilityUp + probabilityLeftRight) * utilities[iterate][row][col - 1];
	else
		utility += (probabilityUp + probabilityLeftRight) * utilities[iterate][row][col];
	if (isLegal(row - 1, col) == true)
		utility += probabilityLeftRight * utilities[iterate][row - 1][col];
	else
		utility += probabilityLeftRight * utilities[iterate][row][col];
	return utility;
}
double bellmanUpdate::utilitiesOfGoingRight(int row, int col, int iterate)
{
	double utility = 0;
	if (isLegal(row, col + 1) == true)
		utility += probabilityUp * utilities[iterate][row][col + 1];
	else
		utility += probabilityUp * utilities[iterate][row][col];
	if (isLegal(row - 1, col) == true)
		utility += probabilityLeftRight * utilities[iterate][row - 1][col];
	else
		utility += probabilityLeftRight * utilities[iterate][row][col];
	if (isLegal(row + 1, col) == true)
		utility += probabilityLeftRight * utilities[iterate][row + 1][col];
	else
		utility += probabilityLeftRight * utilities[iterate][row][col];
	return utility;
}
bool bellmanUpdate::isLegal(int row, int col)
{
	if (row < 0 || col < 0 || row >= 3 || col >= 4 || (row == wallRow && col == wallCol))
		return false;
	else
		return true;
}
void bellmanUpdate::printUtilities()
{
	for (int k = 0; k < 20; k++)
	{
		cout << k + 1 << " iteration" << endl;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
				cout << utilities[k][i][j] << " ";
			cout << endl;
		}
		cout << endl;
	}

}
