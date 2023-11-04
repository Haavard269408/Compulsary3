#include <iostream>
using namespace std;


class File {
private:

	string name;
	int size;
	string date;

public:
	File() {
		name = "";
		size = 0;
		date = "";
	}
	// we can write f.eks 3 different constructs with different number of parameters. When we call File how many parameters we use determines which constructor to be called. 
	File(string newName, int newSize, string newDate) {
		name = newName;
		size = newSize;
		date = newDate;
	}

	string setName(string newName) {
		return name = newName;
	}
	string getName() {
		return name;
	}

	int getSize() {
		return size;
		
	}
	string getDate() {
		return date;
	}

	void printFile() {
		cout << "\nFile name: " << name << "\nFile size: " << size << "\nFile date: " << date << endl;

	}
}; 
