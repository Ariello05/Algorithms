﻿#include <bitset>
#include <iostream>
#include <climits>
#include <stdio.h>
#include <utility>
#include <vector>
#include "HyperCube.h"
#include "EdmondsKarp.h"
#include <time.h>
#include "Bipartite.h"
#include <chrono>
#include <string>
#include <vector>
#include "GLPKCreator.h"
#include <fstream>

using std::cout;
using std::cin;
using std::endl;

/**
	returns true if str contains str2
*/
bool contains(char* str, std::string str2) {
	std::string conv = str;
	return conv.find(str2) != std::string::npos;
}

extern int runGLPK(int k, int i, std::string file);
extern int runGLPK(int k, std::string file);

extern int runNormal(int k, int i);
extern int runNormal(int k);

extern int runTest(bool bi, std::string file);

int main(int argc, char *argv[])
{
	srand(time(NULL));	

	if (argc <= 2) {
		std::cerr << "--size k (optional)--degree i (optional)[--glpk, --test] name ";
		return 0;
	}
	std::vector<char *> strV;
	for (int i = 1; i <= argc; ++i) {
		strV.push_back(argv[i]);
	}

	int k = -1;
	int j = -1;
	bool bi = false;
	int type = 0;
	std::string fileName = "placeholder.txt";

	for (int i = 0; i < strV.size(); ++i)
	{
		try {
			if (strV[i] == nullptr) {
				continue;
			}

			if (contains(strV[i], "--size"))
			{
				++i;
				k = std::stoi(strV[i]);
				continue;
			}
			if (contains(strV[i], "--degree")) {
				++i;
				bi = true;
				j = std::stoi(strV[i]);
				continue;
			}

			if (contains(strV[i], "--glpk")) {
				type = 1;
				++i;
				fileName = strV[i];
			}
			else if (contains(strV[i], "--test")) {
				type = 2;
				++i;
				fileName = strV[i];
			}
		}
		catch (std::exception const& e) {
			std::cerr << "--size k, (optional)--degree i, (optional)[--glpk, --test] name ";
			return 0;
		}
	}
	
	if (type == 0) {//normal
		if (k == -1) {
			std::cerr << "k is undefined";
			return 0;
		}

		if (bi) {
			if (j == -1) {
				std::cerr << "i is undefined";
				return 0;
			}
			return runNormal(k, j);
		}
		else {
			return runNormal(k);
		}
	}
	else if (type == 1) {//glpk
		if (k == -1) {
			std::cerr << "k is undefined";
			return 0;
		}

		if (bi) {
			if (j == -1) {
				std::cerr << "i is undefined";
				return 0;
			}
			return runGLPK(k, j, fileName);
		}
		else {
			return runGLPK(k, fileName);
		}
	}
	else if (type == 2) {//test

		return runTest(bi, fileName);
	}
	return 0;
}


int runGLPK(int k, int i, std::string file)
{
	Graph* t;
	t = new Bipartite(k, i);
	GLPKCreator::make(t,file);
	std::cout << "GPLK created, CTRL+C to stop control Check \n";
	EdmondsKarp ek(t);
	auto start = std::chrono::high_resolution_clock::now();
	std::cout << "max = " << ek.run() << std::endl;
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cerr << "Time elapsed(seconds): " << duration.count() << endl;

	return 1;
}

int runGLPK(int k, std::string file)
{
	Graph* t;
	t = new HyperCube(k);
	GLPKCreator::make(t, file);
	std::cout << "GPLK created, CTRL+C to stop control Check \n";
	EdmondsKarp ek(t);
	auto start = std::chrono::high_resolution_clock::now();
	std::cout << "max = " << ek.run() << std::endl;
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cerr << "Time elapsed(seconds): " << duration.count() << endl;

	return 1;
}

int runNormal(int k, int i)
{
	Graph* t;
	auto start = std::chrono::high_resolution_clock::now();
		
	t = new Bipartite(k, i);
	EdmondsKarp ek(t);

	std::cout << "max = " << ek.run() << std::endl;
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cerr << "Time elapsed(seconds): " << duration.count() << endl;

	delete t;
	return 1;

}

int runNormal(int k)
{
	Graph* t;
	auto start = std::chrono::high_resolution_clock::now();

	t = new HyperCube(k);
	EdmondsKarp ek(t);

	std::cout << "max = " << ek.run() << std::endl;
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cerr << "Time elapsed(seconds): " << duration.count() << endl;
	std::cerr << "Routes: " << ek.getLastRoutes() << endl;

	delete t;
	return 1;
}

int runTest(bool bi, std::string fileName)
{
	std::ofstream file(fileName);

	if (bi) {//run for all
		file << "k i fmax\n";
		double sum;
		// 3 1024
		// 4 512
		// 5 256
		// 6 128
		// 7 64
		// 8 32
		// 9 32
		// 10 32
		int first = 512;// 2^9
		for (unsigned int k = 3; k <= 10; ++k) {
			for (unsigned int i = 1; i <= k; ++i) {
				Graph* hc = new Bipartite(k,i);
				EdmondsKarp ek(hc);
				sum = 0.0;
				for (int l = first; l >= 0; --l) {
					sum += (double)ek.run() / double(first);
				}
				file << k << " " << i << " " << sum << endl;

				delete hc;
			}
			if (first >= 64) {
				first /= 2;
			}
		}
	}
	else {
		file << "k fmax routes\n";
		double sum;
		double routes;
		// 3 1024
		// 4 512
		// 5 256
		// 6 128
		// 7 64
		// 8 32
		// 9 16
		// 10 8
		// 11 8
		// 12 8
		// 13 8
		// 14 8
		// 15 8
		// 16 8
		int first = 1024;// 2^10
		for (unsigned int k = 1; k <= 16; ++k) {
			Graph* hc = new HyperCube(k);
			EdmondsKarp ek(hc);
			sum = 0.0;
			routes = 0.0;
			for (int i = first; i >= 0; --i) {
				sum += (double)ek.run() / double(first);
				routes += (double)ek.getLastRoutes() / double(first);
			}
			if (first >= 16) {
				first /= 2;
			}
			file << k << " " << sum << " " << routes << endl;

			delete hc;
		}
	}
	return 1;

}