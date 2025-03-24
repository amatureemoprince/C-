#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <c++/x86_64-w64-mingw32/bits/os_defines.h>

typedef struct LinkNode {
    int data;
    struct LinkNode *next;
}LinkNode;

typedef struct LinkList {
    int size;
    LinkNode *data;
}LinkList;

LinkNode *removeElements(LinkNode **head, int val) {
    LinkNode *temp;

    // 处理头结点
    while (head != NULL && (*head)->data == val) {
        temp = *head;
        *head = temp->next;
        free(temp);
    }

    LinkNode *p = *head;

    // 处理剩余节点
    while (p != NULL && p->next != NULL) {
        if (p->next->data == val) {
            temp = p->next;
            p->next = temp->next;
            free(temp);
        } else {
            p = p->next;
        }
    }

    return *head;
}

//因为不用修改head故可以直接传入LinkNode *head
LinkNode *removeElementsWithHeadNode(LinkNode *head, int val) {
    LinkNode *temp;
    LinkNode *p = head;
    while (p->next != NULL) {
        if (p->next->data == val) {
            temp = p->next;
            p->next = temp->next;
            free(temp);
        }else {
            p = p->next;
        }
    }
    return head;
}

//以下的函数都默认使用头结点

//初始化带有头结点的List
LinkList *createList() {
    LinkList *list = (LinkList *)malloc(sizeof(LinkList));
    list->size = 0;
    LinkNode *head = (LinkNode *)malloc(sizeof(LinkNode));
    head->next = NULL;
    head->data = 0;
    list->data = head;
    return list;
}

//获取第index个元素值
int get(LinkList *list, int index) {
    if (index < 0 || index >= list->size) {
        return -1;
    }
    LinkNode *p = list->data;
    for (int i = 0; i < index + 1; i++) {
        p = p->next;
    }
    return p->data;
}

//头插法
void insertAtHead(LinkList *list, int val) {
    if (list == NULL) {
        return ;
    }
    LinkNode *head = list->data;
    LinkNode *node = (LinkNode *)malloc(sizeof(LinkNode));
    node->data = val;
    node->next = head->next;
    head->next = node;
    list->size++;
}
//尾插法
void insertAtTail(LinkList *list, int val) {
    if (list == NULL) {
        return ;
    }
    LinkNode *p = list->data;
    while (p->next != NULL) {
        p = p->next;
    }
    LinkNode *node = (LinkNode *)malloc(sizeof(LinkNode));
    node->data = val;
    node->next = p->next;
    p->next = node;
    list->size++;
}
//插入index位置
void insertAtIndex(LinkList *list, int index, int val) {
    if (list == NULL) {
        return ;
    }
    if (index < 0 || index > list->size) {
        return ;
    }
    LinkNode *head = list->data;
    LinkNode* node = (LinkNode *)malloc(sizeof(LinkNode));
    node->data = val;
    for (int i = 0; i < index; i++) {
        head = head->next;
    }
    node->next = head->next;
    head->next = node;
    list->size++;
}

void deleteAtIndex(LinkList *list, int index) {
    if (list == NULL) {
        return;
    }
    if (index < 0 || index >= list->size) {
        return;
    }
    LinkNode *head = list->data;
    for(int i = 0; i < index; i++) {
        head = head->next;
    }
    LinkNode *temp = head->next;
    head->next = temp->next;
    free(temp);
}

//反转链表
void reverse(LinkList *list) {
    if (list == NULL) {
        return;
    }
    LinkNode *pre = NULL;
    LinkNode *cur = list->data->next;
    LinkNode *temp;
    while (cur) {
        temp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = temp;
    }
    list->data->next = pre;
}

void exchangeNextTo(LinkList *list) {
    if (list == NULL) {
        return ;
    }
    LinkNode *head = list->data;

    LinkNode *p = head->next->next;
    LinkNode *q = head->next;
    while (p) {
        LinkNode *temp = p->next;
        p->next = head->next;
        head->next = p;
        q->next = temp;

        head = q;
        q = q->next;
        p = q->next;
    }

}

void deleteTailK(LinkList *list, int k) {
    if (list == NULL) {
        return ;
    }
    if (k > list->size) {
        return ;
    }
    LinkNode *p = list->data;
    LinkNode *q = list->data;
    for (int i = 0; i < k; i++) {
        p = p->next;
    }

    while (p->next) {
        p = p->next;
        q = q->next;
    }

    LinkNode *temp = q->next;
    q->next = p;
    free(temp);
}

LinkNode *getIntersectionNode(LinkList *list_a, LinkList *list_b) {
    if (list_a == NULL || list_b == NULL) {
        return NULL;
    }
    LinkNode *p_a = list_a->data;
    LinkNode *p_b = list_b->data;
    int len_a = 0;
    int len_b = 0;
    //得到两个链表的数据长度
    while (p_a->next != NULL || p_b->next != NULL) {
        if (p_a->next != NULL) {
            p_a = p_a->next;
            len_a++;
        }
        if (p_b->next != NULL) {
            p_b = p_b->next;
            len_b++;
        }
    }
    printf("len_a is %d, len_b is %d\n", len_a, len_b);
    //先让长的跑
    LinkNode *longHead, *shortHead;
    int len = abs(len_a - len_b);
    if (len_a >= len_b) {
        longHead = list_a->data;
        shortHead = list_b->data;
    }else {
        shortHead = list_a->data;
        longHead = list_b->data;
    }
    for (int i = 0; i < len; i++) {
        longHead = longHead->next;
    }
    //在同一起跑线上进行判断
    while (shortHead) {
        if (shortHead == longHead) {
            return shortHead;
        }else {
            shortHead = shortHead->next;
            longHead = longHead->next;
        }
    }
    return NULL;
}

