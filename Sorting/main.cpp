#include "sort.h"
#include <ctime>
#include <chrono>
#include <time.h>
#include <random>
#include <iostream>
#include <stdio.h>
#include <fstream>

using std::cout;
using std::endl;
using std::rand;
using std::cerr;
using std::cin;

int main(int argc, char *agrv[]) {
	
	if (argc <= 2) {
		cerr << "(--type select|insert|heap|quick --asc|--desc) | (--stat nazwapliku)";
		return 0;
	}

	if (contains(agrv[1], "--type")) {
		if (argc <= 3) {
			cerr << "Not enough param need --asc|--desc";
			return 0;
		}
		bool asc;
		if (contains(agrv[3], "--asc")) {
			asc = true;
		}
		else if (contains(agrv[3], "--desc")) {
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
		int * tab = new int[n];
		for (int i = 0; i < n; ++i) {
			cin >> tab[i];
		}

		counter_s licznik;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();//c++11

		if (contains(agrv[2], "select")) {
			licznik = selectSort(tab, n, asc);
		}
		else if (contains(agrv[2], "insert")) {
			licznik = insertionSort(tab, n, asc);
		}
		else if (contains(agrv[2], "heap")) {
			licznik = heapSort(tab, n, asc);
		}
		else if (contains(agrv[2], "quick")) {
			licznik = quickSort(tab, n, asc);
		}
		else {
			cerr << "Unkown second argument namely: " << agrv[3] << "\t suspected select|insert|heap|quick" << endl;
			return 0;
		}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

		cout << "I1: Compares:" << licznik.checks << "\tSwaps:" << licznik.swaps << "\tElapsed Time(ms):" << elapsed << endl;

		if (!isSorted(tab, n, asc)) {
			cout << "ARRAY NOT SORTED" << endl;
			return 0;
		}
		printArray(tab, n);

		cin >> n;

	}
	else if (contains(agrv[1], "--stat")) {
		if (argc <= 3) {
			cerr << "Not enough param need nazwapliku k";
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

		int * tab[4];//data

		counter_s counters[4];//swaps sounts
		double times[4];//timer
		counter_s countersAVG[4];
		double timesAVG[4];
		clock_t begin;
		clock_t end;
		file << "N [S]Compares Swaps Time [I]Compares Swaps Time [H]Compares Swaps Time [Q]Compares Swaps Time\n";
		//std::chrono::steady_clock::time_point begin;//timer
		//std::chrono::steady_clock::time_point end;
		srand(time(0));
		for (int n = 100; n <= 10000; n += 100) {

			for (int i = 0; i < 4; ++i) {
				tab[i] = new int[n];
				timesAVG[i] = 0;
				countersAVG[i].checks = 0;
				countersAVG[i].swaps = 0;
			}

			for (int i = 0; i < k; ++i) {
				generate(tab[0], n, 0, 10000);
				copyArray(tab[0], tab[1],n);
				copyArray(tab[0], tab[2], n);
				copyArray(tab[0], tab[3], n);

				begin = clock();
				counters[0] = selectSort(tab[0], n, true);
				end = clock();
				times[0] = double(end - begin) / CLOCKS_PER_SEC;

				begin = clock();
				counters[1] = insertionSort(tab[1], n, true);
				end = clock();
				times[1] = double(end - begin) / CLOCKS_PER_SEC;
				
				begin = clock();
				counters[2] = heapSort(tab[2], n, true);
				end = clock();
				times[2] = double(end - begin) / CLOCKS_PER_SEC;

				begin = clock();
				counters[3] = quickSort(tab[3], n, true);
				end = clock();
				times[3] = double(end - begin) / CLOCKS_PER_SEC;

				for (int i = 0; i < 4; ++i) {//add to average
					timesAVG[i] += times[i];
					countersAVG[i].checks += counters[i].checks;
					countersAVG[i].swaps += counters[i].swaps;
				}

			}

			for (int i = 0; i < 4; ++i) {
				timesAVG[i] = timesAVG[i] / k;//arithmetic average
				countersAVG[i].checks += counters[i].checks / k;
				countersAVG[i].swaps += counters[i].swaps / k;
				delete[] tab[i];
			}

			cout << n << endl;

			file << n << " ";
			for (int i = 0; i < 4; ++i) {
				file << countersAVG[i].checks << " " << countersAVG[i].swaps << " " << timesAVG[i] << " ";
			}
			file << '\n';

		}

	}
	else {
		cerr << "Unkown first argument namely: " << agrv[1] << "\tsuspected --type | --stat" << endl;
		return 0;
	}
	/*
	
	srand(time(0));
	const int SIZE = 10000;
	int tab[SIZE];

	generate(tab, SIZE, 0, 100000);
	int *cp = copyArray(tab, SIZE);
	int *cp2 = copyArray(tab, SIZE);
	int *cp3 = copyArray(tab, SIZE);

	//printArray(tab, SIZE);

	counter_s i1 = selectSort(tab, SIZE,true);
	counter_s i2 = insertionSort(cp, SIZE, true);
	counter_s i3 = heapSort(cp2, SIZE, true);
	counter_s i4 = quickSort(cp3, SIZE, true);
	cout << "I1: Compares:" << i1.checks << "\tSwaps:" << i1.swaps << endl;
	cout << "I2: Compares:" << i2.checks << "\tSwaps:" << i2.swaps << endl;
	cout << "I3: Compares:" << i3.checks << "\tSwaps:" << i3.swaps << endl;
	cout << "I4: Compares:" << i4.checks << "\tSwaps:" << i4.swaps << endl;

	if (!isSorted(tab,SIZE,true)) {
	cout << "ARRAY NOT SORTED" << endl;
	}
	if (!isSorted(cp, SIZE, true)) {
	cout << "ARRAY NOT SORTED" << endl;
	}
	if (!isSorted(cp2, SIZE, true)) {
	cout << "ARRAY NOT SORTED" << endl;
	}
	if (!isSorted(cp3, SIZE, true)) {
	cout << "ARRAY NOT SORTED" << endl;
	}

	//printArray(tab, SIZE);
	//printArray(cp, SIZE);
	//printArray(cp2, SIZE);
	//printArray(cp3, SIZE);

	int cs;
	std::cin >> cs;
	
	return 2137;
	*/
}