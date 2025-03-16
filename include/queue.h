#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "vehicle.h"

typedef struct Node {
    Vehicle* vehicle;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int length;
} Queue;

Queue* createQueue();
void enqueue(Queue* q, Vehicle* vehicle);
Vehicle* dequeue(Queue* q);
Vehicle * peek(Queue* q);
bool isEmpty(Queue* q);
void deleteQueue(Queue* q);

#endif
