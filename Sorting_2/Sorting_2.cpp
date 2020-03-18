#include <ctime>
#include <chrono>
#include <time.h>
#include <random>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>

#include "InsertionSort.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include "CountQuickSort.hpp"
#include "HybridSort.hpp"

using std::cout;
using std::endl;
using std::rand;
using std::cerr;
using std::cin;

int main(int argc, char* agrv[]) {
	if (argc <= 2) {
		cerr << "(--type insert|merge|quick|count|hybrid --asc|--desc) | (--stat nazwapliku)";
		return 0;
	}

	if (Help::contains(agrv[1], "--type")) {
		if (argc <= 3) {
			cerr << "Not enough param need --asc|--desc";
			return 0;
		}
		bool asc;
		if (Help::contains(agrv[3], "--asc")) {
			asc = true;
		}
		else if (Help::contains(agrv[3], "--desc")) {
			asc = false;
		}
		else {
			cerr << "Unkown third argument namely: " << agrv[3] << "\t suspected --asc|--desc" << endl;
			return 0;
		}

		int n;
		cout << "Type size: ";
		cin >> n;
		cout << "Type list: ";
		int* tab = new int[n];
		for (int i = 0; i < n; ++i) {
			cin >> tab[i];
		}

		counter_s licznik;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();//c++11
		ISort<int>* sorter;
		if (Help::contains(agrv[2], "insert")){
			sorter = new InsertionSort<int>(asc,true);
			licznik = sorter->sort(tab, n, asc);
		}
		else if (Help::contains(agrv[2], "merge")) {
			sorter = new MergeSort<int>(asc, true);
			licznik = sorter->sort(tab, n, asc);
		}
		else if (Help::contains(agrv[2], "quick")) {
			sorter = new QuickSort<int>(asc, true);
			licznik = sorter->sort(tab, n, asc);
		}
		else if (Help::contains(agrv[2], "count")) {
			sorter = new CountQuickSort<int>(asc, true);
			licznik = sorter->sort(tab, n, asc);
		}
		else if (Help::contains(agrv[2], "hybrid")) {
			sorter = new HybridSort<int>(asc, true);
			licznik = sorter->sort(tab, n, asc);
		}
		else {
			cerr << "Unkown second argument namely: " << agrv[3] << "\t suspected insert|heap|quick|count|hybrid" << endl;
			return 0;
		}
		delete sorter;
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

		cout << "Compares:" << licznik.checks << "\tSwaps:" << licznik.swaps << "\tElapsed Time(ms):" << elapsed << endl;
		//Help::printArray(tab, n);
		if (!Help::isSorted(tab, n, asc)) {
			cout << "ARRAY NOT SORTED" << endl;
			return 0;
		}
		Help::printArray(tab, n);

		cin >> n;

	}
	else if (Help::contains(agrv[1], "--stat")) {
		if (argc <= 3) {
			cerr << "Not enough param need: nazwapliku k";
			return 0;
		}
		std::string filename = agrv[2];
		std::ofstream file(filename);
		if (file.bad()) {
			cerr << "Unkown file error!";
			return 0;
		}
		int k;
		try {
			k = std::stoi(agrv[3]);
		}
		catch (std::invalid_argument) {
			cerr << "Unkown third argument namely: " << agrv[3] << "\tsuspected integer" << endl;
			return 0;
		}

		const int algsSize = 5;

		int* tab[algsSize];//data

		counter_s counters[algsSize];//swaps sounts
		double times[algsSize];//timer
		counter_s countersAVG[algsSize];
		double timesAVG[algsSize];
		clock_t begin;
		clock_t end;
		file << "N [I]Compares Swaps Time [M]Compares Swaps Time [Q]Compares Swaps Time [C]Compares Swaps Time [H]Compares Swwaps Time\n";
		//std::chrono::steady_clock::time_point begin;//timer
		//std::chrono::steady_clock::time_point end;
		srand(time(0));
		for (int n = 100; n <= 10000; n += 100) {

			for (int i = 0; i < algsSize; ++i) {
				tab[i] = new int[n];
				timesAVG[i] = 0;
				countersAVG[i].checks = 0;
				countersAVG[i].swaps = 0;
			}
			InsertionSort<int> insertionSorter(true,false);
			MergeSort<int> mergeSorter(true, false);
			QuickSort<int> quickSorter(true, false);
			CountQuickSort<int> quickCountSorter(true, false);
			HybridSort<int> hybridSorter(true, false);

			for (int i = 0; i < k; ++i) {
				Help::generate(tab[0], n, 0, 10000);
				for (int i = 1; i < algsSize; ++i) {
					Help::copyArray(tab[0], tab[i], n);
				}

				begin = clock();
				counters[0] = insertionSorter.sort(tab[0], n, true);
				end = clock();
				times[0] = double(end - begin) / CLOCKS_PER_SEC;

				begin = clock();
				counters[1] = mergeSorter.sort(tab[1], n, true);
				end = clock();
				times[1] = double(end - begin) / CLOCKS_PER_SEC;

				begin = clock();
				counters[2] = quickSorter.sort(tab[2], n, true);
				end = clock();
				times[2] = double(end - begin) / CLOCKS_PER_SEC;

				begin = clock();
				counters[3] = quickCountSorter.sort(tab[3], n, true);
				end = clock();
				times[3] = double(end - begin) / CLOCKS_PER_SEC;

				begin = clock();
				counters[4] = hybridSorter.sort(tab[4], n, true);
				end = clock();
				times[4] = double(end - begin) / CLOCKS_PER_SEC;

				for (int i = 0; i < algsSize; ++i) {//add to average
					timesAVG[i] += times[i];
					countersAVG[i].checks += counters[i].checks;
					countersAVG[i].swaps += counters[i].swaps;
				}

			}

			for (int i = 0; i < algsSize; ++i) {
				timesAVG[i] = timesAVG[i] / k;//arithmetic average
				countersAVG[i].checks += counters[i].checks / k;
				countersAVG[i].swaps += counters[i].swaps / k;
				delete[] tab[i];
			}

			cout << n << endl;

			file << n << " ";
			for (int i = 0; i < algsSize; ++i) {
				file << countersAVG[i].checks << " " << countersAVG[i].swaps << " " << timesAVG[i] << " ";
			}
			file << '\n';

		}

	}
	else {
		cerr << "Unkown first argument namely: " << agrv[1] << "\tsuspected --type | --stat" << endl;
		return 0;
	}

}
