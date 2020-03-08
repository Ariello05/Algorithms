#pragma once

#include <stdio.h>
#include <stdlib.h>

// Typedef so we don't have to write struct everywhere
typedef struct clist_node {
	int val;//value
	struct clist_node* next;//node
	struct clist_node* prev;
}cl_node;

typedef struct clist_head {
	cl_node* startNode;
}CyclicList;

CyclicList* c_initList();

/**
Insert value into list's head
params:
list - A one way list
val - Value to be inserted into the list
*/
void c_insert(CyclicList* list, int val);
/**
returns:
1 - isEmpty
0 - isNotEmpty
*/
int c_isempty(CyclicList* list);
/**
Deletes first encountered element
params:
list - A one way list
val - Value to be deleted from the list
returns:
1 - successful delete
0 - couldn't find value
*/
int c_delete(CyclicList* list, int val);
/**
Gets value from list at index
params:
list - A one way list (where latest element has index 0)
index - Index of element
*/
int c_get(CyclicList* list, int index);
/**
Merges right list into left
params:
left - A one way list to be appended
right - A one way list
*/
void c_merge(CyclicList* left, CyclicList* right);
void c_printList(CyclicList* list, int flag);