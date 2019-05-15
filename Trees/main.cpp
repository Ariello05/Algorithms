#include <iostream>

#include "BST.h"
#include "RB.h"
#include "Splay.h"
#include <string>
#include <chrono> 
#include <fstream>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
//#include "Splay.cpp"

/**
	returns true if str contains str2
*/
bool contains(char* str, std::string str2) {
	std::string conv = str;
	return conv.find(str2) != std::string::npos;
}

extern void runTest(char* argv[]);

int main(int argc, char* argv[])
{
	if (argc < 3) {
		std::cerr << "--type bst|rb|splay (optional) --test";
		return 0;
	}
	if (argc == 4) {
		if (contains(argv[3], "--test")) {
			runTest(argv);
		}
		else {
			std::cerr << "Unkown first argument namely: " << argv[3] << "\t --test" << std::endl;
		}
		return 0;
	}

	if (contains(argv[1], "--type")) {
		Tree<std::string>* t;
		auto start = std::chrono::high_resolution_clock::now();

		if (contains(argv[2], "bst")) {
			t = new BST<string>();
		}
		else if (contains(argv[2], "rb")) {
			t = new RB<string>();
		}
		else if (contains(argv[2], "splay")) {
			t = new Splay<string>();
		}
		else {
			cerr << "Unkown second argument namely: " << argv[2] << "\t suspected bst|rb|splay" << endl;
			return 0;
		}
		int n;
		cout << "Type n: ";
		cin >> n;

		string str;
		for (int i = 0; i < n; ++i) {
			cout << "\n [ insert s | delete s | search s | load f | inorder | bfs | exit ] \n";
			cin >> str;
			if (str == "insert") {
				cin >> str;
				auto last = str.length();
				if (!((str[0] > 64 && str[0] < 91) || (str[0] > 96 && str[0] < 123))) {
					str = str.substr(1,last);
				}
				last = str.length();
				if (!((str[last-1] > 64 && str[last-1] < 91) || (str[last-1] > 96 && str[last-1] < 123))) {
					str = str.substr(0, last-1);
				}
				t->insert(str);
			}
			else if (str == "delete") {
				cin >> str;
				t->remove(str);
			}
			else if (str == "search") {
				cin >> str;
				if (t->search(str)) {
					cout << "1\n";
				}
				else {
					cout << "0\n";
				}
			}
			else if (str == "load") {
				cin >> str;
				t->load(str);
			}
			else if (str == "inorder") {
				t->inOrder();
			}
			else if (str == "bfs") {
				t->bfs();
			}
			else if (str == "exit") {
				break;
			}
			else {
				cerr << "Unkown operation" << endl;
			}
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
		cerr << "Time elapsed(seconds): " << duration.count() << endl;
		t->printInfo();

		delete t;
	}
	else {
		std::cerr << "Unkown first argument namely: " << argv[1] << "\t --type" << std::endl;
		return 0;
	}
}

void runTest(char *argv[]) {
	if (contains(argv[1], "--type")) {
		Tree<std::string>* t;
		
		if (contains(argv[2], "bst")) {
			t = new BST<string>();
		}
		else if (contains(argv[2], "rb")) {
			t = new RB<string>();
		}
		else if (contains(argv[2], "splay")) {
			t = new Splay<string>();
		}
		else {
			cerr << "Unkown second argument namely: " << argv[2] << "\t suspected bst|rb|splay" << endl;
			return;
		}
		string input;
		cout << "Type input file\n";
		cin >> input;
		cout << "Type output file\n";
		string str;
		cin >> str;
		std::ofstream of(str);

		cout << "Run inOrder()? [y|n]\n";
		cin >> str;

		auto start = std::chrono::high_resolution_clock::now();
		t->load(input);
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		of << "Insert: " << endl
			<< "\tChecks: " << t->getChecks() << endl
			<< "\tSwaps: " << t->getSwaps() << endl
			<< "\tTime[ms]: " << duration.count() << endl << endl;
		t->printInfo();

		if (str == "y") {
			auto start = std::chrono::high_resolution_clock::now();
			t->inOrder();
			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
			of << "InOrder: " << endl
				<< "\tTime[ms]: " << duration.count() << endl << endl;
			t->printInfo();
		}

		start = std::chrono::high_resolution_clock::now();
		t->resetSwapsChecks();
		t->searchFromFile(input);
		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		of << "Search: " << endl
			<< "\tChecks: " << t->getChecks() << endl
			<< "\tSwaps: " << t->getSwaps() << endl
			<< "\tTime[ms]: " << duration.count() << endl << endl;
		t->printInfo();

		start = std::chrono::high_resolution_clock::now();
		t->resetSwapsChecks();
		t->deleteFromFile(input);
		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		of << "Delete: " << endl
			<< "\tChecks: " << t->getChecks() << endl
			<< "\tSwaps: " << t->getSwaps() << endl 
			<< "\tTime[ms]: " << duration.count() << endl << endl;
		t->printInfo();
		of.close();
		
		//auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
		//cerr << "Time elapsed(seconds): " << duration.count() << endl;
		//t->printInfo();
		cerr << "End..." << endl;

		delete t;
	}
	else {
		std::cerr << "Unkown first argument namely: " << argv[1] << "\t --type" << std::endl;
		return;
	}
}