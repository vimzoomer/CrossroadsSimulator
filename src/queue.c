#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->length = 0;
    return q;
}

void enqueue(Queue* q, Vehicle* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vehicle = value;
    newNode->next = NULL;

    q->length += 1;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

Vehicle* dequeue(Queue* q) {
    if (q->front == NULL) {
        return NULL;
    }

    Node* temp = q->front;
    Vehicle* value = temp->vehicle;

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    q->length -= 1;

    free(temp);
    return value;
}

Vehicle* peek(Queue* q) {
    return q->front ? q->front->vehicle : NULL;
}

bool isEmpty(Queue* q) {
    return q->front == NULL;
}

void deleteQueue(Queue* q) {
    Node* current = q->front;
    Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    free(q);
}

