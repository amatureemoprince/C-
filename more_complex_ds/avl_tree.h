#ifndef AVL_TREE_H
#define AVL_TREE_H

//定义AVL节点
typedef struct AVL_TREE {
    int data;
    int height;
    struct AVL_TREE *left;
    struct AVL_TREE *right;
}AVL_TREE_NODE;
//定义右旋操作
void LL(AVL_TREE_NODE *root);
//定义左旋操作
void RR(AVL_TREE_NODE *root);
//定义左右旋操作
void LR(AVL_TREE_NODE *root);
//定义右左旋操作
void RL(AVL_TREE_NODE *root);
//初始化一颗AVL树
AVL_TREE_NODE *init_avl_tree();
//测试
int add(int first, int second);

#endif