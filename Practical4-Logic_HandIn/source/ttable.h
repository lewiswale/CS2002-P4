#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

void printTruthTable(int noOfIn, char *formula, int *values, int checkingEquality);
void printHeader(int n, char *formula);
void parseValues(stack *stackP, char *formula, int *values, int valueSize, int currentPos, int checkingEquality);
int getFormulaSize(char *formula);
void iterateFormula(stack *stackP, char *formula, int *values, int valueSize, int checkingEquality);
void parseChar(stack *stackP, char element, int *values);
int xorOperation(int o1, int o2);
int notOperation(int operand);
int andOperation(int o1, int o2);
int orOperation(int o1, int o2);
int equalOperation(int o1, int o2);
int implicationOperation(int o1, int o2);
void checkFormulaEquality(char *formula1, char *formula2, int *values, int noOfIn);
