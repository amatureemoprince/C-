#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct LinkNode {
  int data;
  struct LinkNode *next;
}LinkNode;

//没有头结点的操作
LinkNode *removeElements(LinkNode *head, int val) {
    if (head == NULL) {
        return NULL;
    }

    LinkNode *temp;

    while (head->data == val) {
        temp = head;
        head = head->next;
        free(temp);
    }

    LinkNode *p = head;

    while (p != NULL && p->next != NULL) {
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

//带有头结点
LinkNode *removeElementsWithHeadNode(LinkNode *head, int val) {
    LinkNode *temp;
    LinkNode *p = head;
    while (p->next != NULL) {
        if (p->next->data == val) {
            temp = p->next;
            p = temp->next;
            free(temp);
        }else {
            p = p->next;
        }
    }
    return head;
}

void printList(LinkNode *head) {
    LinkNode *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}



int main(){

  return 0;
}
