#include "MainCore.h"

 /// INITIALISATION
/* Program initialisation */

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
	if (optSelected == OptSelect::InsertItem) {
		cout << "\n [2]TIP!> If nothing happenes, the input was illegal.";
		cout << "\n [2]INSERT> Please enter a key. (EG: 905, 247, 390)" << "\n /:";
		cin >> key;
		while (!cin) { //Validate for integer input
			cin.clear();
			cin.ignore();
			cin >> key;
		}

		cout << "\n [2]INSERT> Please enter a name. (EG: Alpha, Biscuit, Charles)" << "\n /:";
		cin >> name;

		return;
	}

	if (optSelected == OptSelect::RemoveItem) {
		cout << "\n [3]DELETE> Please enter a key. (EG: 905, 247, 390)" << "\n /:";
		cin >> key;
		
		while (!cin) { //Validate for integer input
			cin.clear();
			cin.ignore();
			cin >> key;
		}

		return;
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