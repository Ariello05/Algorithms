#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List* initList() {
	List* list = malloc(sizeof(List));
	list->startNode = NULL;
	return list;
}

void insert(List* list, int val) {
	if (list == NULL) {
		printf("Init list!");
		return;
	}

	l_node* newNode = malloc(sizeof(l_node));
	newNode->val = val;
	newNode->next = list->startNode;//old head
	list->startNode = newNode;//new head
}

int isempty(List* list) {
	if (list->startNode == NULL)
		return 1;
	else
		return 0;
}

int delete(List* list, int val) {

	if (isempty(list))
		return 0;

	l_node* temp = list->startNode;

	if (list->startNode->val == val) {
		list->startNode = list->startNode->next;
		free(temp);
		return 1;
	}
	while (temp->next != NULL) {
		if (temp->next->val == val) {
			l_node* buf = temp->next;
			temp->next = buf->next;
			free(buf);
			return 1;
		}
		else {
			temp = temp->next;
		}
	}
	return 0;
}

int get(List* list, int index) {
	if (isempty(list)) {
		return 0;
	}

	l_node* el = list->startNode;

	for (int i = 0; i < index; ++i) {
		el = el->next;
	}

	return el->val;
}

int has(List* list, int val) {
	if (isempty(list))
		return 0;

	l_node* temp = list->startNode;

	if (list->startNode->val == val) {
		return 1;
	}
	while (temp->next != NULL) {
		if (temp->next->val == val) {
			return 1;
		}
		else {
			temp = temp->next;
		}
	}
	return 0;
}


void merge(List* left, List* right) {
	l_node* start = left->startNode;
	while (start->next != NULL) {
		start = start->next;
	}
	start->next = right->startNode;
}


void printList(List* list, int flag) {

	if (isempty(list)) {
		printf("Empty list \n");
		return;
	}
	int i = 0;
	l_node* temp = list->startNode;
	printf("%5s   %8s\n", "VALUE", "NEXT POINTER");

	while (temp != NULL) {
		if (temp->next == NULL)
			printf("%5d %8s\n", temp->val, "NULL");
		else
			printf("%5d %8p\n", temp->val, temp->next);
		temp = temp->next;
		++i;
	}
	printf("i: %d\n", i);
	if (flag) {
		printf("\n");
	}
}
