#include <stdio.h>
#include <stdlib.h>

typedef struct bst_tree_node {
    int data;
    struct bst_tree_node *left_child;
    struct bst_tree_node *right_child;
} BST_TREE_NODE;

// 创建节点
BST_TREE_NODE *create_bst_node(int val) {
    BST_TREE_NODE *node = (BST_TREE_NODE *)malloc(sizeof(BST_TREE_NODE));
    if (node == NULL) {
        return NULL;
    }
    node->data = val;
    node->left_child = NULL;
    node->right_child = NULL;
    return node;
}

// 查找节点（非递归实现）
BST_TREE_NODE *bst_search(BST_TREE_NODE *root, int val) {
    BST_TREE_NODE *current = root;
    while (current != NULL) {
        if (val < current->data) {
            current = current->left_child;
        } else if (val > current->data) {
            current = current->right_child;
        } else {
            return current;
        }
    }
    return NULL;
}

// 插入节点（优化版）
void insert_bst(BST_TREE_NODE **root, BST_TREE_NODE *node) {
    if (node == NULL) return;
    if (*root == NULL) {
        *root = node;
        return;
    }
    BST_TREE_NODE *current = *root;
    while (1) {
        if (node->data < current->data) {
            if (current->left_child == NULL) {
                current->left_child = node;
                break;
            }
            current = current->left_child;
        } else if (node->data > current->data) {
            if (current->right_child == NULL) {
                current->right_child = node;
                break;
            }
            current = current->right_child;
        } else {
            free(node);
            break;
        }
    }
}
//构造BST
void build_bst(BST_TREE_NODE **root, BST_TREE_NODE **nodes, int len) {
    *root = NULL;
    for (int i = 0; i < len; i++) {
        insert_bst(root, nodes[i]);
    }
}


// 释放BST（后序遍历）
void destroy_bst(BST_TREE_NODE *root) {
    if (root == NULL) return;
    destroy_bst(root->left_child);
    destroy_bst(root->right_child);
    free(root);
}

int main() {
    BST_TREE_NODE *root = NULL;

    // 测试插入
    insert_bst(&root, create_bst_node(4));
    insert_bst(&root, create_bst_node(5));
    insert_bst(&root, create_bst_node(3));
    insert_bst(&root, create_bst_node(2));
    insert_bst(&root, create_bst_node(6));

    // 测试查找
    int test_values[] = {3, 5, 1};
    for (int i = 0; i < 3; i++) {
        BST_TREE_NODE *found = bst_search(root, test_values[i]);
        if (found != NULL) {
            printf("Found: %d\n", found->data);
        } else {
            printf("%d not found\n", test_values[i]);
        }
    }

    destroy_bst(root);
    return 0;
}