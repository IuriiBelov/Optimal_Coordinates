#include <stdio.h>
#include <malloc.h>

#include "matrix_memory.h"

Errors allocMemoryForMatrix(int*** pMatrixOfCoordinates, int numOfRows, int numOfColumns) {
	int i, j;

	*pMatrixOfCoordinates = malloc(numOfRows * sizeof(int*));
	if (NULL == *pMatrixOfCoordinates) {
		return NOT_ENOUGH_MEMORY_ERROR;
	}

	for (i = 0; i < numOfRows; ++i) {
		(*pMatrixOfCoordinates)[i] = malloc(numOfColumns * sizeof(int));

		if (NULL == (*pMatrixOfCoordinates)[i]) {
			for (j = 0; j < i; ++j) {
				free((*pMatrixOfCoordinates)[j]);
			}
			free(*pMatrixOfCoordinates);

			*pMatrixOfCoordinates = NULL;

			return NOT_ENOUGH_MEMORY_ERROR;
		}
	}

	return NO_ERRORS;
}

void freeMemoryForMatrix(int*** pMatrixOfCoordinates, int numOfRows) {
	int i;

	for (i = 0; i < numOfRows; ++i) {
		free((*pMatrixOfCoordinates)[i]);
	}
	free(*pMatrixOfCoordinates);

	*pMatrixOfCoordinates = NULL;
}