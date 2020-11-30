#include <stdio.h>

#include "errors.h"

int handleErrors(Errors error) {
	switch (error) {
	case INCORRECT_COMMAND_LINE_ARGUMENTS_ERROR:
		printf("ERROR: incorrect command line arguments\n");
		break;
	case FILE_NOT_FOUND_ERROR:
		printf("ERROR: file not found\n");
		break;
	case INCORRECT_INPUT_DATA_ERROR:
		printf("ERROR: incorrect input data\n");
		break;
	case NOT_ENOUGH_MEMORY_ERROR:
		printf("ERROR: not enough memory\n");
	}
	printf("The program will be accidentally terminated\n");

	return 0;
}