#pragma once
#include "ISort.hpp"
#include <string>
#include <iostream>
#include "Helper.hpp"
#include "InsertionSort.hpp"
using std::cerr;
using std::endl;

class Pivots {
public:
	Pivots(int pos_p, int pos_q) {
		this->pos_p = pos_p;
		this->pos_q = pos_q;
	}

	int pos_p;
	int pos_q;
};

template <typename T>
class CountQuickSort :public ISort<T> {
public:
	CountQuickSort(bool asc = true, bool log = false);
private:

	virtual counter_s runSort(T tab[], int size);
	Pivots partition(T tab[], int p, int q, int begin, int end, counter_s& counter);

	void rotate3(T tab[], int a, int b, int c);
	bool compare(T tab[], int j, int x);
	void quickSort(T tab[], int p, int r, counter_s& checks);

	bool qsCheckASC(T tab[], int j, int x);
	bool qsCheckDESC(T tab[], int j, int x);

};

template<typename T>
inline CountQuickSort<T>::CountQuickSort(bool asc, bool log)
	:ISort<T>(asc, log)
{

}

template<typename T>
inline counter_s CountQuickSort<T>::runSort(T tab[], int size)
{
	counter_s counter;
	counter.checks = 0;
	counter.swaps = 0;

	quickSort(tab, 0, size - 1, counter);
	if (!this->asc) {
		for (int i = 0; i < size / 2; ++i) {
			Help::swap(tab, i, (size-1) - i);
		}
	}

	return counter;
}

template<typename T>
inline Pivots CountQuickSort<T>::partition(T tab[], int p, int q, int begin, int end, counter_s& counter)
{
	int i = begin + 1;
	int k = end - 1;
	int j = i;
	int d = 0;// holds the difference of the number of small and large elements.

	while (j <= k){
		counter.checks++;
		if (this->log) { cerr << Help::COMPARE << "\td:" << d << "\t > \t" << 0 << endl; }
		if (d > 0) {
			counter.checks++;
			if (this->log) { cerr << Help::COMPARE << "tab[" << j  << "]:" << tab[j] << "\t < \t" << "p:" << p << endl; }
			if (tab[j] < p) {
				if (this->log) { cerr << Help::SWAP << "tab[" << i << "]:" << tab[i] << "\t WITH \t" << "tab[" << j << "]:" << tab[j] << endl; }
				Help::swap(tab, i, j);
				counter.swaps++;
				i++;
				j++;
				d++;
			}
			else {
				counter.checks++;
				if (this->log) { cerr << Help::COMPARE << "tab[" << j << "]:" << tab[j] << "\t < \t" << "q:" << q << endl; }
				if (tab[j] < q) {
					j++;
				}
				else {
					counter.swaps++;
					if (this->log) { cerr << Help::SWAP << "tab[" << j << "]:" << tab[j] << "\t WITH \t" << "tab[" << k << "]:" << tab[k] << endl; }
					Help::swap(tab, j, k);
					k--;
					d--;
				}

			}
		}
		else {
			if (this->log) { cerr << Help::COMPARE << "tab[" << k << "]:" << tab[k] << "\t > \t" << "q:" << q << endl; }
			while (tab[k] > q) {
				counter.checks++;
				k--;
				d--;
				if (this->log) { cerr << Help::COMPARE << "tab[" << k << "]:" << tab[k] << "\t > \t" << "q:" << q << endl; }
			}
			counter.checks++;
			if (this->log) { cerr << Help::COMPARE << "\tj:" << j << "\t <= \t" << "k:" << k << endl; }
			if (j <= k) {
				counter.checks++;

				if (this->log) { cerr << Help::COMPARE << "tab[" << k << "]:" << tab[k] << "\t < \t" << "p:" << p << endl; }
				if (tab[k] < p) {
					counter.swaps += 2;
					if (this->log) { cerr << Help::SET << "tab[" << k << "]:" << tab[k] << "\t TO \t" << "tab[" << j << "]:" << tab[j] << endl; }
					if (this->log) { cerr << Help::SET << "tab[" << j << "]:" << tab[j] << "\t TO \t" << "tab[" << i << "]:" << tab[i] << endl; }
					if (this->log) { cerr << Help::SET << "tab[" << i << "]:" << tab[i] << "\t TO \t" << "tab[" << k << "]:" << tab[k] << endl; }

					rotate3(tab, k, j, i);
					i++;
					d++;
				}
				else {
					counter.swaps++;
					if (this->log) { cerr << Help::SWAP << "tab[" << j << "]:" << tab[j] << "\t WITH \t" << "tab[" << k << "]:" << tab[k] << endl; }
					Help::swap(tab, j, k);
				}
				j++;
			}
		}

	}
	if (this->log) { cerr << Help::SWAP << "tab[" << begin << "]:" << tab[begin] << "\t WITH \t" << "tab[" << i-1 << "]:" << tab[i-1] << endl; }
	Help::swap(tab, begin, i - 1);
	if (this->log) { cerr << Help::SWAP << "tab[" << end << "]:" << tab[end] << "\t WITH \t" << "tab[" << k+1 << "]:" << tab[k+1] << endl; }
	Help::swap(tab, end, k + 1);
	counter.swaps += 2;
	return Pivots(i - 1, k + 1);
}

template<typename T>
inline void CountQuickSort<T>::rotate3(T tab[], int a, int b, int c)
{
	auto temp = tab[a];
	tab[a] = tab[b];
	tab[b] = tab[c];
	tab[c] = temp;
}

template<typename T>
inline bool CountQuickSort<T>::compare(T tab[], int j, int x)
{
	if (this->asc) {
		return qsCheckASC(tab, j, x);
	}
	else {
		return qsCheckDESC(tab, j, x);
	}
}

template<typename T>
inline void CountQuickSort<T>::quickSort(T tab[], int begin, int end, counter_s& checks)
{
	//if (end - begin <= 4) {
	//	InsertionSort<T> sorter(this->asc, this->log);
	//	sorter.partial_sort(tab, begin, end, checks);
	//	return;
	//}

	if (begin >= end) {
		return;
	}

	checks.checks++;
	if (this->log) { cerr << Help::COMPARE << "tab[" << end << "]:" << tab[end] << "\t < \t" << "tab[" << begin << "]:" << tab[begin] << endl; }
	if (tab[end] < tab[begin]) {
		checks.swaps++;
		if (this->log) { cerr << Help::SWAP << "tab[" << begin << "]:" << tab[begin] << "\t WITH \t" << "tab[" << end << "]:" << tab[end] << endl; }
		Help::swap(tab, begin, end);
	}
	auto p = tab[begin];
	auto q = tab[end];

	//std::cout << "PRE PART\n";
	//Help::printArray(tab, begin, end);
	Pivots piv = partition(tab,p,q, begin, end, checks);
	//std::cout << "POST PART\n";
	//Help::printArray(tab, begin, end);

	//std::cout << "(begin,end,p,q): " << begin << '\t' << end << '\t' << piv.pos_p << '\t' << piv.pos_q << std::endl;

	quickSort(tab, begin, piv.pos_p-1, checks);
	quickSort(tab, piv.pos_p + 1, piv.pos_q-1, checks);
	quickSort(tab, piv.pos_q + 1, end, checks);
}

template<typename T>
inline bool CountQuickSort<T>::qsCheckASC(T tab[], int j, int x)
{
	return (tab[j] <= x);
}

template<typename T>
inline bool CountQuickSort<T>::qsCheckDESC(T tab[], int j, int x)
{
	return (tab[j] >= x);
}
