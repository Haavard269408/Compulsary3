#include <iostream>
#include <vector>
#include <cstdlib> 
#include <string>
#include <chrono>
#include <thread>
#include "File.h"
#include "Folder.h"

using namespace std;

//using these for time delay for a few functions. More for a "visual effect". 
using namespace std::this_thread;
using namespace std::chrono;


int main()
{
	int input;

	Folder* mainFolder = new Folder("Main-Folder");  // Set the initial current folder.
	Folder* currentFolder = mainFolder;
	currentFolder->subFolders[0] = currentFolder; // sets main folder as first element, so that we can do the "lookLargest" function on it ie subFolderArray not empty in LookLarget function.

	cout << "Current Root Folder: " << currentFolder->getName() << endl;


	while (true) {
		cout << "\n___________________" << endl;
		cout << "\nPress 1 to make a new file: " << endl;
		cout << "\nPress 2 to print all files in folder: " << endl;
		cout << "\nPress 3 to create new folder" << endl;
		cout << "\nPress 4 to change file name: " << endl;
		cout << "\nPress 5 to change folder name: " << endl;
		cout << "\nPress 6 to print all folders: " << endl;
		cout << "\nPress 7 to change folder dir: " << endl;
		cout << "\nPress 8 to get largest file in folder: " << endl;
		cout << "\nPress 0 to exit program" << endl;

		cin >> input;

		if (input == 0) {
			break;
		}

		switch (input) {

		case 1: {

			int maxFiles = 10;
			if (currentFolder->getFileCount() < maxFiles) {
				currentFolder->addFile();
			}
			else {
				cout << "\nFolder: " << currentFolder->getName() << " is full" << endl;
			}
			break;

		}
		case 2: {

			currentFolder->printFilesInFolder();
			break;
		}
		case 3: {

			string folderName;
			cout << "Enter name of folder: ";
			cin >> folderName;

			currentFolder->addSubFolder(folderName);

			cout << "\nCreated new folder " << "'" << folderName << "'" << " under folder: " << currentFolder->getName() << endl;

			break;

		}

		case 4: {

			currentFolder->changeNameOfFiles();

			break;

		}
		case 5: {
			string newName;
			cout << "Enter new name for folder: ";
			cin >> newName;

			currentFolder->setName(newName);
			cout << "New folder name: " << currentFolder->getName();
			break;
		}
		case 6: {

			currentFolder->printFolder();
			break;
		}

		case 7: {

			currentFolder = currentFolder->changeFolderDir(currentFolder->subFolders);

			break;

		}

		case 8: {
			int secondsToWait = 1;
			if (currentFolder != mainFolder) {
				cout << "You can only perform this action in main folder, switching to main folder...";

				sleep_for(seconds(secondsToWait));

				currentFolder = mainFolder;
				cout << "\nSwitched to " << currentFolder->getName() << endl;
			}
			else {

				string folderName;
				cout << "Enter foldername: " << endl;
				cin >> folderName;

				currentFolder->lookLargest(folderName, currentFolder->subFolders);


			}
			break;
		}

		default:
			cout << "Unknown input" << endl;
			break;

		}

	}
}



