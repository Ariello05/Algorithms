#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	string input;
	cout << "Type input file\n";
	cin >> input;
	cout << "Type output file\n";
	string str;
	cin >> str;
	std::ofstream of(str);
	ifstream file(input);

	vector<string>tab;
	string newvar;

	while (std::getline(file, str)) {
		for (int i = 0; i < str.length(); ++i)
		{
			while ((str[i] > 64 && str[i] < 91) || (str[i] > 96 && str[i] < 123))
			{
				newvar += str[i];
				i++;
			}
			if (newvar != "") {
				tab.push_back(newvar);
				newvar.clear();
			}
		}
	}

	random_shuffle(tab.begin(),tab.end());
	for (int i = 0; i < tab.size(); ++i) {
		of << tab[i] << endl;
	}
	of.close();
	file.close();

}
