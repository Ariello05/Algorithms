#pragma once
#include <string>
#include <fstream>
#include <istream>
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

template <typename T>
class Tree {
public:
	virtual void insert(T) {
		insertCount++;
		size++;
		if (max_size < size) {
			max_size = size;
		}
	}
	virtual void remove(T) {
		deleteCount++;
	}
	virtual bool search(T) {
		searchCount++;
		return true;
	}

	void load(std::string f) {
		loadCount++;
		std::ifstream file(f);
		if (!file.is_open()) {
			throw std::runtime_error("Can't find file!\n");
			file.close();
			return;
		}
		std::cerr << "loading...\n";
		std::string var;
		std::string newvar;
		while (std::getline(file, var)) {
			for (int i = 0; i < var.length(); ++i)
			{
				while ((var[i] > 64 && var[i] < 91) || (var[i] > 96 && var[i] < 123))
				{
					newvar += var[i];
					i++;
				}
				if (newvar != "") {
					insert(static_cast<T>(newvar));
					newvar.clear();
				}
			}
		}
		file.close();
	}
	void searchFromFile(std::string f) {
		//loadCount++;
		std::ifstream file(f);
		if (!file.is_open()) {
			throw std::runtime_error("Can't find file!\n");
			file.close();
			return;
		}
		std::cerr << "loading...\n";
		std::string var;
		std::string newvar;
		while (std::getline(file, var)) {
			for (int i = 0; i < var.length(); ++i)
			{
				while ((var[i] > 64 && var[i] < 91) || (var[i] > 96 && var[i] < 123))
				{
					newvar += var[i];
					i++;
				}
				if (newvar != "") {
					search(static_cast<T>(newvar));
					newvar.clear();
				}
			}
		}
		file.close();
	}
	void deleteFromFile(std::string f) {
		//loadCount++;
		std::ifstream file(f);
		if (!file.is_open()) {
			std::cerr << "Can't find file!\n";
			file.close();
			return;
		}
		std::cerr << "loading...\n";
		std::string var;
		std::string newvar;
		while (std::getline(file, var)) {
			for (int i = 0; i < var.length(); ++i)
			{
				while ((var[i] > 64 && var[i] < 91) || (var[i] > 96 && var[i] < 123))
				{
					newvar += var[i];
					i++;
				}
				if (newvar != "") {
					//std::cerr << "\tDELETE: " << newvar << std::endl;

					remove(static_cast<T>(newvar));
					newvar.clear();
				}
			}
		}
		file.close();
	}
	virtual void updateVariables() {

	}
	virtual std::string inOrder() {
		inOrderCount++;
		return "";
	}
	virtual void bfs() = 0;
	virtual std::string min(){
		minCount++;
		return "";
	};
	virtual std::string max() {
		maxCount++;
		return "";
	};
	virtual std::string successor(T f) {
		successorCount++;
		return "";
	};
	void printInfo() {

		std::cerr << "Operations counters: \n"
			<< "\tinsert: " << insertCount << endl
			<< "\tdelete: " << deleteCount << endl
			<< "\tsearch: " << searchCount << endl
			<< "\tload: " << loadCount << endl
			<< "\tinOrder: " << inOrderCount << endl
			<< "\tmin: " << minCount << endl
			<< "\tmax: " << maxCount << endl
			<< "\tsuccessor: " << successorCount << endl << endl
			<< "Maximum size: " << max_size << endl
			<< "Ending size: " << size << endl
			<< "Node checks: " << checks << endl
			<< "Node swaps: " << swaps << endl;
	}
	int getSwaps() {
		return swaps;
	}
	int getChecks() {
		return checks;
	}
	virtual void resetSwapsChecks() {
		swaps = 0;
		checks = 0;
	}

protected:
	int insertCount = 0;
	int deleteCount = 0;
	int searchCount = 0;
	int loadCount = 0;
	int inOrderCount = 0;
	int maxCount = 0;
	int minCount = 0;
	int successorCount = 0;

	int swaps = 0;
	int checks = 0;
	int max_size = 0;
	int size = 0;
};