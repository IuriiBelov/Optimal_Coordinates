#include <stdio.h>
#include <math.h>

#include "matrix.h"

void initializeMatrix(int** matrixOfCoordinates, int numOfRows, int numOfColumns, Point* targets, 
	int numOfTargets) {

	int i, j;

	for (i = 0; i < numOfRows; ++i) {
		for (j = 0; j < numOfColumns; ++j) {
			matrixOfCoordinates[i][j] = 0;
		}
	}

	for (i = 0; i < numOfTargets; ++i) {
		matrixOfCoordinates[(targets[i]).y][(targets[i]).x] = 1;
	}
}

int max(int x, int y) {
	return (x > y ? x : y);
}

int min(int x, int y) {
	return (x < y ? x : y);
}

void findOptimalRowAndColumn(int** matrixOfCoordinates, int numOfRows, int numOfColumns, int radius,
	int* pOptimalRow, int* pOptimalColumn, int* pNumOfHitTargets) {

	int i, j;
	int a, b;
	int currentNumOfHitTargets;

	*pNumOfHitTargets = 0;
	*pOptimalRow = 0;
	*pOptimalColumn = 0;
	for (i = 0; i < numOfRows; ++i) {
		for (j = 0; j < numOfColumns; ++j) {
			currentNumOfHitTargets = 0;
			
			for (a = max(i - radius, 0); a <= min(i + radius, numOfRows - 1); ++a) {
				for (b = max(j - radius, 0); b <= min(j + radius, numOfColumns - 1); ++b) {
					if (sqrt(pow((i - a), 2) + pow((j - b), 2)) <= radius) {
						currentNumOfHitTargets += matrixOfCoordinates[a][b];
					}
				}
			}

			if (currentNumOfHitTargets > *pNumOfHitTargets) {
				*pNumOfHitTargets = currentNumOfHitTargets;
				*pOptimalRow = i;
				*pOptimalColumn = j;
			}
		}
	}
}