LinkNode *detectCycle(LinkList *list) {
    if (list == NULL) {
        return NULL;
    }
    LinkNode *head = list->data;
    LinkNode *fast = head->next->next;
    LinkNode *slow = head->next;

    int pos = -1;
    int index = -1;

    while (fast != NULL) {
        if (fast == NULL) {
            break;
        }
        if (slow == fast) {
            pos = index;
            break;
        }
        fast = fast->next->next;
        slow = slow->next;
        index++;
    }

    if (pos != -1) {
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }

    return NULL;
}

LinkNode *createNode(int val) {
    LinkNode *node = (LinkNode *)malloc(sizeof(LinkNode));
    node->data = val;
    node->next = NULL;
    return node;
}

void dealListThree(LinkList *list_a, LinkList *list_b) {
    LinkNode * link_node1 = createNode(5);
    LinkNode * link_node2 = createNode(6);
    LinkNode * link_node3 = createNode(7);
    LinkNode * link_node4 = createNode(2);
    LinkNode * link_node5 = createNode(4);
    link_node1->next = link_node2;
    link_node2->next = link_node3;
    link_node3->next = link_node4;
    link_node5->next = link_node3;
    list_a->data->next = link_node1;
    list_b->data->next = link_node5;
}

void dealCycle(LinkList *list) {
    // 2 4 5 8   result is 4
    LinkNode * link_node1 = createNode(2);
    LinkNode * link_node2 = createNode(4);
    LinkNode * link_node3 = createNode(5);
    LinkNode * link_node4 = createNode(8);
    link_node1->next = link_node2;
    link_node2->next = link_node3;
    link_node3->next = link_node4;
    link_node4->next = link_node2;
    list->data->next = link_node1;
}

void printList(LinkNode *head) {
    LinkNode *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void coutList(LinkList *list) {
    LinkNode *head = list->data;
    while (head->next != NULL) {
        printf("%d -> ", head->next->data);
        head = head->next;
    }
    printf("NULL\n");
}

// int main() {
//     LinkNode *head = (LinkNode *)malloc(sizeof(LinkNode));
//     head->data = 1;
//     head->next = (LinkNode *)malloc(sizeof(LinkNode));
//     head->next->data = 2;
//     head->next->next = (LinkNode *)malloc(sizeof(LinkNode));
//     head->next->next->data = 3;
//     head->next->next->next = NULL;
//
//     printList(head);
//
//     removeElements(&head, 1);
//     printList(head);
//
//     // 释放链表内存
//     LinkNode *current = head;
//     while (current != NULL) {
//         LinkNode *temp = current;
//         current = current->next;
//         free(temp);
//     }
//
//     return 0;
// }
int main() {
    LinkList * link_list = createList();
    for (int i = 0; i < 10; i++) {
        insertAtHead(link_list, i);
    }
    printf("the insert at head 0-9 elements:\n");
    coutList(link_list);
    for (int i = 0; i < 10; i++) {
        insertAtTail(link_list, i);
    }
    printf("the insert at tail 0-9 elements:\n");
    coutList(link_list);
    printf("the insert at index:\n");
    insertAtIndex(link_list, 1, 5);
    coutList(link_list);
    printf("get index is 5 element: %d\n", get(link_list, 7));
    printf("delete the indes:\n");
    deleteAtIndex(link_list, 4);
    coutList(link_list);
    free(link_list);

    LinkList *list_reverse = createList();
    for (int i = 0; i < 5; i++) {
        insertAtHead(list_reverse, i);
    }
    printf("the two list is: \n");
    coutList(list_reverse);
    reverse(list_reverse);
    printf("reverse the two list: \n");
    coutList(list_reverse);
    printf("exchange the two list: \n");
    exchangeNextTo(list_reverse);
    coutList(list_reverse);
    printf("delete tail k :\n");
    deleteTailK(list_reverse, 2);
    coutList(list_reverse);

    LinkList *list_a = createList();
    LinkList *list_b = createList();
    dealListThree(list_a, list_b);
    printf("the list_a is:\n");
    coutList(list_a);
    printf("the list_b is:\n");
    coutList(list_b);
    LinkNode * intersection_node = getIntersectionNode(list_a, list_b);
    if (intersection_node == NULL) {
        printf("the two lists have't sample node.\n");
    }else {
        printf("the two lists have sample node: %d.\n", intersection_node->data);
    }

    LinkList * links = createList();
    dealCycle(links);
    LinkNode * detect_cycle = detectCycle(links);
    if (detect_cycle == NULL) {
        printf("haven't cycle point!\n");
    }else {
        printf("the cycle point is %d.\n", detect_cycle->data);
    }

    free(list_reverse);
    return 0;
}