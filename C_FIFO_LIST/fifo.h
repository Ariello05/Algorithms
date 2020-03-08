#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct queue_node {
	int val;
	struct queue_node* next;
}node;

typedef struct queue_head {
	node* startNode;
	node* endNode;
}Queue;

Queue* initQueue();
int isEmpty(Queue* queue);
/**
Enqueues value into the queue
params:
queue - A queue
val - Value to be inserted into the queue
*/
void enqueue(Queue* queue, int value);
/**
Dequeues value from the queue
params:
queue - A queue
*/
int dequeue(Queue* queue);
int front(Queue* queue);

