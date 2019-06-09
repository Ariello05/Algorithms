#include "HyperCube.h"
#include <utility>
#include <random>
#include <time.h>

int getH(int x) {
	unsigned int c; // c accumulates the total bits set in v
	for (c = 0; x; c++)
	{
		x &= x - 1; // clear the least significant bit set
	}
	return c;
}

int next(int initial, int current) {
	if (initial >= current) {//if inital is higher than current
		current = initial;

		int i = 0;
		bool flag = false;
		while (true) {
			if ((current & (1 << i)) == 0) {
				return current | (1 << i);// pretty much adds bit one to the first place avaible in initial
			}
			++i;
		}
	}

	int buff = ~initial;
	current = current & buff;//get rid of initial bits
	buff = current;
	int i = 1;
	do {//find first place where initial is not current
		current = buff;
		current = current << i++;
		current = current | initial;
	} while (initial == current);

	return current;
}

HyperCube::HyperCube(unsigned int k)
{
	lastVertice = pow(2, k);
	vect = new List*[lastVertice];
	for (int i = 0; i < lastVertice; ++i) {
		vect[i] = nullptr;
	}

	this->k = k;
	std::pair<int, int> pair;

	for (int i = 0; i < lastVertice; ++i) {
		int op = getH(i);
	
		//cout << "op: " << op << endl;

		for (int s = getH(i); s < k; ++s) {
			pair.first = i;
			op = next(i, op);
			pair.second = op;
			addEdge(pair.first, pair.second);
		}
	}
}

HyperCube::~HyperCube()
{
	for (int i = 0; i < lastVertice; ++i) {
		delete vect[i];
	}
	delete[] vect;
}

void HyperCube::print()
{
	printf("Pair(u,v,cap)\n");
	int last = pow(2, k);
	for (int i = 0; i < last; ++i) {
		List* begin = vect[i];
		while (begin) {
			printf("Pair(%d,%d,%d)\n", i, begin->val.v, begin->val.capacity);
			begin = begin->next;
		}
	}
}

int HyperCube::getAmount()
{
	return lastVertice;
}

List** HyperCube::getNeighbourList()
{
	return vect;
}

int HyperCube::getK()
{
	return k;
}

/**
	Resets flows
*/
void HyperCube::reset()
{
	int last = pow(2, k);
	for (int i = 0; i < last; ++i) {
		List* begin = vect[i];
		while (begin) {
			begin->val.flow = 0;
			begin = begin->next;
		}
	}
}

/**
	Shuffles capacity
*/
void HyperCube::shuffle()
{
	int last = pow(2, k);
	for (int i = 0; i < last; ++i) {
		List* begin = vect[i];
		while (begin) {
			if (begin->val.v <= i) {//No need to shuffle capacity of backRoute it should stay 0
				begin = begin->next;
				continue;
			}

			int a1 = getH(i);
			int a2 = k - a1;//Z
			if (a2 > a1) {
				a1 = a2;//a1 is max
			}
			int b1 = getH(begin->val.v);
			int b2 = k - b1;//Z
			if (b1 > a1) {
				a1 = b1;
			}
			if (b2 > a1) {
				a1 = b2;
			}
			int max = pow(2, a1);
			int rand = std::rand() % max + 1;
			begin->val.capacity = rand;
			begin = begin->next;
		}
	}
}


void HyperCube::addEdge(int u, int v)//numeric values
{
	int a1 = getH(u);
	int a2 = k - a1;//Z
	if (a2 > a1) {
		a1 = a2;//a1 is max
	}
	int b1 = getH(v);
	int b2 = k - b1;//Z
	if (b1 > a1) {
		a1 = b1;
	}
	if (b2 > a1) {
		a1 = b2;
	}
	int max = pow(2, a1);
	int rand = std::rand() % max + 1;
	Route r(v, rand);
	List* el = new List(r);
	el->next = vect[u];
	vect[u] = el;
}
