#include "RadixSort.hpp"

int old_main() {
	const bool asc = true;
	auto radix_sort = RadixSort(asc);
	const int n = 1000;
	int tab[n];
	Help::generate(tab, n, -10000, 10000);
	radix_sort.sort(tab, n);
	if (!Help::isSorted(tab, n, asc)) {
		cout << "ARRAY NOT SORTED" << endl;
		return 0;
	}
	else {
		Help::printArray(tab, n);
	}
}