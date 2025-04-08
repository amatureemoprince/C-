#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
    int val;
    struct NODE *next;
}NODE;

typedef struct LIST {
    int nums;
    NODE *head;
}LIST;

LIST *init_list();

int get_list_length(LIST *list);

NODE *create_new_node(int val);

void insert_list_head(LIST *list, int val);

int get_index_val_in_list(LIST *list, int index);

void insert_list_rear(LIST *list, int val);

void delete_index_in_list(LIST *list, int index);

void traverse_list(LIST *list);

void desroy_list(LIST *list);

LIST *init_list() {
    LIST *list = (LIST *)malloc(sizeof(LIST));
    list->nums = 0;
    NODE *head = (NODE *)malloc(sizeof(NODE));
    head->next = NULL;
    list->head = head;
    return list;
}

NODE *create_new_node(int val) {
    NODE *node = (NODE *)malloc(sizeof(NODE));
    node->next = NULL;
    node->val = val;
    return node;
}

void insert_list_head(LIST *list, int val) {
    NODE * new_node = create_new_node(val);
    new_node->next = list->head->next;
    list->head->next = new_node;
    list->nums++;
}

void insert_list_rear(LIST *list, int val) {
    NODE * new_node = create_new_node(val);
    NODE *p = list->head;
    while (p->next) {
        p = p->next;
    }
    p->next = new_node;
    list->nums++;
}

int get_index_val_in_list(LIST *list, int index) {
    if (index < 0 || index > list->nums) {
        printf("get_index_val_in_list-------------the param is error!\n");
        exit(1);
    }
    NODE *p = list->head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    return p->next->val;
}

int get_list_length(LIST *list) {
    return list->nums;
}

void delete_index_in_list(LIST *list, int index) {
    if (index < 0 || index > list->nums) {
        printf("delete_index_in_list-------------the param is error!\n");
        return;
    }
    NODE *p = list->head;
    NODE *q;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    q = p->next;
    p->next = q->next;
    free(q);
    list->nums--;
}

void traverse_list(LIST *list) {
    NODE *p = list->head;
    for (int i = 0; i < list->nums; i++) {
        p = p->next;
        printf("%d ", p->val);
    }
    printf("\n");
}

void desroy_list(LIST *list) {
    if (list == NULL) {
        return;
    }
    NODE *p = list->head->next;
    NODE *temp;
    for (int i = 0; i < list->nums; i++) {
        temp = p->next;
        free(p);
        list->head->next = temp;
        p = list->head->next;
    }
    free(list->head);
    free(list);
}

int main(){
    LIST * list = init_list();
    for (int i = 0; i < 4; i++) {
        insert_list_head(list, i);
    }
    for (int i = 0; i < 4; i++) {
        insert_list_rear(list, i);
    }
    traverse_list(list);
    printf("the list nums is %d\n", get_list_length(list));
    delete_index_in_list(list, 3);
    traverse_list(list);
    printf("get index = 1 val: %d\n", get_index_val_in_list(list, 1));
}