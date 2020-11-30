#pragma once

#include "errors.h"
#include "point.h"

Errors allocMemoryForMatrix(int*** pMatrixOfCoordinates, int numOfRows, int numOfColumns);
void freeMemoryForMatrix(int*** pMatrixOfCoordinates, int numOfRows);