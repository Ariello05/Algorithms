#include <iostream>
#include "helper.h"

using std::cout;
using std::endl;

int partitionASC(int tab[], int p, int r, int & checks) {
	int x = tab[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; ++j) {
		checks += 2;//if + for
		cout << "COMPERING Index: " << j << " [" << tab[j] << "]\twith Pivot: " << x << endl;
		if (tab[j] <= x) {
			++i;
			cout << "SWAPPING Index: " << i << " [" << tab[i] << "]\twith Index: " << j << " [" << tab[j] << "]" << endl;
			swap(tab, i, j);
		}
	}
	swap(tab, i + 1, r);
	return i + 1;
}

int partitionDESC(int tab[], int p, int r, int & checks) {
	int x = tab[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; ++j) {
		checks += 2;//if + for
		cout << "COMPERING Index: " << j << " [" << tab[j] << "]\twith Pivot: " << x << endl;
		if (tab[j] >= x) {
			++i;
			cout << "SWAPPING Index: " << i << " [" << tab[i] << "]\twith Index: " << j << " [" << tab[j] << "]" << endl;
			swap(tab, i, j);
		}
	}
	swap(tab, i + 1, r);
	return i + 1;
}

int partition(int tab[], int p, int r, int & checks, bool asc) {
	if (asc) {
		return partitionASC(tab, p, r, checks);
	}
	else {
		return partitionDESC(tab, p, r, checks);
	}
}

/**
Quicksort Recursive
*/
void quicksortR(int tab[], int p, int r, int & checks, bool asc) {
	if (p < r) {//only if beg is higher than end
		int q = partition(tab, p, r, checks, asc);

		quicksortR(tab, p, q - 1, checks, asc);
		quicksortR(tab, q + 1, r, checks, asc);
	}
}

/**
Quicksort Recursive using pointer to a function in place of partition
*/
void quicksortFP(int tab[], int p, int r, int &checks, int(*f)(int *, int, int, int &)) {
	if (p < r) {//only if beg is higher than end
		int q = f(tab, p, r, checks);

		quicksortFP(tab, p, q - 1, checks, f);
		quicksortFP(tab, q + 1, r, checks, f);
	}
}