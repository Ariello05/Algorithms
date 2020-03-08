#pragma once

#include <stdio.h>
#include <stdlib.h>


// Typedef so we don't have to write struct everywhere
typedef struct list_node {
	int val;//value
	struct list_node* next;//node
}l_node;

typedef struct list_head {
	l_node* startNode;
}List;

List* initList();

/**
Insert value into list's head
params:
list - A one way list
val - Value to be inserted into the list
*/
void insert(List* list, int val);
/**
returns:
1 - isEmpty
0 - isNotEmpty
*/
int isempty(List* list);
/**
Deletes first encountered element
params:
list - A one way list
val - Value to be deleted from the list
returns:
1 - successful delete
0 - couldn't find value
*/
int delete(List* list, int val);
/**
Gets value from list at index 
params:
list - A one way list (where latest element has index 0)
index - Index of element
*/
int get(List* list, int index);
/**
Searches for value
params:
list - A one way list (where latest element has index 0)
value - value
*/
int has(List* list, int value);
/**
Merges right list into left
params:
left - A one way list to be appended
right - A one way list
*/
void merge(List* left, List* right);
void printList(List* list, int flag);