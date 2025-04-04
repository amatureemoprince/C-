#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 定义链表节点
 */
typedef struct Node {
    int data;
    struct Node *next;
} Node;
#define MAX_SIZE 100
typedef struct{
    int data;
    int next;
}SLinkList[MAX_SIZE];
// 初始化链表
void initList(SLinkList list) {
    for (int i = 0; i < MAX_SIZE; i++) {
        list[i].data = 0;  // 初始化数据为 0
        list[i].next = -1; // 初始化 next 为 -1，表示没有指向下一个节点
    }
}


/**
 * 创建一个链表头结点
 * @return 头节点
 */
Node *createHead() {
    Node *head = (Node *) malloc(sizeof(Node));
    if (head == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    head->data = 0;
    head->next = 0;
    return head;
}

/**
 * 获取链表长度
 * @param head 链表头
 * @return 链表长度
 */
int getLinkLen(const Node *head) {
    return head->data;
}

/**
 * 创建一个节点
 * @param data 节点的值
 * @return 新节点
 */
Node *createNode(const int data) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

/**
 * 头插法
 * @param head 插入的链表头结点地址
 * @param data 插入的数据
 */
void insertHead(Node *head, const int data) {
    if (head == NULL) {
        printf("the head is the NULL\n");
        return;
    }
    Node *newNode = createNode(data);
    newNode->next = head->next;
    head->next = newNode;
    head->data++;
}

/**
 *
 * @param head 链表头
 * @param data 元素值
 * @param location 插入的位置
 */
void insertLocation(Node *head, const int data, const int location) {
    if (head == NULL) {
        return;
    }
    head->data++;
    Node *node = createNode(data);
    Node *p = head;
    for (int i = 0; i < location - 1; i++) {
        p = p->next;
    }
    const Node *q = p->next;
    p->next = node;
    node->next = q->next;
}

/**
 * 尾差法
 * @param head 链表头
 * @param data 插入数值
 */
void insetEnd(Node *head, const int data) {
    if (head == NULL) {
        return;
    }
    head->data++;
    Node *p = head;
    //遍历到最后一个节点
    while (p->next) {
        p = p->next;
    }
    Node *node = createNode(data);
    p->next = node;
}

/**
 * 遍历链表
 * @param head 需要遍历的头节点
 */
void traversalLinkList(const Node *head) {
    if (head == NULL || head->next == NULL) {
        printf("the head is the NULL or empty list\n");
        return;
    }
    const Node *node = head->next;
    printf("linkList has %d nodes: ", head->data);
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

/**
 *
 * @param head 查询链表头节点
 * @param num 查找的数值
 * @return 数值的位置
 */
int findElement(const Node *head, const int num) {
    if (head == NULL) {
        return -1;
    }
    int index = 1;
    for (const Node *node = head->next; node; node = node->next) {
        if (node->data == num) {
            return index;
        }
        index++;
    }
    return index;
}

/**
 *
 * @param head 链表的头节点
 * @param index 删除的位置
 */
void deletedElement(Node *head, const int index) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    head->data--;
    Node *p = head;
    //遍历到要删除的节点之前
    for (int i = 0; i < index - 1; i++) {
        p = p->next;
    }
    //删除并释放节点
    Node *q = p->next;
    p->next = q->next;
    free(q);
}

/**
 * 释放链表节点
 * @param head 需要释放的头节点
 */
void freeNode(Node *head) {
    if (head == NULL) {
        return;
    }
    Node *p = head;
    while (p) {
        Node *q = p->next;
        free(p);
        p = q;
    }
}

/**
 * 2009年题
 * 已知一个带有表头结点的单链表，结点结构为
 * data	link
 * 假设该链表只给出了头指针list。在不改变链表的前提下，请设计一个尽可能高效的算法，查找链表中倒数第k
 * 个位置上的结点（k
 * 为正整数）。若查找成功，算法输出该结点的data域的值，并返回1；否则，只返回0
 */
//思路：双指针法，快的先走k步，然后慢的和快的一起走，快的到了最后，慢的就是倒数的第k个了
int findKBackWord(const Node *head, const int k) {
    if (head == NULL || k <= 0) {
        return 0;
    }
    const Node *fast = head;
    const Node *slow = head;
    for (int i = 0; i < k; i++) {
        fast = fast->next;
    }
    if (!fast) {
        return 0;
    }
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }
    printf("the back element %d is %d \n", k, slow->data);
    return 1;
}

/**
 *2012年真题
 * 假定采用带头结点的单链表保存单词，当两个单词有相同的后缀时，可共享相同的后缀存储空间，
 * 例如，“loading”和”being“的存储映像如下图所示。
 * 设str1和str2分别指向两个单词所在单链表的头结点，链表结点结构为|data| |next|，请设计一个时间上尽可能高效的算法，
 * 找出由str1和str2所指向的两个链表共同后缀的起始位置（如图中字符i所在结点的位置p）。
 */
int findSimpleLocation(const Node *str1, const Node *str2) {
    if (str1->next && str2->next) {
        fprintf(stderr, "the parameter is NULL");
        return -1;
    }
    int len1 = 0;
    int len2 = 0;
    int index = 0;
    const Node *head1 = str1->next;
    const Node *head2 = str2->next;
    while (head1 != NULL) {
        len1++;
        head1 = head1->next;
    }
    while (head2 != NULL) {
        len2++;
        head2 = head2->next;
    }
    head1 = str1->next;
    head2 = str2->next;
    const int k = (len1 > len2) ? len1 - len2 : len2 - len1;
    //如果str1更长的话，移动str1上的指针
    if (len1 > len2) {
        for (int i = 0; i < k; i++) {
            if (head1) {
                head1 = head1->next;
            }
        }
    }else {
        for (int i = 0; i < k; i++) {
            if (head2) {
                head2 = head2->next;
            }
        }
    }
    //现在head1和head2都在离最后一个节点相同远的地方了
    while (head1 && head2) {
        if (head1 == head2) {
            return k + index;
        }
        index++;
        head1 = head1->next;
        head2 = head1->next;
    }
    return -1;
}



int main(void) {
    Node *head = createHead();
    for (int i = 0; i < 10; i++) {
        insertHead(head, i);
    }
    traversalLinkList(head);
    printf("the index of 5 is %d \n", findElement(head, 5));
    printf("delete 5 location from the linkList .\n");
    deletedElement(head, 5);
    traversalLinkList(head);
    printf("insert 10 in the linkList .\n");
    insertHead(head, 10);
    traversalLinkList(head);
    // TODO: 测试2009年数据结构题
    printf("the result is %d \n", findKBackWord(head, 1));
    freeNode(head);
    SLinkList list; // 声明链表
    initList(list); // 初始化链表

    // 添加节点示例
    list[0].data = 1;
    list[0].next = 1; // 指向下一个节点
    list[1].data = 2;
    list[1].next = -1; // 最后一个节点的 next 指向 -1

    // 打印链表
    for (int i = 0; i < 2; i++) {
        printf("Node %d: data = %d, next = %d\n", i, list[i].data, list[i].next);
    }

    return 0;
}
