#include <stdio.h>
#include <stdlib.h>
#include "cycliclist.h"

CyclicList* c_initList() {
	CyclicList* list = malloc(sizeof(CyclicList));
	list->startNode = NULL;
	return list;
}

void c_insert(CyclicList* list, int val) {
	if (list == NULL) {
		printf("Init list!");
		return;
	}
	cl_node* newNode = malloc(sizeof(cl_node));
	newNode->val = val;

	if (list->startNode == NULL) {
		newNode->next = newNode;
		newNode->prev = newNode;
		list->startNode = newNode;
		return;
	}
	cl_node* oldStart = list->startNode;
	cl_node* listEnd = list->startNode->prev;
	
	listEnd->next = newNode;
	oldStart->prev = newNode;
	newNode->prev = listEnd;
	newNode->next = oldStart;
}

int c_isempty(CyclicList* list) {
	if (list->startNode == NULL)
		return 1;
	else
		return 0;
}

int c_delete(CyclicList* list, int val) {

	if (isempty(list))
		return 0;

	cl_node* temp = list->startNode;

	if (temp->val == val) {
		if (temp->next == temp) {//one element case
			list->startNode = NULL;
			free(temp);
		}
		else {
			cl_node* next = temp->next;
			cl_node* prev = temp->prev;

			next->prev = prev;
			prev->next = next;
			list->startNode = next;
			free(temp);
		}
		return 1;
	}
	temp = temp->next;

	while (temp != list->startNode) {
		if (temp->val == val) {
			cl_node* next = temp->next;
			cl_node* prev = temp->prev;

			next->prev = prev;
			prev->next = next;
			free(temp);
			return 1;
		}
		else {
			temp = temp->next;
		}
	}
	return 0;
}

int c_has(CyclicList* list, int val) {
	if (isempty(list))
		return 0;

	cl_node* temp = list->startNode;

	if (temp->val == val){
		return 1;
	}
	temp = temp->next;

	while (temp != list->startNode) {
		if (temp->val == val) {
			return 1;
		}
		else {
			temp = temp->next;
		}
	}
	return 0;
}

int c_get(CyclicList* list, int index) {
	if (isempty(list)) {
		return 0;
	}

	cl_node* el = list->startNode;

	for (int i = 0; i < index; ++i) {
		el = el->next;
	}

	return el->val;
}

void c_merge(CyclicList* left, CyclicList* right) {
	if (isempty(right) || isEmpty(left)) {
		printf("Cannot merge empty list!");
		return;
	}
	cl_node* leftStart = left->startNode;
	cl_node* leftEnd = leftStart->prev;

	cl_node* rightStart = right->startNode;
	cl_node* rightEnd = rightStart->prev;

	leftEnd->next = rightStart;
	rightStart->prev = leftEnd;
	rightEnd->next = leftStart;
	leftStart->prev = rightEnd;
}


void c_printList(CyclicList* list, int flag) {
	if (isempty(list)) {
		printf("Empty list \n");
		return;
	}
	int i = 0;
	cl_node* temp = list->startNode;
	printf("%5s   %8s \t%8s \n", "VALUE", "PREV POINTER", "NEXT POINTER");

	while (temp != NULL) {
		if (temp->next == list->startNode) {
			printf("%5d %8p %8p\n", temp->val, temp->prev, temp->next);
			break;
		}
		else
			printf("%5d %8p %8p\n", temp->val, temp->prev, temp->next);
		temp = temp->next;
		++i;
	}
	printf("i: %d\n", i);
	if (flag) {
		printf("\n");
	}
}
