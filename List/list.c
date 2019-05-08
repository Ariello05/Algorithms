#include <stdio.h>
#include <stdlib.h>

// Typedef so we don't have to write struct everywhere
typedef struct list_node {
	int val;//value
	struct list_node * next;//node
}node;

typedef struct list_head {
	node * beg;
}list;

/**
Insert value into list's head
params:
list - A one way list
val - Value to be inserted into the list
*/
void insert(list * list, int val) {
	node * newNode = malloc(sizeof(node *));
	newNode->val = val;
	newNode->next = list->beg;//old head
	list->beg = newNode;//new head
}

/**
returns:
1 - isEmpty
0 - isNotEmpty
*/
int isempty(list * list) {
	if (list->beg == NULL)
		return 1;
	else
		return 0;
}

/**
Deletes first encountered element
params:
list - A one way list
val - Value to be deleted from the list
returns:
1 - successful delete
0 - couldn't find value
*/
int delete(list * list, int val) {

	if (isempty(list))
		return 0;

	node * temp = list->beg;

	if (list->beg->val == val) {
		list->beg = list->beg->next;
		free(temp);
		return 1;
	}
	while (temp->next != NULL) {
		if (temp->next->val == val) {
			node *buf = temp->next;
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

void printList(list *list, int flag) {
	if (isempty(list)) {
		printf("Empty list \n");
		return;
	}
	int i = 0;
	node * temp = list->beg;
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

/**
returns:
1 - found value
0 - couldn't find value
*/
int findMTF(list *list, int val) {
	if (isempty(list))
		return 0;


	if (list->beg->val == val) {
		return 1;
	}

	node * temp = list->beg;
	while (temp->next != NULL) {
		if (temp->next->val == val) {
			node *buf = temp->next;
			temp->next = buf->next;
			buf->next = list->beg;
			list->beg = buf;

			return 1;
		}
		else {
			temp = temp->next;
		}
	}
	return 0;
}

/**
returns:
1 - found value
0 - couldn't find value
*/
int findTRANS(list *list, int val) {
	if (isempty(list))
		return 0;

	node * prev = list->beg;
	node * temp = list->beg->next;
	if (temp == NULL || prev->val == val)// If list has got only 1 element or first element is the one we are searching for
		return 1;

	if (temp->val == val) {
		prev->next = temp->next;
		temp->next = prev;
		list->beg = temp;
		return 1;
	}

	while (temp->next != NULL) {
		if (temp->next->val == val) {
			node *buf = temp->next;
			temp->next = buf;
			prev->next = temp;
			return 1;
		}
		else {
			printf("ELSE\n");
			prev = temp;
			temp = temp->next;
		}
	}
	return 0;
}
/*
int main() {
	list * lista = malloc(sizeof(list *));
	lista->beg = NULL;

	insert(lista, 10);
	insert(lista, 20);
	insert(lista, 30);
	insert(lista, 40);
	printList(lista, 1);
	findTRANS(lista, 20);

	printList(lista, 1);
}
*/