#include <iostream>

#include "BST.h"
#include "RB.h"
#include "Splay.h"
#include <string>
#include <chrono> 
#include <fstream>
#include "HashMap.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
//#include "Splay.cpp"

enum class structureType { BST, RB, HMAP };

/**
	returns true if str contains str2
*/
bool contains(char* str, std::string str2) {
	std::string conv = str;
	return conv.find(str2) != std::string::npos;
}

Tree<std::string>* buildTree(structureType type) {
	Tree<std::string>* t;

	switch (type) {
		case structureType::BST:
			t = new BST<std::string>();
			break;
		case structureType::RB:
			t = new RB<std::string>();
			break;
		case structureType::HMAP:
			t = new HashMap<std::string>();
			break;
		default:
			t = new RB<std::string>();
			break;
	}
	return t;
}


structureType resolveType(char* string){
	if (contains(string, "bst")) {
		return structureType::BST;
	}
	else if (contains(string, "rb")) {
		return structureType::RB;
	}
	else if (contains(string, "hmap")) {
		return structureType::HMAP;
	}
	else {
		std::string error = "Unkown second argument namely: " + std::string(string) + "\t expected > bst|rb|splay";
		throw std::runtime_error("Argument error...");
	}
}

extern void runTest(structureType type, std::string inputPath, std::string outputPath);
extern void runProgram(structureType type);
extern void runFromFile(structureType type, std::string inputPath, std::string outputPath);

int main(int argc, char* argv[])
{
	try {
		if (argc < 3) {
			throw std::runtime_error("--type bst|rb|hmap <./input> out.res");
			return 0;
		}
		if (argc >= 3) {
			if (contains(argv[1], "--test")) {
				structureType type;
				type = resolveType(argv[2]);
				runTest(type, argv[3], argv[4]);
			}
			else if((contains(argv[1], "--type"))) {
				structureType type;
				type = resolveType(argv[2]);
				if (argc == 3) {
					runProgram(type);
				}
				else if(argc == 5) {
					runFromFile(type, argv[3], argv[4]);
				}
				else {
					throw std::runtime_error("Expected: --type bst|rb|hmap <./input> out.res");
				}
			}
			else {
				throw std::runtime_error("Unkown first argument namely: " + std::string(argv[1])+ "\t expected: --type\n");
				return 0;
			}	
		}

	}
	catch (std::runtime_error& err) {
		std::cerr << err.what() << std::endl;
		return 0;
	}

}

void runProgram(structureType type) {
	auto start = std::chrono::high_resolution_clock::now();
	Tree<std::string>* t = buildTree(type);

	int n;
	cerr << "Type n\n> ";
	cin >> n;

	std::string str;
	for (int i = 0; i < n; ++i) {
		cerr << "[ insert s | load f | delete s | find s | min | max | successor k | inorder | exit | bfs ] \n> ";
		cin >> str;
		if (str == "insert") {
			cin >> str;
			auto last = str.length();
			if (!((str[0] > 64 && str[0] < 91) || (str[0] > 96 && str[0] < 123))) {
				str = str.substr(1, last);
			}
			last = str.length();
			if (!((str[last - 1] > 64 && str[last - 1] < 91) || (str[last - 1] > 96 && str[last - 1] < 123))) {
				str = str.substr(0, last - 1);
			}
			t->insert(str);
		}
		else if (str == "delete") {
			cin >> str;
			t->remove(str);
		}
		else if (str == "find") {
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
			cout << t->inOrder() << "\n";
		}
		else if (str == "min") {
			cout << t->min() << "\n";
		}
		else if (str == "max") {
			cout << t->max() << "\n";
		}
		else if (str == "successor") {
			cin >> str;
			cout << t->successor(str) << "\n";
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

void runFromFile(structureType type, std::string inputPath, std::string outputPath) {
	auto start = std::chrono::high_resolution_clock::now();
	Tree<std::string>* t = buildTree(type);
	std::ifstream inputFile(inputPath);
	std::ofstream outputFile(outputPath);

	if (inputFile.bad()) {
		throw std::runtime_error("Can't find file of name:" + inputPath + "\n");
	}
	int n;
	inputFile >> n;

	std::string str;
	for (int i = 0; i < n; ++i) {
		inputFile >> str;
		if (str == "insert") {
			inputFile >> str;
			auto last = str.length();
			if (!((str[0] > 64 && str[0] < 91) || (str[0] > 96 && str[0] < 123))) {
				str = str.substr(1, last);
			}
			last = str.length();
			if (!((str[last - 1] > 64 && str[last - 1] < 91) || (str[last - 1] > 96 && str[last - 1] < 123))) {
				str = str.substr(0, last - 1);
			}
			t->insert(str);
		}
		else if (str == "delete") {
			inputFile >> str;
			t->remove(str);
		}
		else if (str == "find") {
			inputFile >> str;
			if (t->search(str)) {
				outputFile << "1\n";
			}
			else {
				outputFile << "0\n";
			}
		}
		else if (str == "load") {
			inputFile >> str;
			t->load(str);
		}
		else if (str == "inorder") {
			outputFile << t->inOrder() << "\n";
		}
		else if (str == "min") {
			//TODO
		}
		else if (str == "max") {
			//TODO
		}
		else if (str == "successor k") {
			//TODO 
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


void runTest(structureType type, std::string inputPath, std::string outputPath) {
	Tree<std::string>* t = buildTree(type);

	std::ofstream of(outputPath);
	std::string str;
	cout << "Run inOrder()? [y|n]\n";
	cin >> str;

	auto start = std::chrono::high_resolution_clock::now();
	t->load(inputPath);
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
	t->searchFromFile(inputPath);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	of << "Search: " << endl
		<< "\tChecks: " << t->getChecks() << endl
		<< "\tSwaps: " << t->getSwaps() << endl
		<< "\tTime[ms]: " << duration.count() << endl << endl;
	t->printInfo();

	start = std::chrono::high_resolution_clock::now();
	t->resetSwapsChecks();
	t->deleteFromFile(inputPath);
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



/*
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
*/