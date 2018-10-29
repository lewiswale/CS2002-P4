#include "ttable.h"

// Prints corrctly formatted truth table of a given formula.
void printTruthTable(int noOfIn, char *formula, int *values, int checkingEquality) {
  printf("\n");
  printHeader(noOfIn, formula);
  stack formulaStack;
  makeStack(&formulaStack, getFormulaSize(formula));
  parseValues(&formulaStack, formula, values, noOfIn, 0, checkingEquality);
  destroyStack(&formulaStack);
}
// Prints correctly formatted table header.
void printHeader(int n, char *formula) {
  char letter = 'a';
  for (size_t i = 0; i < n; i++) {
    printf("%c ", letter);
    letter++;
  }
  int result_spacing = 11;
  printf(": %s : Result\n", formula);
  for (size_t i = 0; i < n*2 + getFormulaSize(formula) + result_spacing; i++) {
    printf("%s", "=");
  }
  printf("\n");
}
