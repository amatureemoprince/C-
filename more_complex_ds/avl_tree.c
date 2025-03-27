#include "avl_tree.h"

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

void RR(AVL_TREE_NODE *root) {

}

void LR(AVL_TREE_NODE *root) {

}

void RL(AVL_TREE_NODE *root) {

}

int add(int first, int second){
    return first + second;
}