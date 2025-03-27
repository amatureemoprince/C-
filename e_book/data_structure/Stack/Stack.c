#define MAX_SIZE 10
#include <stdbool.h>
#include <stdlib.h>

typedef struct Stack {
  int arr[MAX_SIZE];
  int top;
}Stack;

Stack *init_stack() {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->top = -1;
  return stack;
}

void push(Stack *stack, int val) {
  if (stack->top == MAX_SIZE - 1) {
    return;
  }
  stack->arr[++stack->top] = val;
}

bool pop(Stack *stack, int *x) {
  if (stack->top == -1) {
    return false;
  }
  *(x) = stack->arr[stack->top--];
  return true;
}
int main(void){
  return 0;
}
