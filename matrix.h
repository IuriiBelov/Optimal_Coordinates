#pragma once

#include "point.h"

void initializeMatrix(int** matrixOfCoordinates, int numOfRows, int numOfColumns, Point* targets, 
	int numOfTargets);
void findOptimalRowAndColumn(int** matrixOfCoordinates, int numOfRows, int numOfColumns, int radius,
	int* pOptimalRow, int* pOptimalColumn, int* pNumOfHitTargets);