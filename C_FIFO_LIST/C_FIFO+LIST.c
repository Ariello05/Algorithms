// C_FIFO_LIST.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <stdio.h>
#include "fifo.h"
#include "list.h"
#include "cycliclist.h"
#include <time.h>

void random_1000(List* list, const int min, const int max) {
	for (int i = 0; i < 1000; ++i) {
		int val = rand() % max + min;
		insert(list, val);
	}
}

void c_random_1000(CyclicList* list, const int min, const int max) {
	for (int i = 0; i < 1000; ++i) {
		int val = rand() % max + min;
		c_insert(list, val);
	}
}

extern void testFIFO();
extern void testList();
extern void testCyclicList();

int main()
{
	printf("Type [1,2,3] to choose which program to test, where\n 1:- FIFO (queue) \n 2:- Single linked List\n 3:- Cyclic double linked List\n");
	char c;
	srand(time(NULL));
	printf(" -> ");
	scanf_s("%c", &c, 1);
	printf("\n");
	if (c == '1') {
		testFIFO();
	}
	else if (c == '2') {
		testList();
	}
	else if (c == '3') {
		testCyclicList();
	}

	return 0;
}

void testFIFO() {
	Queue* queue = initQueue();
	enqueue(queue, 12);
	enqueue(queue, 20);
	enqueue(queue, 23);
	printf("%d\n", dequeue(queue));
	printf("%d\n", dequeue(queue));
	printf("%d\n", dequeue(queue));
	enqueue(queue, 22);
	printf("%d\n", dequeue(queue));
	printf("%d\n", front(queue));
	free(queue);
}

void testList() {
	clock_t start, end;
	double timeSpent = 0;

	List* list = initList();

	random_1000(list,0,1000); //1000 random values between 1 and 1000
	//Average time of 10000 tests on accessing 500th element
	for (int i = 0; i < 10000; i++) {
		start = clock();
		get(list, 700);
		end = clock();
		timeSpent += (double)(end - start);
	}
	timeSpent /= 10000;
	timeSpent /= CLOCKS_PER_SEC;
	printf("Averaged time of access to 700th node: %f secs. \n", timeSpent);

	timeSpent = 0;
	for (int i = 0; i < 5000; i++) {
		int n = rand() % 1000;

		start = clock();
		get(list, n);
		end = clock();
		timeSpent += (double)(end - start);
	}
	timeSpent /= 5000;
	timeSpent /= CLOCKS_PER_SEC;
	printf("Averaged time of access to 5000 random nodes: %f secs. \n", timeSpent);

	List* l1 = initList();
	List* l2 = initList();

	insert(l1, 1);
	insert(l1, 2);
	insert(l1, 3);
	insert(l2, 4);
	insert(l2, 5);
	insert(l2, 6);
	merge(l1, l2);
	printList(l1, 1);
	free(list);
	free(l1);
	free(l2);

	return 0;
}

void testCyclicList() {
	clock_t start, end;
	double timeSpent = 0;

	CyclicList* list = c_initList();

	random_1000(list, 0, 1000); //1000 random values between 1 and 1000
	//Average time of 10000 tests on accessing 500th element
	for (int i = 0; i < 10000; i++) {
		start = clock();
		c_get(list, 700);
		end = clock();
		timeSpent += (double)(end - start);
	}
	timeSpent /= 10000;
	timeSpent /= CLOCKS_PER_SEC;
	printf("Averaged time of access to 700th node: %f secs. \n", timeSpent);

	timeSpent = 0;
	for (int i = 0; i < 5000; i++) {
		int n = rand() % 1000;

		start = clock();
		c_get(list, n);
		end = clock();
		timeSpent += (double)(end - start);
	}
	timeSpent /= 5000;
	timeSpent /= CLOCKS_PER_SEC;
	printf("Averaged time of access to 5000 random nodes: %f secs. \n", timeSpent);

	CyclicList* l1 = c_initList();
	CyclicList* l2 = c_initList();

	c_insert(l1, 1);
	c_insert(l1, 2);
	c_insert(l1, 3);
	c_insert(l2, 4);
	c_insert(l2, 5);
	c_insert(l2, 6);
	c_merge(l1, l2);
	c_printList(l1, 1);
	free(list);
	free(l1);
	free(l2);

	return 0;
}