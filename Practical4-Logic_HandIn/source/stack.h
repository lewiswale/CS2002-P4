typedef struct stack {
  int *contents;
  int top;
  int maxSize;
} stack;

void makeStack(stack *stackP, int maxSize);
void destroyStack(stack *stackP);
int isFull(stack *stackP);
int isEmpty(stack *stackP);
void push(stack *stackP, int element);
int pop(stack *stackP);
int top(stack *stackP);
