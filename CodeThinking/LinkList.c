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
    free(list_reverse);
    return 0;
}