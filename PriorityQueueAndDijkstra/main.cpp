#include <iostream>
#include "PriorityQueue.h"

int main() {
	PriorityQueue pq(10);
	pq.insert(0, 1);
	pq.insert(5, 5);
	pq.insert(3, 5);
	pq.insert(2, 3);
	pq.insert(10, 9);
	pq.insert(1, 2);
	pq.insert(0, 10);
	pq.print();
	std::cout << "--------------------------\n";

	pq.priority(0, 9);
	pq.print();

	int a;
	std::cin >> a;
}