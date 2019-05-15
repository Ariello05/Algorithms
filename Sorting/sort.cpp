#include "helper.h"
#include "sort.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

/**
	Ascending check function for selection sort
*/
bool ssCheckASC(int tab[], int j, int maxmin) {
	return tab[j] < maxmin;
}
/**
Descending check function for selection sort
*/
bool ssCheckDESC(int tab[], int j, int maxmin) {
	return tab[j] > maxmin;
}

counter_s selectSort(int tab[], int size, bool asc) {
	counter_s counter;
	counter.checks = 0;
	counter.swaps = 0;

	bool(*f)(int *tab, int j, int maxmin);

	if (asc) {
		f = &ssCheckASC;
	}
	else {
		f = &ssCheckDESC;
	}

	int key;
	int min;
	for (int i = 0; i < size - 1; ++i) {
		min = tab[i];
		key = i;
		for (int j = i + 1; j < size; ++j) {
			counter.checks++;
			//cerr << "COMPERING Index: [" << j << "] " << tab[j] << "\twith minmax: " << min << endl;
			if (f(tab, j, min)) {
				min = tab[j];
				key = j;
			}
		}

		//cerr << "--SWAPING Index: [" << i << "] " << tab[i] << "\twith key at: [" << key << "] " << tab[key] << endl;
		swap(tab, i, key);
		counter.swaps++;
		
	}

	return counter;
}

/**
	Ascending check function for insertion sort
*/
bool isCheckASC(int tab[], int j, int elem) {
	//cerr << "COMPERING Index: [" << j << "] " << tab[j] << "\t with key:" << elem << endl;

	return tab[j] > elem;
}

/**
	Descending check function for insertion sort
*/
bool isCheckDESC(int tab[], int j, int elem) {
	//cerr << "COMPERING Index: [" << j << "] " << tab[j] << "\t with key:" << elem << endl;

	return tab[j] < elem;
}


counter_s insertionSort(int tab[], int size, bool asc) {
	counter_s counter;
	counter.checks = 0;
	counter.swaps = 0;

	bool(*f)(int *tab, int j, int elem);
	if (asc) {
		f = &isCheckASC;
	}
	else {
		f = &isCheckDESC;
	}
	
	int elem;
	int j;
	for (int i = 1; i < size; ++i) {
		elem = tab[i];
		j = i - 1;

		while (j >= 0 && f(tab,j,elem)) {
			counter.checks++;
			counter.swaps++;
			//cerr << "SWITCHING Index: [" << j+1 << "] " << tab[i] << "\t from key at: [" << j << "] " << tab[j] << endl;
			tab[j + 1] = tab[j];
			--j;
		}

		//cerr << "SWITCHING Index: [" << j+1 << "] " << tab[j+1] << "\t to key " << elem << endl;
		counter.swaps++;
		tab[j + 1] = elem;
	}
	return counter;
}

/**
	Ascending check function for Heap sort
*/
bool hscheckASC(int tab[], int indexL, int maxmin) {
	return tab[indexL] > tab[maxmin];
}

/**
	Descending check function for Heap sort
*/
bool hscheckDESC(int tab[], int indexL, int maxmin) {
	return tab[indexL] < tab[maxmin];
}

void heapify(int tab[], int n, int i, counter_s & checks, bool (*f)(int *tab,int l,int r)) {
	int max = i;//max in means of ascendence / so it will be minimun is the sense of descendence
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	checks.checks += 3;//3 inner ifs

	//cerr << "COMPERING Index: [" << left << "] " << "\twith Index: [" << i << "] " << tab[i] << endl;
	if (left < n && f(tab,left,max)) {
		max = left;
	}

	//cerr << "COMPERING Index: [" << right << "] " << "\twith Index: [" << max << "] " << tab[max] << endl;
	if (right < n && f(tab,right,max)) {
		max = right;
	}

	if (max != i) {
		swap(tab, max, i);
		checks.swaps++;
		//cerr << "SWAPPING Index: [" << max << "] " << tab[max] << "\twith Index: [" << i << "] " << tab[i] << endl;

		heapify(tab, n, max, checks, f);
	}
	
}

