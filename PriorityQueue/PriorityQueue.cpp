#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(int n)
	:max(n)
{
	size = 0;
	tab = new PQData[n];//simplest
}


PriorityQueue::~PriorityQueue()
{
	delete[] tab;
}

void PriorityQueue::insert(unsigned int p, int x)
{
	PQData data = PQData(p, x);
	insert(data);
}

void PriorityQueue::insert(PQData data)
{
	if (size == max) {
		throw std::runtime_error("Overflow");
	}

	tab[size] = data;

	size++;
	bubbleUp(size - 1, data);
}

void PriorityQueue::priority(unsigned int p, int x)
{
	PQData pqd;
	for (int i = 0; i < size; ++i) {
		pqd = tab[i];
		if (pqd.value == x && pqd.priority > p) {
			tab[i].priority = p;
			bubbleUp(i, tab[i]);
		}
	}
	 
}

int PriorityQueue::top()
{
	if (size == 0) {
		throw std::runtime_error("Empty");
	}

	return tab[0].value;
}

int PriorityQueue::pop()
{
	if (size == 0) {
		throw std::runtime_error("Empty");
	}
	int p = top();
	tab[0] = tab[size-1];

	size--;
	bubbleDown(0);
	return p;
}

bool PriorityQueue::isEmpty()
{
	return size == 0;
}

void PriorityQueue::print()
{
	for (int i = 0; i < size; ++i) {
		std::cout << "Index: " << i << " | Priority: " << tab[i].priority << " | Value: " << tab[i].value << std::endl;
	}
}


void PriorityQueue::swap(int i1, int i2)
{
	PQData buf = tab[i1];
	tab[i1] = tab[i2];
	tab[i2] = buf;
}

void PriorityQueue::bubbleUp(int i, PQData data)
{
	int parentI = (i - 1) / 2;
	while (parentI >= 0 && tab[parentI].priority > data.priority) {
		swap(parentI, i);
		i = parentI;
		parentI = (i - 1) / 2;
	}
}

void PriorityQueue::bubbleDown(int i)
{
	int left = i * 2 + 1;
	int right = i * 2 + 2;
	int max = i;

	if (left < size && tab[left].priority < tab[max].priority) {
		max = left;
	}

	if (right < size && tab[right].priority < tab[max].priority) {
		max = right;
	}

	if (max != i) {
		swap(max, i);
		bubbleDown(max);
	}
}
