#include "MainCore.h"

bool FileExists(string filepath) {
	struct stat buffer;
	return (stat(filepath.c_str(), &buffer) == 0);
}

#pragma region [ MENU Functions ]

void HashMenuOptions() {
	cout <<
		"\n HASHING OPTIONS"
		"\n [1] Check List"
		"\n [2] Insert Item"
		"\n [3] Remove Item"
		"\n [4] Print Table"
		"\n [5] Hash Image"
		"\n [0] EXIT"
		<< endl;
}

void ValidateKey() {
	 /// INSERT Item
	// Validate user input when inserting an item to the table
	if (optSelected == OptSelect::InsertItem) {
		cout << "\n [2]TIP!> If nothing happenes, the input was illegal.";
		cout << "\n [2]INSERT> Please enter a key. (EG: 905, 247, 390)" << "\n /: ";
		cin >> key;

		while (!cin) { //Validate for integer input
			cin.clear();
			cin.ignore();

			cout << "\n /: "; 
			cin >> key;
		}

		cout << "\n [2]INSERT> Please enter a name. (EG: Alpha, Biscuit, Charles)" << "\n /: ";
		cin >> name;

		return;
	}

	 /// REMOVE Item
	// Validate user input when removing an item from the table
	if (optSelected == OptSelect::RemoveItem) {
		cout << "\n [3]DELETE> Please enter a key. (EG: 905, 247, 390)" << "\n /: ";
		cin >> key;
		
		while (!cin) { //Validate for integer input
			cin.clear();
			cin.ignore();
			cin >> key;
		}

		return;
	}


	 /// HASH File Name
	// Validate user input when hashing an image
	if (optSelected == OptSelect::HashImage) {
		cout << "\n [5]HASH> Please enter a filepath to any file. EG. c:\\Users\\fileName.PNG" << "\n /: ";
		cin >> filepath;

		cout << fs::exists(filepath) << endl; //Returns bool if file exists or not
	}
}

void MenuValidation() {
	bool flag = true;
	while (flag) {
		cout << "\n //: ";
		cin >> userInput;
		switch (userInput) {

		 ///CHECK TABLE
		// Check if the hashtable is empty or not
		case OptSelect::CheckTable:
			flag = false;
			HT.isEmpty();
			continue;

		 ///INSERT ITEM
		// Insert an item to the hashtable
		case OptSelect::InsertItem:
			optSelected = OptSelect::InsertItem;
			flag = false;
			ValidateKey();
			HT.InsertItem(key, name);
			continue;

		 ///REMOVE ITEM
		// Remove an item from the hashtable
		case OptSelect::RemoveItem:
			optSelected = OptSelect::RemoveItem;
			flag = false;
			ValidateKey();
			HT.RemoveItem(key);
			continue;

		 ///PRINT TABLE
		// Prints the hash table to the console
		case OptSelect::PrintTable:
			flag = false;
			HT.PrintTable();
			continue;

		 ///HASH IMAGE NAME
		// Hashes the name of the image
		case OptSelect::HashImage:
			optSelected = OptSelect::HashImage;
			flag = false;
			ValidateKey();
			HT.HashFunction(filename);
			HT.HashFunction("KittyFishtank");
			continue;

		 ///EXIT CONSOLE
		// Ends the program
		case OptSelect::Exit:
			flag = false;
			exitConsole = true;
			exit(0);
			continue;

		default: cout << "[]> Invalid.\n"; continue; //Loops until a valid input is recieved.
		}
	}
}

#pragma endregion

int main() {
	HashTable hashTable;

	HashMenuOptions();

	while (!exitConsole) {
		MenuValidation();
	}

	return 0;
}