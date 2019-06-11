#include "Bipartite.h"
#include <vector>
#include <random>
#include <algorithm>
#include <limits>

Bipartite::Bipartite(unsigned int k, unsigned int i)
{
	if (i > k) {
		throw std::exception("Has to be i <= k");
	}
	this->k = k;
	this->i = i;
	sizeV = pow(2, k);
	int total = 2 * sizeV + 2;//V1 + V2 + s + t
	vect = new List*[total];
	for (int j = 0; j < total; ++j) {
		vect[j] = nullptr;
	}

	for (int j = 1; j <= sizeV; ++j) {
		List* el = new List(Route(j,1));
		el->next = vect[0];
		vect[0] = el;
	}

	for (int j = sizeV+1; j < total-1; ++j) {
		List* el = new List(Route(total-1,1));
		vect[j] = el;
	}
 
	int l_size = 0;//list size
	bool valid = false;

	List* d;
	for (int j = 1; j <= sizeV; ++j) {
		while (l_size < i) {
			int ran = std::rand() % sizeV + sizeV + 1;
			valid = false;

			while (!valid) {
				valid = true;
				for (d = vect[j]; d; d = d->next) {
					if (d->val.v == ran) {
						valid = false;
						ran = std::rand() % sizeV + 1 + sizeV;
						break;
					}
				}

			}
			l_size++;

			d = new List(Route(ran,1));
			d->next = vect[j];//>?
			vect[j] = d;
		}
		l_size = 0;

	}
}


Bipartite::~Bipartite()
{
}

int Bipartite::getAmount()
{
	return 2 * sizeV + 2;
}
							
List** Bipartite::getNeighbourList()
{
	return vect;
}

int Bipartite::getK()
{
	return k;
}

void Bipartite::reset()
{
	int last = 2 * sizeV + 2;
	for (int i = sizeV+1; i < last; ++i) {
		List* begin = vect[i];
		while (begin) {
			begin->val.flow = 0;
			begin = begin->next;
		}
	}
	List* first = vect[0];
	while (first) {
		first->val.flow = 0;
		first = first->next;
	}
	
}

void Bipartite::shuffle()
{
	for (int j = 1; j <= sizeV; ++j) {
		delete vect[j];
		vect[j] = nullptr;
	}

	bool valid = false;
	int l_size = 0;
	List* d;
	for (int j = 1; j <= sizeV; ++j) {
		valid = false;
		while (l_size < i) {
			int ran = std::rand() % sizeV + sizeV + 1;

			while (!valid) {
				valid = true;
				for (d = vect[j]; d; d = d->next) {
					if (d->val.v == ran) {
						valid = false;
						ran = std::rand() % sizeV + 1 + sizeV;
						break;
					}
				}

			}
			l_size++;

			d = new List(Route(ran, 1));
			d->next = vect[j];//>?
			vect[j] = d;
		}
		l_size = 0;

	}
}

void Bipartite::print()
{
	List* first = vect[0];
	while (first) {
		printf("(%d -> %d)\n", 0, first->val.v);
		first = first->next;
	}
	printf("------\n");
	for (int j = 1; j <= sizeV; ++j) {
		List* begin = vect[j];
		while (begin) {
			printf("(%d -> %d)\n",j, begin->val.v);
			begin = begin->next;
		}
	}
	printf("------\n");
	for (int j = sizeV+1; j <= 2 * sizeV; ++j) {
		List* begin = vect[j];
		if (begin == nullptr) {
			printf("(%d has no parent)\n", j);
		}
		while (begin) {
			printf("(%d -> %d)\n", j, begin->val.v);
			begin = begin->next;
		}
	}
}
