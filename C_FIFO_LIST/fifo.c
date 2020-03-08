#include <stdlib.h>
#include <stdio.h>
#include "fifo.h"

Queue* initQueue() {
	Queue* queue = malloc(sizeof(Queue));
	queue->startNode = NULL;
	queue->endNode = NULL;
	return queue;
}

int isEmpty(Queue* queue) {
	if (queue->startNode == NULL)
		return 1;
	else
		return 0;
}

void enqueue(Queue* queue, int value) {
	if (queue == NULL) {
		printf("Init queue!");
		return;
	}

	if (queue->startNode == NULL) {
		node* start = malloc(sizeof(node));
		start->val = value;
		start->next = NULL;
		queue->startNode = start;
		queue->endNode = start;
	}
	else {

		node* nextNode = malloc(sizeof(node));
		nextNode->val = value;
		nextNode->next = NULL;

		queue->endNode->next = nextNode;
		queue->endNode = nextNode;
	}
}

int dequeue(Queue* queue) {
	
	if (isEmpty(queue)) {
		printf("Can't dequeue empty queue!");
		return 0;
	}
	node* startNode = queue->startNode;
	int value = startNode->val;

	if (startNode == queue->endNode) {
		queue->startNode = NULL;
		queue->endNode = NULL;
		free(startNode);
		return value;
	}

	node* nextNode = startNode->next;
	queue->startNode = nextNode;

	free(startNode);

	return value;
}

int front(Queue* queue) {
	if (queue->startNode == NULL) {
		printf("Can't peek empty queue!");
		return 0;
	}
	return queue->startNode->val;
}

