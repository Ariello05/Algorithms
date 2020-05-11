#include <ctime>
#include <chrono>
#include <time.h>
#include <random>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#endif


#include "InsertionSort.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include "CountQuickSort.hpp"
#include "RadixSort.hpp"

using std::string;
using std::cout;
using std::endl;
using std::rand;
using std::cerr;
using std::cin;

template<typename T>
void runTask_1(int n, char* agrv[], bool asc) {
	cout << "Type list: ";
	T* tab = new T[n];
	for (int i = 0; i < n; ++i) {
		cin >> tab[i];
	}

	counter_s licznik;
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();//c++11
	ISort<T>* sorter;
	if (Help::contains(agrv[2], "insert")) {
		sorter = new InsertionSort<T>(asc, true);
		licznik = sorter->sort(tab, n, asc);
	}
	else if (Help::contains(agrv[2], "merge")) {
		sorter = new MergeSort<T>(asc, true);
		licznik = sorter->sort(tab, n, asc);
	}
	else if (Help::contains(agrv[2], "quick")) {
		sorter = new QuickSort<T>(asc, true);
		licznik = sorter->sort(tab, n, asc);
	}
	else if (Help::contains(agrv[2], "count")) {
		sorter = new CountQuickSort<T>(asc, true);
		licznik = sorter->sort(tab, n, asc);
	}
	else if (Help::contains(agrv[2], "radix")) {
		cerr << "Can't run radix for this Type!" << endl;
		return;
	}
	else {
		cerr << "Unkown second argument namely: " << agrv[3] << "\t suspected insert|heap|quick|count|radix" << endl;
		return;
	}
	delete sorter;
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	cout << "\n Compares:" << licznik.checks << "\tSwaps:" << licznik.swaps << "\tElapsed Time(ms):" << elapsed << endl;
	//Help::printArray(tab, n);
	if (!Help::isSorted(tab, n, asc)) {
		cout << "ARRAY NOT SORTED" << endl;
		return ;
	}
	Help::printArray(tab, n);
}

