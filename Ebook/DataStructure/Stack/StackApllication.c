#define MAX_SIZE 10
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
  char chars[MAX_SIZE];
  int top;
}Stack;

//栈在括号匹配中的应用
bool isBracket(Stack *stack, const char *chars) {
  if (stack == NULL || chars == NULL) {
    return false;
  }
  for (int i = 0; chars[i] != '\0'; i++ ) {
    if (chars[i] == '(' || chars[i] == '[' || chars[i] == '{') {
      stack->chars[++stack->top] = chars[i];
      continue;
    }
    //拿到栈顶的元素
    const char compare = stack->chars[stack->top];
    //比较是否为正确的
    if (chars[i] == ')' && compare == '(' || chars[i] == ']' && compare == '[' || chars[i] == '}' && compare == '{') {
      stack->top--;
    }else {
      return false;
    }
  }
  return true;
}
int main(void){
  printf("Please input some brackets: ");

  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->top = -1;

  scanf("%s", stack->chars);

  if (isBracket(stack, stack->chars)) {
    printf("Brackets are matched.\n");
  } else {
    printf("Brackets are not matched.\n");
  }

  free(stack);
  return 0;
}
