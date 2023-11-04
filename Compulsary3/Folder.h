#include <iostream>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

/// <summary>
/// Generates random number between 1 and 100
/// </summary>
/// <returns>Random integer between 1 and 100. </returns>
int generateRandomNum() { 
	int lowerBound = 0;
	int upperBound = 100;
	return rand() % (upperBound - lowerBound + 1) + lowerBound;
};


class Folder {
private:

	string name;
	int size;
	string date;

	File files[10];

	int folderCount = 1;

public:
	Folder(string newName, int newSize = generateRandomNum(), string newDate = "21.10.2023") {

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
	string getDate() {
		return date;
	}
	int getSize() {
		return size;
	}
	int getFileCount() {
		return fileCount;
	}
	int fileCount = 0;
	File* getFiles() {
		return files;
	}
	Folder* parentFolder;
	Folder* subFolders[5];

	/// <summary>
	/// Adds a file to the current folder. With user input as name, randomnumber as number and predfined date.
	///
	/// </summary>
	/// <returns>A file object to the files array</returns>
	File addFile() {

		if (fileCount < 10) {
			string fileName;
			cout << "Input file name: ";
			cin >> fileName;

			int size = generateRandomNum();

			string date = "31.10.2023";

			File file(fileName, size, date);
			files[fileCount] = file;
			fileCount++;

			printFile(file);
			return file;
		}


	}


	/// <summary>
	/// Print the information of each file.
	/// </summary>
	/// <param name="file">File object that we want to print the information</param>
	void printFile(File file) {
		cout << "\nAdded file name: " << file.getName();
		cout << "\nFile size: " << file.getSize();
		cout << "\nDate created: " << file.getDate() << endl;
	}

	/// <summary>
	/// Prints information of all files in a given folder
	/// </summary>
	void printFilesInFolder() {

		cout << "\nCurrent folder: " << getName() << endl;

		for (int i = 0; i < fileCount; i++)
		{
			files[i].printFile();

		}


	}

	/// <summary>
	/// Adds a folder "sub-folder" to a currently selected folder, fills the subFolder array for said folder. 
	/// </summary>
	/// <param name="name"></param>
	/// <returns>Folder for the subFolder array for current folder</returns>
	Folder* addSubFolder(string name) {

		int folderSize = sizeof(subFolders) / sizeof(subFolders[0]);

		if (folderCount < folderSize) {
			Folder* newFolder = new Folder(name, generateRandomNum(), "31.10.2023");

			subFolders[folderCount] = newFolder;
			newFolder->parentFolder = this;
			folderCount++;

			printFolder();

			return newFolder;
		}

		else {
			cout << "Directory is full! ";
			cout << "\nFiles array size: " << sizeof(subFolders) / sizeof(subFolders[0]);

		}

	}

	/// <summary>
	/// Changes which folder is the current folder and will show up in termnial
	/// </summary>
	/// <param name="folderArray"></param>
	/// <returns>Parent folder if user input, folder at a certain index if user input, this or just returns to menu if undefined, </returns>
	Folder* changeFolderDir(Folder* folderArray[]) {

		if (folderArray != nullptr) {

			int secondsToWait = 1;
			int index;
			cout << "Please enter index of the folder you want to access (-1 go to parent-folder): ";
			cin >> index;

			if (index == -1) {
				if (parentFolder != NULL) {
					cout << "Switching: ...";
					sleep_for(seconds(secondsToWait));
					cout << "\nSwitched to previous folder: " << parentFolder->getName();

					return parentFolder;

				}
				else { "this is the root directory. "; }


			}

			else if (index >= 0 && index < folderCount) {

				cout << "Switching: ...";
				sleep_for(seconds(secondsToWait));
				cout << "\nSwitched to folder: " << folderArray[index]->getName();

				return folderArray[index];

			}

			else {
				cout << "Invalid folder index." << endl;
				return this;
			}


		}



	}

	/// <summary>
	/// Prints all info relevant for current folder
	/// </summary>
	void printFolder() {

		cout << "\nCurrent folder: " << getName() << endl;
		int index = 0;
		for (int i = 0; i < folderCount; i++)
		{
			index++;
			cout << "\nName of folder: " << subFolders[i]->getName() << "\nSize of folder: " << subFolders[i]->getSize() << "\nDate created: " << subFolders[i]->getDate() <<
				"\nFile index: " << (index - 1) << endl;
		}



	}

	//void printFolderContent() {

	//	cout << "current folder: " << getName();
	//	cout << "\nfiles: " << endl;

	//	cout << getFiles()->getName();
	//	cout << getFiles()->getSize();
	//}

	/// <summary>
	/// Changes name of files based on user input
	/// </summary>
	void changeNameOfFiles() {

		int index;
		string newName;

		cout << "\nEnter index of file you want to change: ";
		cin >> index;

		cout << "\nEnter new name: ";
		cin >> newName;

		for (int i = 0; i < 1; i++)
		{
			files[index].setName(newName);
			cout << "\nNew filename: " << files->getName();
		}
	}

	/// <summary>
	/// Takes a folderArray and looks trough all files in a given folder, if any. It shall then print out the largest file name and size.
	/// </summary>
	/// <param name="folderName"></param>
	/// <param name="folderArray"></param>
	void lookLargest(string folderName, Folder* folderArray[]) {
		//current bug: if switching to newly created folder -> folderArray = 0 -> not able to perfrom this function on current folder, have to go back to prev (parent folder). 
		int fileArraySize = sizeof(files) / sizeof(files[0]);
		int folderSize = sizeof(subFolders) / sizeof(subFolders[0]);

		for (int i = 0; i < folderSize; i++)
		{
			if (folderArray[i] != nullptr) {

				string name = folderArray[i]->getName();

				File* files = folderArray[i]->getFiles();

				if (folderName == name && folderArray[i]->getFileCount() != 0) {

					cout << "Searching folder: " << name << endl;

					File currentLargestFile = files[0];
					int currFileSize = currentLargestFile.getSize();

					for (int j = 0; j < 10; j++)
					{

						if (files[j].getSize() > currFileSize) {
							currentLargestFile = files[j];
							currFileSize = files[j].getSize();
						}
					}

					cout << "\nLargest file name: " << currentLargestFile.getName();
					cout << "\nLargest file size: " << currentLargestFile.getSize() << endl;

					char input;
					cout << "\n Would you like to print out all files in that folder aswell? Press Y for yes/everthing else for no and go back: ";
					cin >> input;
					// fix bug
					if (input == 'y' || input == 'Y') {
						folderArray[i]->printFilesInFolder();
					}
					else {
						return;
					}

				}

			}
		}
	}
};
