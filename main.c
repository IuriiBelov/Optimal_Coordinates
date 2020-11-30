#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "point.h"
#include "input.h"
#include "matrix_memory.h"
#include "matrix.h"

#define X1 0
#define Y1 0
#define X2 100
#define Y2 100

void convertTargetsCoordinates(Point* targets, int numOfTargets, int x1, int y1);
void calculateOptimalCoordinates(int* pOptimalX, int* pOptimalY, int optimalRow, int optimalColumn, int x1,
	int y1);
void printResults(int optimalX, int optimalY, int numOfHitTargets);

int main(int argc, char** argv) {
	Point* targets;
	int numOfTargets;
	int** matrixOfCoordinates;
	int optimalRow, optimalColumn;
	int numOfHitTargets;
	int optimalX, optimalY;
	Errors error;
	
	error = checkCommandLineArguments(argc, argv);
	if (NO_ERRORS != error) {
		return handleErrors(error);
	}
	
	error = getInputData(argv[1], &targets, &numOfTargets, X1, X2, Y1, Y2);
	if (NO_ERRORS != error) {
		return handleErrors(error);
	}
	
	error = allocMemoryForMatrix(&matrixOfCoordinates, (Y2 - Y1), (X2 - X1));
	if (NO_ERRORS != error) {
		return handleErrors(error);
	}
	
	convertTargetsCoordinates(targets, numOfTargets, X1, Y1);
	initializeMatrix(matrixOfCoordinates, (Y2 - Y1), (X2 - X1), targets, numOfTargets);
	
	findOptimalRowAndColumn(matrixOfCoordinates, (Y2 - Y1), (X2 - X1), atoi(argv[2]), &optimalRow, &optimalColumn,
		&numOfHitTargets);
	calculateOptimalCoordinates(&optimalX, &optimalY, optimalRow, optimalColumn, X1, Y1);

	printResults(optimalX, optimalY, numOfHitTargets);
	
	freeMemoryForMatrix(&matrixOfCoordinates, (Y2 - Y1));
	
	return 0;
}

void convertTargetsCoordinates(Point* targets, int numOfTargets, int x1, int y1) {
	int i;

	for (i = 0; i < numOfTargets; ++i) {
		(targets[i]).x -= x1;
		(targets[i]).y -= y1;
	}
}

void calculateOptimalCoordinates(int* pOptimalX, int* pOptimalY, int optimalRow, int optimalColumn, int x1,
	int y1) {
	
	*pOptimalX = optimalColumn + x1;
	*pOptimalY = optimalRow + y1;
}

void printResults(int optimalX, int optimalY, int numOfHitTargets) {
	printf("Optimal coordinates:\n");
	printf("x: %d\n", optimalX);
	printf("y: %d\n", optimalY);
	printf("Number of hit targets: %d\n", numOfHitTargets);
}