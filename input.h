#pragma once

#include "errors.h"
#include "point.h"

Errors checkCommandLineArguments(int argc, char** argv);
Errors getInputData(char* filename, Point** pTargets, int* pNumOfTargets, int x1, int x2, int y1, int y2);