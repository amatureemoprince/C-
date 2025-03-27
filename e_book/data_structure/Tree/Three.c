#include <stdio.h>
#include <stdlib.h>

/**
 * 声明树的结点
 */
typedef struct Three {
  int val;
  int height;
  struct Three *left;
  struct Three *right;
}Three;

/**
 * 初始化
 * @return 树的根节点
 */
Three *init(const int val) {
  Three *three = (Three *)malloc(sizeof(Three));
  if (three == NULL) {
    fprintf(stderr, "three memory allocation fails");
    return NULL;
  }
  three->val = val;
  three->height = 0;
  three->left = NULL;
  three->right = NULL;
  return three;
}


int main(void){
  Three *three = init(5);
  free(three);
  return 0;
}
