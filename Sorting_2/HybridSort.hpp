#pragma once
#include "ISort.hpp"
#include <string>
#include <iostream>
#include "InsertionSort.hpp"

using std::cerr;
using std::endl;


template <typename T>
/**
	Hybrid sort uses QuickSort with InsertionSort.
	QuickSort for threshold of > 8, otherwise use InsertionSort.
*/
class HybridSort :public ISort<T> {
public:
	HybridSort(bool asc = true, bool log = false);
private:

	virtual counter_s runSort(T tab[], int size);
	int partition(T tab[], int begin, int end, counter_s& counter);

	bool compare(T tab[], int j, int x);
	void hybridSort(T tab[], int p, int r, counter_s& checks);

	bool qsCheckASC(T tab[], int j, int x);
	bool qsCheckDESC(T tab[], int j, int x);

};

template<typename T>
inline HybridSort<T>::HybridSort(bool asc, bool log)
	:ISort<T>(asc, log)
{
}

template<typename T>
inline counter_s HybridSort<T>::runSort(T tab[], int size)
{
	counter_s counter;
	counter.checks = 0;
	counter.swaps = 0;

	hybridSort(tab, 0, size - 1, counter);

	return counter;
}

template<typename T>
inline int HybridSort<T>::partition(T tab[], int begin, int end, counter_s& counter) {
	int x = tab[end];
	int i = begin - 1;
	for (int j = begin; j <= end - 1; ++j) {
		counter.checks++;
		if (this->log) { cerr << Help::COMPARE << "Index: [" << j << "] " << tab[j] << "\t WITH \t Pivot: " << x << endl; }
		if (compare(tab, j, x)) {
			++i;
			if (this->log) { cerr << Help::SWAP << "Index: [" << i << "] " << tab[i] << "\t WITH \t Index: [" << j << "] " << tab[j] << endl; }
			Help::swap(tab, i, j);
			counter.swaps++;
		}
	}
	if (this->log) { cerr << Help::SWAP << "Index: [" << i + 1 << "] " << tab[i + 1] << "\t WITH \t Pivot: " << x << endl; }
	Help::swap(tab, i + 1, end);
	counter.swaps++;
	return i + 1;
}

template<typename T>
inline bool HybridSort<T>::compare(T tab[], int j, int x)
{
	if (this->asc) {
		return qsCheckASC(tab, j, x);
	}
	else {
		return qsCheckDESC(tab, j, x);
	}
}

template<typename T>
inline void HybridSort<T>::hybridSort(T tab[], int begin, int end, counter_s& checks)
{
	if (end - begin <= 8) {
		InsertionSort<T> sorter(this->asc, this->log);
		sorter.partial_sort(tab, begin, end, checks);
		return;
	}
	if (begin < end) {//only if beg is higher than end
		int q = partition(tab, begin, end, checks);

		hybridSort(tab, begin, q - 1, checks);
		hybridSort(tab, q + 1, end, checks);
	}
}

template<typename T>
inline bool HybridSort<T>::qsCheckASC(T tab[], int j, int x)
{
	return (tab[j] <= x);
}

template<typename T>
inline bool HybridSort<T>::qsCheckDESC(T tab[], int j, int x)
{
	return (tab[j] >= x);
}
