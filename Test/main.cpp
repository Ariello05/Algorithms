#include <iostream>
#include "class.hpp"
#include <vector>

using std::cout;
using std::endl;

int main() {
	//int tab[2];
	//tab[0] = 1;
	//tab[1] = 2;
	//Tester<int> t;
	//t.take(tab);
	std::vector<int> vect;
	vect.push_back(1);
	vect.push_back(2);
	Tester<std::vector<int> > t2;
	t2.take(vect);

	t2.shuff();
	//cout << tab[0] << "\t" << tab[1] << endl;
	cout << vect[0] << "\t" << vect[1] << endl;
	int a;
	std::cin >> a;
}
