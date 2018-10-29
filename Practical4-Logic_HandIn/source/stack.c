// Implementation of a stack.
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
// Allocates memory for stack struct.
void makeStack(stack *stackP, int maxSize) {
  int *newContents;

  newContents = malloc(sizeof(int) * maxSize);

  if (newContents == NULL) {
    printf("%s\n", "Not enough memory to initialise stack.");
    exit(1);
  }

  stackP->contents = newContents;
  stackP->maxSize = maxSize;
  stackP->top = -1;
}
// Frees alloated memory from stack.
void destroyStack(stack *stackP) {
  free(stackP->contents);

  stackP->contents = NULL;
  stackP->maxSize = 0;
  stackP->top = -1;
}
// Detects if stack is empty.
int isEmpty(stack *stackP) {
  return stackP->top < 0;
}
// Detects if stack is full.
int isFull(stack *stackP) {
  return stackP->top >= stackP->maxSize - 1;
}
// Pushes given element onto stack.
void push(stack *stackP, int element) {
  if (isFull(stackP)) {
    printf("\n%s\n", "Formula is malformed.");
    exit(1);
  }

  stackP->contents[++stackP->top] = element;
}
// Returns top element of stack without removing it.
int top(stack *stackP) {
  if (isEmpty(stackP)) {
    printf("%s\n", "Stack is empty.");
  }

  return stackP->contents[stackP->top];
}
// Returns top elementof stack and then removes it.
int pop(stack *stackP) {
  if (isEmpty(stackP)) {
    printf("\n%s\n", "Formula is malformed.");
    exit(1);
  }

  return stackP->contents[stackP->top--];
}
