#ifndef bellmanUpdate_H
#define bellmanUpdate_H
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<algorithm>
using namespace std;
class bellmanUpdate
{
public:
	bellmanUpdate();
	double utilitiesOfGoingUp(int, int, int);
	double utilitiesOfGoingDown(int, int, int);
	double utilitiesOfGoingLeft(int, int, int);
	double utilitiesOfGoingRight(int, int, int);
	void calculateUtilities();
	bool isLegal(int, int);
	void printUtilities();
private:
	double utilities[20][3][4];
	int initialRow = 2;
	int initialCol = 0;
	int winRow = 0;
	int winCol = 3;
	int loseRow = 1;
	int loseCol = 3;
	int wallRow = 1;
	int wallCol = 1;
	double reward = -0.04;
	double probabilityUp = 0.8;
	double probabilityLeftRight = 0.1;
	int discountFactor = 1;
};
#endif
