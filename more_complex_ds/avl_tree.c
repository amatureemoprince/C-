#include <stdio.h>
#include <stdlib.h>
//定义AVL节点
typedef struct AVL_TREE {
    int key;
    int high;
    struct AVL_TREE *left;
    struct AVL_TREE *right;
}AVL_TREE_NODE;

//初始化一个虚拟空节点NIL
AVL_TREE_NODE __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    printf("init the NIL node!");
    NIL->key = -1;
    NIL->high = 0;
    NIL->left = NIL->right = NIL;
    return ;
}

//初始化节点
AVL_TREE_NODE *init_avl_tree(){
    AVL_TREE_NODE *avl_tree = (AVL_TREE_NODE *)malloc(sizeof(AVL_TREE_NODE));
    avl_tree->high = 0;
    return avl_tree;
}

AVL_TREE_NODE *new_avl_tree_node(int key) {
    AVL_TREE_NODE *avl_tree_node = (AVL_TREE_NODE *)malloc(sizeof(AVL_TREE_NODE));
    avl_tree_node->key = key;
    avl_tree_node->left = avl_tree_node->right = NULL;
    return avl_tree_node;
}

//定义右旋操作
void LL(AVL_TREE_NODE *root) {
    if (!root) {
        return ;
    }
    //右旋操作
    //传入的root，将new_root替代root，new_root->right替代root->left，root替代new_root->right则可
    AVL_TREE_NODE *new_root = root->left;
    AVL_TREE_NODE *temp;
    temp = new_root->right;
    new_root->right = root;
}
//定义左旋操作
void RR(AVL_TREE_NODE *root) {

}
//定义左右旋操作
void LR(AVL_TREE_NODE *root) {

}
//定义右左旋操作
void RL(AVL_TREE_NODE *root) {

}
//销毁操作
void destroy_avl_tree(AVL_TREE_NODE *root) {
    if (root == NIL) {
        return;
    }
    free(root->left);
    free(root->right);
}

int main(){
  return 0;
}