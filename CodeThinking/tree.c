#include<stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left_child;
    struct TreeNode *right_child;
}TreeNode;

typedef struct Tree {
    TreeNode *root;
    int size;
}Tree;

Tree *initTree() {
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->size = 0;
    tree->root = NULL;
    return tree;
}



//前序遍历
void preorderTraversal(TreeNode *root) {
    if (root == NULL) {
        return ;
    }
    printf("%d ", root->data);
    preorderTraversal(root->left_child);
    preorderTraversal(root->right_child);
}
//中序遍历
void inTraversal(TreeNode *root) {
    if (root == NULL) {
        return ;
    }
    inTraversal(root->left_child);
    printf("%d ", root->data);
    inTraversal(root->right_child);
}
//后序遍历
void postTraversal(TreeNode *root) {
    if (root == NULL) {
        return ;
    }
    postTraversal(root->left_child);
    postTraversal(root->right_child);
    printf("%d ", root->data);
}

TreeNode *createNode(int val) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->data = val;
    node->left_child = NULL;
    node->right_child = NULL;
    return node;
}

int main(){
    Tree * init_tree = initTree();
    TreeNode * tree_node1 = createNode(1);
    TreeNode * tree_node2 = createNode(2);
    TreeNode * tree_node3 = createNode(3);
    TreeNode * tree_node4 = createNode(4);
    TreeNode * tree_node5 = createNode(5);
    init_tree->root = tree_node1;
    tree_node1->left_child = tree_node2;
    tree_node1->right_child = tree_node3;
    tree_node2->left_child = tree_node4;
    tree_node3->right_child = tree_node5;

    printf("the preTraversal is:\n");
    preorderTraversal(init_tree->root);
    printf("\n");
    printf("the inTraversal is:\n");
    inTraversal(init_tree->root);
    printf("\n");
    printf("the postTraversal is:\n");
    postTraversal(init_tree->root);
    return 0;
}