#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 100

typedef struct TreeNode {
    int data;
    struct TreeNode *left_child;
    struct TreeNode *right_child;
}TreeNode;

typedef struct Tree {
    TreeNode *root;
    int size;
}Tree;

typedef struct Stack {
    TreeNode *data[MAX_STACK];
    int top;
}Stack;

Stack *initStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

void push(Stack *stack, TreeNode *node) {
    if (stack == NULL) {
        return ;
    }
    if (stack->top == MAX_STACK - 1) {
        return ;
    }
    stack->data[++stack->top] = node;
}
//返回栈顶元素，并将栈的长度减一
TreeNode *pop(Stack *stack) {
    if (stack == NULL) {
        return NULL;
    }
    if (stack->top < 0) {
        return NULL;
    }
    return stack->data[stack->top--];
}

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
//迭代遍历二叉树
TreeNode **preBinary(TreeNode *root, int *returnSize) {
    if (root == NULL) {
        return NULL;
    }

    int index = 0;
    TreeNode *p = root;
    TreeNode **result = (TreeNode *)malloc(sizeof(TreeNode *) * MAX_STACK);
    Stack * stack = initStack();
    push(stack, p);

    //只要栈不为空
    while (stack->top != -1) {
        TreeNode * node = pop(stack);
        result[index++] = node;
        if (node->right_child) {
            push(stack, node->right_child);
        }

        if (node->left_child) {
            push(stack, node->left_child);
        }
    }

    *returnSize = index;
    return result;
}
//迭代中序遍历
TreeNode **inBinary(TreeNode *root, int *returnSize) {
    if (root == NULL) {
        return ;
    }
    Stack * stack = initStack();
    TreeNode **result = (TreeNode **)malloc(sizeof(TreeNode *) * MAX_STACK);
    int index = 0;

    TreeNode *cur = root;
    while (cur != NULL || stack->top != -1) {
        //遍历到最后一个左孩子节点
        if (cur) {
            push(stack, cur);
            cur = cur->left_child;
        }else {
            //处理栈中的节点
            cur = pop(stack);
            result[index++] = cur;
            cur = cur->right_child;
        }

    }

    *returnSize = index;
    return result;
}

void reveser(TreeNode **result, int index) {
    int loop = index / 2;
    TreeNode *temp;
    for (int i = 0; i < loop; i++) {
        temp = result[i];
        result[i] = result[index - 1 - i];
        result[index - 1 - i] = temp;
    }
}
//后序遍历迭代遍历
TreeNode **postBinary(TreeNode *root, int *len) {
    if (root == NULL) {
        return NULL;
    }
    Stack *stack = initStack();
    int index = 0;
    TreeNode **result = (TreeNode **)malloc(MAX_STACK * sizeof(TreeNode *));
    TreeNode *cur = root;

    push(stack, cur);
    while (stack->top != -1) {
        cur = pop(stack);
        result[index++] = cur;
        if (cur->left_child) {
            push(stack, cur->left_child);
        }
        if (cur->right_child) {
            push(stack, cur->right_child);
        }
    }
    reveser(result, index);
    *len = index;
    return result;

}

void coutStack(Stack *stack) {
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

//测试
void coutZ(TreeNode *node, TreeNode *other) {
    printf("input node address is %0x\n", node);
    node = other;
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
    printf("\n");

    int len;
    TreeNode ** pre_binary = preBinary(init_tree->root, &len);
    printf("the diedai pre traversal is:\n");
    for (int i = 0; i < len; i++) {
        printf("%d ", pre_binary[i]->data);
    }
    printf("\n");
    printf("the diedai in traversal is:\n");
    TreeNode ** in_binary = inBinary(init_tree->root, &len);
    for (int i = 0; i < len; i++) {
        printf("%d ", in_binary[i]->data);
    }

    printf("\n");
    printf("the diedai post traversal is:\n");
    TreeNode ** post_binary = postBinary(init_tree->root, &len);
    for (int i = 0; i < len; i++) {
        printf("%d ", post_binary[i]->data);
    }

    return 0;
}