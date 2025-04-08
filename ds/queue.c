//实现循环队列：采用舍去一个空间来区分满和空

#define MAX_QUEUE_NUM 100
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue{
    int data[MAX_QUEUE_NUM];
    int rear;
    int front;
}Queue;

Queue *init_queue() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = 0;
    queue->rear = 0;
    return queue;
}


int in_queue(Queue *queue, int val) {
    if ((queue->rear + 1) % MAX_QUEUE_NUM == queue->front) {
        return 0;
    }
    queue->data[queue->rear % MAX_QUEUE_NUM] = val;
    queue->rear = (queue->rear + 1) % MAX_QUEUE_NUM;
    return 1;
}

int out_queue(Queue *queue) {
    if (queue->front == queue->rear) {
        return -1;
    }
    int x = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAX_QUEUE_NUM;
    return x;
}

void traverse_queue(Queue *queue) {
    int i = queue->front;
    int j = queue->rear;
    while (i != j) {
        printf("%d ", queue->data[i]);
        i = (i + 1) % MAX_QUEUE_NUM;
    }
    printf("\n");
}

