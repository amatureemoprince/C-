#include <inttypes.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 100
#define MAX_QUEUE 100

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

typedef struct Queue {
    TreeNode *data[MAX_QUEUE];
    int front;
    int rear;
    int size;
}Queue;

Stack *initStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

//简单使用，不定义为循环队列
Queue *initQueue() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
    return queue;
}

void inQueue(Queue *queue, TreeNode *node) {
    if (queue == NULL || node == NULL) {
        return;
    }
    if (queue->size == MAX_QUEUE) {
        return;
    }
    queue->data[queue->rear++] = node;
    queue->size++;
}

TreeNode *outQueue(Queue *queue) {
    if (queue == NULL || queue->size == 0) {
        return NULL;
    }
    TreeNode * tree_node = queue->data[queue->front++];
    queue->size--;
    return tree_node;
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
    TreeNode **result = (TreeNode **)malloc(sizeof(TreeNode *) * MAX_STACK);
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
    free(stack);
    *returnSize = index;
    return result;
}
//迭代中序遍历
TreeNode **inBinary(TreeNode *root, int *returnSize) {
    if (root == NULL) {
        return NULL;
    }
    Stack * stack = initStack();
    TreeNode **result = (TreeNode **)malloc(sizeof(TreeNode *) * MAX_STACK);
    int index = 0;

    TreeNode *cur = root;
    while (cur != NULL || stack->top != -1) {
        if (cur) {
            //遍历到最后一个左孩子节点
            push(stack, cur);
            cur = cur->left_child;
        }else {
            //处理栈中的节点
            cur = pop(stack);
            result[index++] = cur;
            cur = cur->right_child;
        }

    }
    free(stack);
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
    free(stack);
    reveser(result, index);
    *len = index;
    return result;
}
//层序遍历（使用队列辅助）
TreeNode **levelTraversal(TreeNode *root, int *returnSize) {
    Queue * queue = initQueue();
    TreeNode **result = (TreeNode **)malloc(sizeof(TreeNode *) * MAX_QUEUE);
    int index = 0;

    TreeNode *cur = root;
    inQueue(queue, cur);
    while (queue->size) {
        //出队并加入到result中
        TreeNode * out_queue = outQueue(queue);
        result[index++] = out_queue;
        //判断出队节点的左右孩子节点是否存在
        if (out_queue->left_child) {
            inQueue(queue, out_queue->left_child);
        }
        if (out_queue->right_child) {
            inQueue(queue, out_queue->right_child);
        }
    }
    free(queue);
    *returnSize = index;
    return result;
}

void reverseT(TreeNode ***arr, int len) {
    if (arr == NULL || len <= 1) {
        return;
    }

    int p = len - 1;
    for (int i = 0; i < len / 2; i++) {
        TreeNode **temp = arr[i];
        arr[i] = arr[p - i];
        arr[p - i] = temp;
    }
}

//从下面到上面进行层序遍历：root为遍历树的根，levelSize为每一层的长度，lines为共有多少层
TreeNode ***levelOrderBottom(TreeNode *root, int *levelSize, int *lines) {
    if (root == NULL) {
        *lines = 0;
        return NULL;
    }
    //初始化标记
    //每层的元素个数和用于遍历存储位置的index
    int level, levelIndex = 0;
    //初始化队列
    Queue *queue = initQueue();
    //头结点入队列
    TreeNode *cur = root;
    inQueue(queue, cur);
    //声明返回的result：动态分配内存
    TreeNode ***result = NULL;
    //遍历每一层
    while (queue->size != 0) {
        //存储该层的节点个数
        level = queue->size;
        levelSize[levelIndex] = level;
        //将该层的元素存储到一个一维数组中
        TreeNode **lineElements = (TreeNode **)malloc(sizeof(TreeNode *) * level);
        for (int i = 0; i < level; i++) {
            TreeNode * out_queue = outQueue(queue);
            lineElements[i] = out_queue;
            if (out_queue->left_child) {
                inQueue(queue, out_queue->left_child);
            }
            if (out_queue->right_child) {
                inQueue(queue, out_queue->right_child);
            }
        }
        //将一层的元素加入到result中
        result = (TreeNode ***)realloc(result, sizeof(TreeNode **) * (levelIndex + 1));
        result[levelIndex++] = lineElements;
    }
    *lines = levelIndex;
    //将遍历得到的结果反转
    reverseT(result, levelIndex);
    int len = levelIndex - 1;
    for (int i = 0; i < levelIndex / 2; i++) {
        int temp = levelSize[i];
        levelSize[i] = levelSize[len - i];
        levelSize[len - i] = temp;
    }
    return result;
}
//返回最右侧的节点
TreeNode **rightSideView(TreeNode *root, int *len) {
    if (root == NULL) {
        return NULL;
    }
    TreeNode **result = NULL;
    TreeNode *cur = root;
    int treeHight = 0;

    //初始化一个栈并将cur入栈
    Queue *queue = initQueue();
    inQueue(queue, cur);
    while (queue->size != 0) {
        TreeNode * out_queue = outQueue(queue);
        result = realloc(result, sizeof(TreeNode *) * treeHight + 1);
        result[treeHight++] = out_queue;
        if (out_queue->right_child) {
            inQueue(queue, out_queue->right_child);
        }
    }
    *len = treeHight;
    return result;
}

