#pragma once
#include "ISort.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <math.h>



using std::cerr;
using std::endl;
using std::cout;

class DigitizedNumber {
public:
	DigitizedNumber(int num) {
		minus = (num < 0) ? true : false;

		digits = std::vector<int>();
		digits.push_back(num % 10);
		while (std::abs(num / 10) > 0) {
			num /= 10;
			digits.push_back(num % 10);
		}
	}

	int length() {
		return digits.size();
	}

	operator int() {
		int num = 0;
		int mn = 1;
		for (int i = 0; i < digits.size(); ++i) {
			num += digits[i] * mn;
			mn *= 10;
		}
		//num /= 10;
		return num;
	}

	int operator[](int position) {
		if (position >= digits.size()) {
			return 0;
		}
		else {
			if (minus)
				return -digits[position];
			else
				return digits[position];
		}
	}

private:
	std::vector<int> digits;
	bool minus;
};

// only INT
// LSD
class RadixSort :public ISort<int> {
public:
	RadixSort(bool asc = true, bool log = false);
private:
	//std::vector<int> xd;
	//std::vector<DigitizedNumber> numbers;
	std::vector<DigitizedNumber> buckets[10];
	virtual counter_s runSort(int tab[], int size);
};

inline RadixSort::RadixSort(bool asc, bool log)
	:ISort<int>(asc, log)
{
}

inline counter_s RadixSort::runSort(int tab[], int size)
{
	counter_s counter;
	counter.checks = 0;
	counter.swaps = 0;
	int max_size = 0; //aka our k
	for (int i = 0; i < size; ++i) {
		DigitizedNumber dn = DigitizedNumber(tab[i]);
		buckets[dn[0]].push_back(dn);
		counter.swaps++;
		if (dn.length() > max_size) {
			max_size = dn.length();
		}
	}
	
	#ifdef _WIN32
		if (max_size <= 1) {//At this point we will be using most of the memory, so we check here...
			PROCESS_MEMORY_COUNTERS_EX pmc;
			GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)& pmc, sizeof(pmc));
			SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
			//SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
			counter.memory = virtualMemUsedByMe;
			//_tprintf(TEXT("There is  %*ld %% of memory in use.\n"),
			//	7, physMemUsedByMe);
		}
	#endif

	for (int i = 1; i < max_size; ++i) {
		std::vector<DigitizedNumber> newBuckets[10];
		for (int j = 0; j < 10; ++j) {
			for (DigitizedNumber& el : buckets[j]) {
				newBuckets[el[i]].push_back(el);
				counter.swaps++;
			}
		}
		for (int j = 0; j < 10; ++j) {

			#ifdef _WIN32
				if (i == 1) {//At this point we will be using most of the memory, so we check here...
					PROCESS_MEMORY_COUNTERS_EX pmc;
					GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)& pmc, sizeof(pmc));
					SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
					SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
					counter.memory = physMemUsedByMe;
					//_tprintf(TEXT("There is  %*ld %% of memory in use.\n"),
					//	7, physMemUsedByMe);
				}
			#endif

			buckets[j] = std::move(newBuckets[j]);
			counter.swaps++;
		}
	}
	int i = 0;
	int k = size;
	
	while (i < k){ //Insert back into tab
		for (int j = 9; j >= 0; --j) {
			auto begin = buckets[j].rbegin();
			for (; begin != buckets[j].rend(); ++begin) {
				int val = *begin;
				if (val < 0) {//workaround for negative numbers
					if (asc) {
						tab[i++] = val;
					}
					else {
						tab[k - 1] = val;
						k--;
					}
				}
				else {
					if (asc) {
						tab[k - 1] = val;
						k--;
					}
					else {
						tab[i++] = val;
					}
				}
				counter.swaps++;
			}
		}
	}
	for (auto& el : buckets) {//cleanup
		el.clear();
	}
	buckets->clear();

	return counter;
}