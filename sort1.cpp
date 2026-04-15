#include <iostream>
#include <fstream>
#include <cstring>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <windows.h>
#include <unordered_map>
using namespace std;

string clean(const string& word) {

	string cleaner;

	for (char ch : word) {

		if (isalpha(static_cast<unsigned char>(ch))) {
			cleaner += ch;
		}

	}

	return cleaner;

}

string low(const string& word) {

	string lowik = word;

	for (char& ch : lowik) {

		ch = tolower(static_cast<unsigned char>(ch));

	}

	return lowik;

}

string searching(vector<string>& arr1, string search) {

	int h = arr1.size();
	string s;
	string result;

	for (int i = 0; i < h; i++) {

		s = arr1[i];
		if (search == s) {

			return arr1[i];

		}


	}


	return "false";

}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	int i = 0;
	int h;
	string see, search, result;
	ifstream file("test_text.txt");
	unordered_map<string, int> arr;
	string word;
	if (file.is_open()) {

		while (file >> word) {
			word = clean(word);
			if (!word.empty()) {
				word = low(word);
				arr[word]++;
			}
		}

	}
	else {
		cout << "falls";
	}



	//vector<string> arr1(arr.begin(), arr.end());


	cout << "Введите слово:" << endl;
	cin >> search;
	//result = searching(arr1, search);
	//cout << result << endl;

	auto it = arr.find(search);
	if (it != arr.end()) {

		int k = it->second;
		string world = it->first;
		cout << "Слово: " << world << " встречается " << k << " раз(а)";

	}
	else {

		cout << "false";

	}

	return 0;


}