double *averageOfLevels(TreeNode *root, int *len) {
    if (root == NULL) {
        return ;
    }
    //声明队列
    Queue *queue = initQueue();
    TreeNode *cur = root;
    inQueue(queue, cur);
    //返回的double数组
    double *result = NULL;
    int treeHight = 0;
    int level = 0;
    double averge = 0;

    while (queue->size != 0) {
        //得到每一层的长度
        level = queue->size;
        //声明每层元素值和
        int total = 0;
        for (int i = 0; i < level; i++) {
            TreeNode * out_queue = outQueue(queue);
            total += out_queue->data;
            //入栈out_queue的孩子节点
            if (out_queue->left_child) {
                inQueue(queue, out_queue->left_child);
            }
            if (out_queue->right_child) {
                inQueue(queue, out_queue->right_child);
            }
        }
        //计算平均值并加入到result中
        result = (TreeNode **)realloc(result, sizeof(TreeNode *) * (treeHight + 1));
        result[treeHight++] = (total + 0.0) / level;
    }
    *len = treeHight;
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

void printNodeData(TreeNode **right_side_view, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", right_side_view[i]->data);
    }
    printf("\n");
}

void coutY(int *arr, int len) {
    for (int i = 2; i < 2 + len; i++) {
        arr[i - 2] = i;
    }
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
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

    int len;
    TreeNode ** right_side_view = rightSideView(init_tree->root, &len);
    printf("the tree right view is:\n");
    printNodeData(right_side_view, len);
    printf("the average num is: \n");
    double * average_of_levels = averageOfLevels(init_tree->root, &len);
    for (int i = 0; i < len; i++) {
        printf("%.2f ", average_of_levels[i]);
    }
    printf("\n");
    // printf("the preTraversal is:\n");
    // preorderTraversal(init_tree->root);
    // printf("\n");
    // printf("the inTraversal is:\n");
    // inTraversal(init_tree->root);
    // printf("\n");
    // printf("the postTraversal is:\n");
    // postTraversal(init_tree->root);
    // printf("\n");
    //
    // int len;
    // TreeNode ** pre_binary = preBinary(init_tree->root, &len);
    // printf("the diedai pre traversal is:\n");
    // for (int i = 0; i < len; i++) {
    //     printf("%d ", pre_binary[i]->data);
    // }
    // printf("\n");
    // printf("the diedai in traversal is:\n");
    // TreeNode ** in_binary = inBinary(init_tree->root, &len);
    // for (int i = 0; i < len; i++) {
    //     printf("%d ", in_binary[i]->data);
    // }
    //
    // printf("\n");
    // printf("the diedai post traversal is:\n");
    // TreeNode ** post_binary = postBinary(init_tree->root, &len);
    // for (int i = 0; i < len; i++) {
    //     printf("%d ", post_binary[i]->data);
    // }
    // printf("\n");
    // printf("the level traversal is:\n");
    // TreeNode ** level_traversal = levelTraversal(init_tree->root, &len);
    // for (int i = 0; i < len; i++) {
    //     printf("%d ", level_traversal[i]->data);
    // }
    // printf("\n");
    // printf("test:\n");
    // int arr[] = {0, 1, 2, 3};
    // coutY(arr, 4);
    // for (int i = 0; i < 4; i++) {
    //     printf("%d ", arr[i]);
    // }
    // printf("\n");
    // // TODO: 从下到上遍历
    // int levelSize[] = {0};
    // int lines = 0;
    // TreeNode *** level_order_bottom = levelOrderBottom(init_tree->root, levelSize, &lines);
    // printf("the lines is: %d\n", lines);
    //
    // printf("from buttom to the top is: \n");
    // printf("[");
    // for (int i = 0; i < lines; i++) {
    //     printf(" [");
    //     for (int j = 0; j < levelSize[i]; j++) {
    //         printf(" %d ", level_order_bottom[i][j]->data);
    //     }
    //     printf("] ");
    // }
    // printf("]\n");

    return 0;
}