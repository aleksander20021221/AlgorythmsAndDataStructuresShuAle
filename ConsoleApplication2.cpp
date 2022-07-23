#include <iostream>
#include <string>
using namespace std;

bool isInteger(string str) {
	for (int i = 1; i < str.length(); i++)
		if (!(isdigit(str[i]) && ((str[0]=='-')||(isdigit(str[0])))))
			return false;
	return true;
}

int input() {
	cout << "Enter the number" << endl;
	string name;
	do {
		getline(cin, name);
		if (!isInteger(name))
			cout << "Invalid! Enter the number again" << endl;
	}
	while (!isInteger(name));
	int i = stoi(name);
	return i;
}

bool isFirstBigger(int first, int second) {
	return (first > second);
}

void exchange(int & one, int & two) {
	int temporary = two;
	two = one;
	one = temporary;
}

int main() {

	cout << "Start of program" << endl;
	int rawArray[5];

	for (int i = 0; i < sizeof(rawArray) / sizeof(int); i++) {
		int k = input();
		rawArray[i] = k;
	}

	cout << "Enter 0 if normal, 1 if reversed"<<endl;
	int flag;
	cin >> flag;


	if (flag == 0) {
		for (int i = 0; i < sizeof(rawArray) / sizeof(int); i++)
			for (int j = 0; j < (sizeof(rawArray) / sizeof(int)) - 1; j++)
				if (isFirstBigger(rawArray[j], rawArray[j + 1])) {
					exchange(rawArray[j], rawArray[j + 1]);
				}
	}
	if (flag == 1) {
		for (int i = 0; i < sizeof(rawArray) / sizeof(int); i++)
			for (int j = 0; j < (sizeof(rawArray) / sizeof(int)) - 1; j++)
				if (!isFirstBigger(rawArray[j], rawArray[j + 1])) {
					exchange(rawArray[j], rawArray[j + 1]);
				}
	}

	cout << "Sorted array:" << endl;
	for (int i = 0; i < sizeof(rawArray) / sizeof(int); i++) {
		cout << rawArray[i] << " ";
	}
	return 0;
}

