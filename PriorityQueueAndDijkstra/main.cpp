#include <iostream>
#include "PriorityQueue.h"
#include <string>

int main() {

	int m;
	std::cout << "Type m: " << std::endl;
	std::cin >> m;
	PriorityQueue pq(m);

	std::string str;
	for (int i = 0; i < m; ++i) {
		std::cout << "Type [insert p x, empty, top, pop, priority p x, print]: " << std::endl;
		std::cin >> str;
		if (str.find("insert") != std::string::npos) {
			int x, p;
			std::cin >> x >> p;
			pq.insert(x, p);
		}
		else if (str.find("empty") != std::string::npos) {
			std::cout << pq.isEmpty() << std::endl;
		}
		else if (str.find("top") != std::string::npos) {
			std::cout << pq.top() << std::endl;
		}
		else if (str.find("pop") != std::string::npos) {
			std::cout << pq.pop() << std::endl;
		}
		else if (str.find("priority") != std::string::npos) {
			int x, p;
			std::cin >> x >> p;
			pq.priority(x, p);
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