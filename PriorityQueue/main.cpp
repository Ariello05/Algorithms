#include <iostream>
#include "PriorityQueue.h"
#include <string>

int main() {

	int m;
	std::cout << "Type m: " << std::endl;
	std::cin >> m;
	PriorityQueue pq(m);
	std::cout << "Type [insert x p, empty, top, pop, priority x p, print]: " << std::endl;
	std::string str;
	for (int i = 0; i < m; ++i) {
		std::cout << "> ";
		std::cin >> str;
		if (str.find("insert") != std::string::npos) {
			int x, p;
			std::cin >> x >> p;
			pq.insert(p, x);
		}
		else if (str.find("empty") != std::string::npos) {
			std::cout << pq.isEmpty() << std::endl;
		}
		else if (str.find("top") != std::string::npos) {
			try {
				std::cout << pq.top() << std::endl;
			}
			catch (EmptyException e) {
				std::cout << std::endl;
			}
		}
		else if (str.find("pop") != std::string::npos) {
			try {
				std::cout << pq.pop() << std::endl;
			}
			catch (EmptyException e) {
				std::cout << std::endl;
			}
		}
		else if (str.find("priority") != std::string::npos) {
			int x, p;
			std::cin >> x >> p;
			pq.priority(p, x);
		}
		else if (str.find("print") != std::string::npos) {
			pq.print();
		}
		else {
			std::cout << "Unkown operation" << std::endl;
		}
	}

	int a;
	std::cin >> a;
}