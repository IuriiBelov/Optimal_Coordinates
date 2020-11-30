#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>

#include "input.h"

#define ARRAY_SIZE 10
#define STRING_SIZE 100

Errors checkCommandLineArguments(int argc, char** argv) {
	if (argc != 3 || NULL == argv[0] || NULL == argv[1] || NULL == argv[2] || atoi(argv[2]) <= 0) {
		return INCORRECT_COMMAND_LINE_ARGUMENTS_ERROR;
	}
	return NO_ERRORS;
}

Errors reallocMemoryForTargets(Point** pTargets, int *pCurrentArraySize, int numOfTargets) {
	Point* temp;
	int i;

	*pCurrentArraySize += ARRAY_SIZE;
	temp = malloc((*pCurrentArraySize) * sizeof(Point));

	if (NULL == temp) {
		free(*pTargets);
		return NOT_ENOUGH_MEMORY_ERROR;
	}

	for (i = 0; i < numOfTargets - 1; ++i) {
		temp[i] = (*pTargets)[i];
	}
	free(*pTargets);
	*pTargets = temp;

	return NO_ERRORS;
}

Errors getCoordinate(char* str, int* pI, int indent, int* pC) {
	char str1[STRING_SIZE / 2];
	int flag = 0;

	while (isdigit(str[*pI])) {
		str1[*pI - indent] = str[*pI];
		++(*pI);
		flag = 1;
	}
	str1[*pI - indent] = '\0';

	if (flag == 0) {
		return INCORRECT_INPUT_DATA_ERROR;
	}
	
	*pC = atoi(str1);

	return NO_ERRORS;
}

Errors getCoordinates(char* str, int* pX, int* pY) {
	int i;
	
	i = 0;
	if (NO_ERRORS != getCoordinate(str, &i, 0, pX) || ',' != str[i]) {
		return INCORRECT_INPUT_DATA_ERROR;
	}
	++i;
	if (NO_ERRORS != getCoordinate(str, &i, i, pY) || str[i] != '\n' && str[i] != EOF && str[i] != '\0') {
		printf("%c\n", (int)(str[i]));
		return INCORRECT_INPUT_DATA_ERROR;
	}

	return NO_ERRORS;
}

Errors checkCoordinates(int x, int y, int x1, int x2, int y1, int y2) {
	if (x < x1 || x > x2 || y < y1 || y > y2) {
		return INCORRECT_INPUT_DATA_ERROR;
	}

	return NO_ERRORS;
}

void freeResources(Point** pTargets, FILE* fp) {
	free(*pTargets);
	fclose(fp);
}

Errors getInputData(char* filename, Point** pTargets, int* pNumOfTargets, int x1, int x2, int y1, int y2) {
	FILE* fp;
	char str[STRING_SIZE];
	int currentArraySize = ARRAY_SIZE;
	int x, y;
	Errors error;

	fp = fopen(filename, "r");
	if (NULL == fp) {
		return FILE_NOT_FOUND_ERROR;
	}
	
	*pTargets = malloc(currentArraySize * sizeof(Point));
	if (NULL == *pTargets) {
		fclose(fp);
		return NOT_ENOUGH_MEMORY_ERROR;
	}
	*pNumOfTargets = 0;

	while (NULL != fgets(str, STRING_SIZE, fp)) {
		++(*pNumOfTargets);

		if (*pNumOfTargets > currentArraySize) {
			error = reallocMemoryForTargets(pTargets, &currentArraySize, *pNumOfTargets);
			if (NO_ERRORS != error) {
				fclose(fp);
				return error;
			}
		}

		error = getCoordinates(str, &x, &y);
		if (NO_ERRORS != error) {
			freeResources(pTargets, fp);
			return error;
		}

		error = checkCoordinates(x, y, x1, x2, y1, y2);
		if (NO_ERRORS != error) {
			freeResources(pTargets, fp);
			return error;
		}
		
		(*pTargets)[*pNumOfTargets - 1].x = x;
		(*pTargets)[*pNumOfTargets - 1].y = y;
	}

	fclose(fp);

	return NO_ERRORS;
}