counter_s heapSort(int tab[], int n, bool asc) {
	counter_s counter;
	counter.checks = 0;
	counter.swaps = 0;

	bool(*f)(int *, int, int);
	if (asc) {
		f = &hscheckASC;
	}
	else {
		f = &hscheckDESC;
	}

	for (int i = n / 2 - 1; i >= 0; --i) {
		heapify(tab, n, i, counter, f);
	}

	for (int i = n - 1; i >= 0; i--)
	{
		//cerr << "SWAPPING Index: [" << 0 << "] " << tab[0] << "\twith Index: [" << i << "] " << tab[i] << endl;
		swap(tab,0,i);
		counter.swaps++;
		heapify(tab, i, 0, counter, f);
	}
	return counter;
}


int partition(int tab[], int p, int r, counter_s & counter, bool(*f)(int * tab,int j,int x)) {
	int x = tab[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; ++j) {
		counter.checks++;
		//cerr << "COMPERING Index: [" << j << "] " << tab[j] << "\twith Pivot: " << x << endl;
		if (f(tab,j,x)) {
			++i;
			//cerr << "SWAPPING Index: [" << i << "] " << tab[i] << "\twith Index: [" << j << "] " << tab[j] << endl;
			swap(tab, i, j);
			counter.swaps++;
		}
	}
	//cerr << "SWAPPING Index: [" << i+1 << "] " << tab[i+1] << "\twith Pivot: " << x << endl;
	swap(tab, i + 1, r);
	counter.swaps++;
	return i + 1;
}

/**
	Ascending check function for Quick sort
*/
bool qscheckASC(int tab[], int j, int x) {
	return (tab[j] <= x);
}

/**
	Descending check function for Quick sort
*/
bool qscheckDESC(int tab[], int j, int x) {
	return (tab[j] >= x);
}


/**
	Quicksort Recursive using pointer to a function in partition
*/
void quicksortFP2(int tab[], int p, int r, counter_s &checks, bool(*f)(int * tab, int j, int x)) {
	if (p < r) {//only if beg is higher than end
		int q = partition(tab, p, r, checks, f);

		quicksortFP2(tab, p, q - 1, checks, f);
		quicksortFP2(tab, q + 1, r, checks, f);
	}
}

/**
	Quicksort interface adapter + function pointer definition
*/
counter_s quickSort(int tab[], int n, bool asc) {
	counter_s counter;
	counter.checks = 0;
	counter.swaps = 0;

	bool(*f)(int * tab, int j, int x);

	if (asc) {
		f = &qscheckASC;
	}
	else {
		f = &qscheckDESC;
	}

	int q = partition(tab, 0, n-1, counter, f);

	quicksortFP2(tab, 0, q - 1, counter, f);
	quicksortFP2(tab, q + 1, n-1, counter, f);

	return counter;
}

/**
	Median partition
*/
int partition3m(int tab[], int p, int r, counter_s & counter, bool(*f)(int * tab, int j, int x)) {

}

/**
	Modified insertion sort
	Adapter: N -> P, R
*/
void mIS(int tab[],int p, int r, counter_s & counter, bool asc) {

	bool(*f)(int *tab, int j, int elem);
	if (asc) {
		f = &isCheckASC;
	}
	else {
		f = &isCheckDESC;
	}

	int elem;
	int j;
	for (int i = p; i < r; ++i) {
		elem = tab[i];
		j = i - 1;

		while (j >= 0 && f(tab, j, elem)) {
			counter.checks++;
			counter.swaps++;
			//cerr << "SWITCHING Index: [" << j+1 << "] " << tab[i] << "\t from key at: [" << j << "] " << tab[j] << endl;
			tab[j + 1] = tab[j];
			--j;
		}

		//cerr << "SWITCHING Index: [" << j+1 << "] " << tab[j+1] << "\t to key " << elem << endl;
		counter.swaps++;
		tab[j + 1] = elem;
	}
}

/**
	Modified quick sort
*/
void mQS(int tab[], int p, int r, counter_s &checks, bool(*f)(int * tab, int j, int x), bool asc) {
	if (r - p <= 16) {
		mIS(tab, p, r, checks, asc);
	}
	else {
		int q = partition3m(tab,p,r,counter,f);
	}
}


counter_s modifiedQuickSort(int tab[], int n, bool asc) {
	counter_s checks;
	checks.checks = 0;
	checks.swaps = 0;

	bool(*f)(int * tab, int j, int x);
	if (asc) {
		f = &qscheckASC;
	}
	else {
		f = &qscheckDESC;
	}
	mQS(tab, 0, n - 1, checks, f, asc);
	return checks;
}