template <>
void runTask_1<int>(int n, char* agrv[], bool asc) {
	cout << "Type list: ";
	int* tab = new int[n];
	for (int i = 0; i < n; ++i) {
		cin >> tab[i];
	}

	counter_s licznik;
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();//c++11
	ISort<int>* sorter;
	if (Help::contains(agrv[2], "insert")) {
		sorter = new InsertionSort<int>(asc, true);
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
	else if (Help::contains(agrv[2], "radix")) {
		sorter = new RadixSort(asc, true);
		licznik = sorter->sort(tab, n, asc);
	}
	else {
		cerr << "Unkown second argument namely: " << agrv[3] << "\t suspected insert|heap|quick|count|radix" << endl;
		return;
	}
	delete sorter;
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

		#ifdef _WIN32
			cout << "\n Compares:" << licznik.checks << "\tSwaps:" << licznik.swaps << "\tElapsed Time(ms):" << elapsed << "\tMemory used:" << licznik.memory/8192 << " KB" << endl;
		#else
			cout << "\n Compares:" << licznik.checks << "\tSwaps:" << licznik.swaps << "\tElapsed Time(ms):" << elapsed << endl;
			cout << "\n Used memory info available only on WIN32" << endl;
		#endif

	//Help::printArray(tab, n);
	if (!Help::isSorted(tab, n, asc)) {
		cout << "ARRAY NOT SORTED" << endl;
		return;
	}
	Help::printArray(tab, n);
}

int main(int argc, char* agrv[]) {
	if (argc <= 3) {
		cerr << "(--type insert|merge|quick|count|radix --comp '>='|'<=') | (--stat nazwapliku k) | --radixTest nazwapliku";
		system("pause");
		return 0;
	}

	if (Help::contains(agrv[1], "--type")) {
		if (argc <= 4) {
			cerr << "Not enough param need --comp '>='|'<='";
			system("pause");
			return 0;
		}
		bool asc;
		if (!Help::contains(agrv[3], "--comp")) {
			cerr << "Expected --comp...\n";
			system("pause");
			return 0;
		}

		string str = agrv[4];

		if (Help::contains(str, "<=")) {
			asc = true;
		}
		else if (Help::contains(str, ">=")) {
			asc = false;
		}
		else {
			cerr << "Unkown fourth argument namely: " << str << "\t suspected '>='|'<='" << endl;
			system("pause");
			return 0;
		}

		int n;
		cout << "Type list size: ";
		cin >> n;

		cout << "Select list type: int|double|string: ";
		string type;
		cin >> type;

		if (Help::contains(type, "double")) {
			runTask_1<double>(n,agrv,asc);
		}
		else if (Help::contains(type, "int")) {
			runTask_1<int>(n, agrv, asc);
		}
		else if (Help::contains(type, "string")) {
			runTask_1<string>(n, agrv, asc);
		}
		else {
			cout << "Deducted int ... \n";
			runTask_1<int>(n, agrv, asc);
		}

		system("pause");

	}
	else if (Help::contains(agrv[1], "--stat")) {
		if (argc <= 3) {
			cerr << "Not enough param need: nazwapliku k";
			system("pause");
			return 0;
		}
		std::string filename = agrv[2];
		std::ofstream file(filename);
		if (file.bad()) {
			cerr << "Unkown file error!";
			system("pause");
			return 0;
		}
		int k;
		try {
			k = std::stoi(agrv[3]);
		}
		catch (std::invalid_argument) {
			cerr << "Unkown third argument namely: " << agrv[3] << "\tsuspected integer" << endl;
			system("pause");
			return 0;
		}


#ifdef _WIN32

#else
		cout << "\n --stat available only on Win 32" << endl;
		return;
#endif

		const int algsSize = 3;

		int* tab[algsSize];//data

		counter_s counters[algsSize];//swaps sounts
		double times[algsSize];//timer
		counter_s countersAVG[algsSize];
		double timesAVG[algsSize];
		size_t memAVG[algsSize];
		clock_t begin;
		clock_t end;
		file << "N [I]Compares Swaps Time Memory [Q]Compares Swaps Time Memory [R]Compares Swaps Time Memory\n";
		//std::chrono::steady_clock::time_point begin;//timer
		//std::chrono::steady_clock::time_point end;
		srand(time(0));

		for (int n = 100; n <= 10000; n += 100) {

			for (int i = 0; i < algsSize; ++i) {
				tab[i] = new int[n];
				timesAVG[i] = 0;
				countersAVG[i].checks = 0;
				countersAVG[i].swaps = 0;
				memAVG[i] = 0;
			}
			InsertionSort<int> insertionSorter(true,false);
			//MergeSort<int> mergeSorter(true, false);
			QuickSort<int> quickSorter(true, false);
			//CountQuickSort<int> quickCountSorter(true, false);
			RadixSort radixSorter(true, false);
			for (int i = 0; i < k; ++i) {
				Help::generate(tab[0], n, 0, 10000);
				for (int i = 1; i < algsSize; ++i) {
					Help::copyArray(tab[0], tab[i], n);
				}

				begin = clock();
				counters[0] = insertionSorter.sort(tab[0], n, true);
				end = clock();
				times[0] = double(end - begin) / CLOCKS_PER_SEC;

				//begin = clock();
				//counters[1] = mergeSorter.sort(tab[1], n, true);
				//end = clock();
				//times[1] = double(end - begin) / CLOCKS_PER_SEC;

				begin = clock();
				counters[1] = quickSorter.sort(tab[1], n, true);
				end = clock();
				times[1] = double(end - begin) / CLOCKS_PER_SEC;

				//begin = clock();
				//counters[3] = quickCountSorter.sort(tab[3], n, true);
				//end = clock();
				//times[3] = double(end - begin) / CLOCKS_PER_SEC;

				begin = clock();
				counters[2] = radixSorter.sort(tab[2], n, true);
				end = clock();
				times[2] = double(end - begin) / CLOCKS_PER_SEC;

				for (int i = 0; i < algsSize; ++i) {//add to average
					//if (i == 0) continue;
					timesAVG[i] += times[i];
					countersAVG[i].checks += counters[i].checks;
					countersAVG[i].swaps += counters[i].swaps;
					memAVG[i] += counters[i].memory;
				}

			}

			for (int i = 0; i < algsSize; ++i) {
				//if (i == 0) continue;
				timesAVG[i] = timesAVG[i] / k;//arithmetic average
				countersAVG[i].checks = countersAVG[i].checks / k;
				countersAVG[i].swaps = countersAVG[i].swaps / k;
				memAVG[i] = memAVG[i] / k;
				delete[] tab[i];
			}

			cout << n << endl;

			file << n << "\t ";
			for (int i = 0; i < algsSize; ++i) {
				//if (i == 0) continue;
				file << countersAVG[i].checks << "\t " << countersAVG[i].swaps << "\t " << timesAVG[i] << "\t " << memAVG[i] <<"\t ";
			}
			file << '\n';

		}

	}
	else if (Help::contains(agrv[1], "--radixTest")) {
		if (argc <= 3) {
			cerr << "Not enough param need: nazwapliku rozmiarDanych";
			system("pause");
			return 0;
		}
		std::string filename = agrv[2];
		std::ofstream file(filename);
		if (file.bad()) {
			cerr << "Unkown file error!";
			system("pause");
			return 0;
		}
		int n;
		try {
			n = std::stoi(agrv[3]);
		}
		catch (std::invalid_argument) {
			cerr << "Unkown third argument namely: " << agrv[3] << "\tsuspected integer" << endl;
			system("pause");
			return 0;
		}

		int min = -10;
		int max = 10;
		int* tab = new int [n];

		clock_t begin;
		clock_t end;

		double timesAVG = 0;
		counter_s countersAVG;
		countersAVG.checks = 0;
		countersAVG.swaps = 0;
		countersAVG.memory = 0;
		file << "K \t Times \t Swaps" << endl;
		RadixSort radixSorter(true, false);
		//int data_size[9] = { 10,50,100,500,1000,5000,10000,50000,100000 };

		for (int k = 0; k < 5; ++k) {
			
			for (int i = 0; i < 10; ++i) {//10 powtórzeń
				Help::generate(tab, n, min, max);
				begin = clock();
				auto counters = radixSorter.sort(tab, n, true);
				end = clock();
				auto times = double(end - begin) / CLOCKS_PER_SEC;
				countersAVG.swaps += counters.swaps;
				#ifdef _WIN32
					countersAVG.memory += counters.memory;
				#endif
				timesAVG += times;
			}
			countersAVG.swaps /= 10;
			timesAVG /= 10;
			countersAVG.memory /= 10;
			min *= 10;
			max *= 10;
			cout << k << endl;

			#ifdef _WIN32
			file << k << '\t' << timesAVG << '\t' << countersAVG.swaps << '\t' << countersAVG.memory << endl;
			#else
			file << k << '\t' << timesAVG << '\t' << countersAVG.swaps << endl;
			cout << "\n Used memory info available only on WIN32" << endl;
			#endif

			countersAVG.checks = 0;
			countersAVG.swaps = 0;
			countersAVG.memory = 0;
			timesAVG = 0;
		}
	}
	else {
		cerr << "Unkown first argument namely: " << agrv[1] << "\tsuspected --type | --stat" << endl;
		system("pause");
		return 0;
	}

}
