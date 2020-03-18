#pragma once
#include "ISort.hpp"
using std::cerr;
using std::endl;


template <typename T>
class InsertionSort:public ISort<T> {
public:
	InsertionSort(bool asc = true, bool log = false);
	void partial_sort(T tab[], int p, int q, counter_s& counter);

private:

	virtual counter_s runSort(T tab[], int size);

	bool compare(T tab[], int j, int i);

	bool isCheckASC(T tab[], int j, int i);
	bool isCheckDESC(T tab[], int j, int i);

};

template<typename T>
inline InsertionSort<T>::InsertionSort(bool asc, bool log)
	:ISort<T>(asc,log)
{
}

template<typename T>
inline counter_s InsertionSort<T>::runSort(T tab[], int size)
{
	counter_s counter;
	counter.checks = 0;
	counter.swaps = 0;
 
	T elem;
	int j;
	for (int i = 1; i < size; ++i) {
		elem = tab[i];
		j = i - 1;

		while (j >= 0 && compare(tab,j,elem)) {
			counter.checks++;
			counter.swaps++;
			if (this->log) { cerr << Help::SET << "Index: [" << j + 1 << "]= " << tab[j + 1] << "\t TO \t 'previous' key at: [" << j << "]= " << tab[j] << endl; }
			tab[j + 1] = tab[j];
			--j;
		}

		if (this->log) { cerr << Help::SET << "Index: [" << j + 1 << "]= " << tab[j + 1] << "\t TO \t key of value=" << elem << endl; }
		counter.swaps++;
		tab[j + 1] = elem;
	}
	return counter;
}

template<typename T>
inline void InsertionSort<T>::partial_sort(T tab[], int p, int q, counter_s & counter)
{
	T elem;
	int j;
	for (int i = p+1; i <= q; ++i) {
		elem = tab[i];
		j = i - 1;

		while (j >= p && compare(tab, j, elem)) {
			counter.checks++;
			counter.swaps++;
			if (this->log) { cerr << Help::SET << "Index: [" << j + 1 << "]= " << tab[j + 1] << "\t TO \t 'previous' key at: [" << j << "]= " << tab[j] << endl; }
			tab[j + 1] = tab[j];
			--j;
		}

		if (this->log) { cerr << Help::SET << "Index: [" << j + 1 << "]= " << tab[j + 1] << "\t TO \t key of value=" << elem << endl; }
		counter.swaps++;
		tab[j + 1] = elem;
	}
}

template<typename T>
inline bool InsertionSort<T>::compare(T tab[], int j, int elem)
{
	if (this->asc) {
		return isCheckASC(tab,j, elem);
	}
	else {
		return isCheckDESC(tab, j, elem);
	}
}


template<typename T>
inline bool InsertionSort<T>::isCheckASC(T tab[], int j, int elem)
{
	if (this->log) { cerr << Help::COMPARE<<"Index: [" << j << "]= " << tab[j] << "\t WITH \t value="<< elem << endl; }

	return tab[j] > elem;
}

template<typename T>
inline bool InsertionSort<T>::isCheckDESC(T tab[], int j, int elem)
{
	if (this->log) { cerr << Help::COMPARE<<"Index: [" << j << "]= " << tab[j] << "\t WITH \t value=" << elem << endl; }

	return tab[j] < elem;
}

