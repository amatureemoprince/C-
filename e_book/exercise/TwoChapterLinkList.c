#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
}Node;

/**
 * 第一题
 */
void deleteSample(Node *head, const int x) {
    if (head == NULL) {
        return;
    }
    Node *p = head;
    Node *q = p->next;
    while (q) {
        if (q->data == x) {
            Node *temp = q;
            q = q->next;
            p->next = q;
            free(temp);
        }else {
            q = q->next;
            p = p->next;
        }
    }
}

/**
 * 第二题
 */
//涉及删除插入的问题首先思考双指针
void deleteMin(const Node *head) {
    if (head == NULL) {
        return;
    }
    
}
int main(void) {
    return 0;
}