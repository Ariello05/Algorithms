#include <iostream>
#include "stdafx.h"
#include "UniqueVector.h"
#include "DFA.h"
#include "AutomatonMatcher.h"
#include "TransitionCreator.h"
#include "KMP.h"

using std::string;
using std::wstring;
using std::u32string;
using std::cout;
using std::wcout;


class InputAutomator {
public:
	InputAutomator():end('q'){}

	void runLoop() {
		char c;
		std::cin >> c;
		while (c != end) {
			std::cin >> c;
		}
	}

private:
	const char end;	 
};


int main()
{
	//SetConsoleOutputCP(CP_UTF8);
	//SetConsoleCP(CP_UTF8);

	std::string str;
	std::string pattern;
	std::string text;
	std::string alphabet = "";
	bool print = false;
	
	while(true) {
		try {
			std::cout << "Type [Pattern: string, Text: string, *(Alphabet: string), DFA, KMP, debug, exit]: " << std::endl;
			std::cin >> str;
			if (str.find("KMP") != std::string::npos) {
				KMP kmp;
				kmp.runMatcher(text, pattern);
			}
			else if (str.find("DFA") != std::string::npos) {
				auto dfa = std::make_shared<DFA>();
				if (alphabet == "") {
					alphabet = text;
				}
	
				TransitionCreator tc;
				tc.computeTransition(*dfa, pattern, alphabet);
				AutomatonMatcher am(dfa);
				if (print) {
					dfa->printRoutes();
					am.runMatcher(text);
				}
				else {
					am.runMatcher(text);
				}
	
			}
			else if (str.find("Pattern") != std::string::npos) {
				std::cin >> str;
				pattern = str;
			}
			else if (str.find("Text") != std::string::npos) {
				std::cin >> str;
				text = str;
			}
			else if (str.find("Alphabet") != std::string::npos) {
				std::cin >> str;
				alphabet = str;
			}
			else if (str.find("debug") != std::string::npos) {
				print = !print;
				if (print) {
					std::cout << "Debug mode ON\n";
				}
				else {
					std::cout << "Debug mode OFF\n";
				}
			}
			else if (str.find("exit") != std::string::npos) {
				break;
			}
			else {
				std::cout << "Unkown operation" << std::endl;
			}
			std::cout << std::endl;
		}catch (std::exception e) {
			cout << e.what() << std::endl;
		}
	}
	//shared_ptr<DFA> d = std::make_shared<DFA>();
	//d->printRoutes();
	//TransitionCreator tc;
	//tc.computeTransition(*d, "abab", "abcd");

}

