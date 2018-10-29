// Main class used for parsing boolean formulae and printing truth tables.
#include "ttable.h"
// Main method, inspecting argument amounts and passing relevant infromation
// into parsing algorithms.
int main(int argc, char *argv[]) {
  if (argc > 4) {
    printf("%s\n", "Too many arguments given!");
    exit(1);
  } else if (argc < 3) {
    printf("%s\n", "Too few arguments given!");
    exit(1);
  }

  long int noOfIn = strtol(argv[1], NULL, 10);
  if (noOfIn > 26) {
    printf("%s\n", "Too many varibales. Must be between 'a' and 'z'.");
    exit(1);
  } else if (noOfIn == 0) {
    printf("%s\n", "An integer must be given stating how many variables are to be used.");
    exit(1);
  }

  char *formula1 = argv[2];
  char *formula2;

  int values[noOfIn];
  int *valueP = values;
  for (size_t i = 0; i < noOfIn; i++) {
    values[i] = 0;
  }

  printTruthTable(noOfIn, formula1, valueP, 0);

  if (argc == 4) {
    formula2 = argv[3];
    printTruthTable(noOfIn, formula2, valueP, 0);
    checkFormulaEquality(formula1, formula2, valueP, noOfIn);
  }

}

// Recursive function used to parse each possible iteration of the formula.
void parseValues(stack *stackP, char *formula, int *values, int valueSize, int currentPos, int checkingEquality) {
  if (currentPos == valueSize - 1) {
    values[currentPos] = 0;
    iterateFormula(stackP, formula, values, valueSize, checkingEquality);
    values[currentPos] = 1;
    iterateFormula(stackP, formula, values, valueSize, checkingEquality);
  } else {
    values[currentPos] = 0;
    parseValues(stackP, formula, values, valueSize, currentPos+1, checkingEquality);
    values[currentPos] = 1;
    parseValues(stackP, formula, values, valueSize, currentPos+1, checkingEquality);
  }
}
// Function used to return the length of a formula.
int getFormulaSize(char *formula) {
  int i = 0;
  char currentChar = formula[i];
  while (!currentChar == '\0') {
    currentChar = formula[++i];
  }
  return i;
}
// Inspects a particular formula, parsing each character.
void iterateFormula(stack *stackP, char *formula, int *values, int valueSize, int checkingEquality) {
  for (size_t n = 0; n < valueSize; n++) {
    printf("%d ", values[n]);
  }
  printf(": ");

  int i = 0;
  char currentChar = formula[i];
  while (!currentChar == '\0') {
    parseChar(stackP, currentChar, values);
    currentChar = formula[++i];
  }
  int result = pop(stackP);
  printf(" : %3d\n", result);
  if (checkingEquality && !result) {
    printf("\n%s\n", "Inequality detected.");
    exit(1);
  }
}
// Performs relevent operation based on the current character being inpsected.
void parseChar(stack *stackP, char element, int *values) {
  switch (element) {
    case ' ': printf(" "); break;
    case '-': push(stackP, notOperation(pop(stackP)));
      printf("%d", top(stackP));
      break;
    case '#': push(stackP, xorOperation(pop(stackP), pop(stackP)));
      printf("%d", top(stackP));
      break;
    case '&': push(stackP, andOperation(pop(stackP), pop(stackP)));
      printf("%d", top(stackP));
      break;
    case '|': push(stackP, orOperation(pop(stackP), pop(stackP)));
      printf("%d", top(stackP));
      break;
    case '=': push(stackP, equalOperation(pop(stackP), pop(stackP)));
      printf("%d", top(stackP));
      break;
    case '>': push(stackP, implicationOperation(pop(stackP), pop(stackP)));
      printf("%d", top(stackP));
      break;
    case '0': push(stackP, 0);
      printf(" ");
      break;
    case '1': push(stackP, 1);
      printf(" ");
      break;
    case 'a'...'z' : push(stackP, values[element - 'a']);
      printf(" ");
      break;
    default : printf("\n%s\n",  "Invalid character within formula.");
      exit(1);
  }
}
// All logical operations.
int xorOperation(int o1, int o2) {
  return ((o1 && !o2) || (!o1 && o2));
}

int notOperation(int operand) {
  return !operand;
}

int andOperation(int o1, int o2) {
  return o1 && o2;
}

int orOperation(int o1, int o2) {
  return o1 || o2;
}

int equalOperation(int o1, int o2) {
  return o1 == o2;
}

int implicationOperation(int o1, int o2) {
  return (!o1) || o2;
}
// Checks equality of two formulae.
void checkFormulaEquality(char *formula1, char *formula2, int *values, int noOfIn) {
  printf("\n%s\n", "Checking equality of formulae...");
  char equalityFormula[2001];
  strcpy(equalityFormula, formula1);
  strcat(equalityFormula, formula2);
  strcat(equalityFormula, "=");
  printTruthTable(noOfIn, equalityFormula, values, 1);
  printf("\n%s\n", "Formulae are equal.");
}
