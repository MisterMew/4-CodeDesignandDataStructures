#include "MainCore.h"

bool FileExists(string filepath) {
	struct stat buffer;
	return (stat(filepath.c_str(), &buffer) == 0);
}

#pragma region [ MENU Functions ]

 /// HASH MENU: View Menu
/* View menu options for hashtable */
void HashMenuOptions() {
	cout <<
		"\n HASHING OPTIONS"
		"\n [1] Check List"
		"\n [2] Insert Item"
		"\n [3] Remove Item"
		"\n [4] Print Table"
		"\n [0] EXIT"
		<< endl;
}

 /// HASH MENU: Validat Input
/* Validate user input for insert/remove */
void ValidateKey() {
	 /// INSERT Item
	// Validate user input when inserting an item to the table
	if (optSelected == OptSelect::InsertItem) {
		cout << "\n [2]TIP!> If nothing happenes, the input was illegal.";
		cout << "\n [2]INSERT> Please enter a key. (EG: Alpha, Bravo2, CH4RL13)" << "\n /: ";
		cin >> gKey;

		cout << "\n [2]INSERT> Please enter some data. (EG: 905, 247, 390)" << "\n /: ";
		cin >> gData;

		while (!cin) { //Validate for integer input
			cin.clear();
			cin.ignore();

			cout << "\n /: ";
			cin >> gData;
		}

		return;
	}

	 /// REMOVE Item
	// Validate user input when removing an item from the table
	if (optSelected == OptSelect::RemoveItem) {
		cout << "\n [3]DELETE> Please enter a key. (EG: Alpha, Bravo2, CH4RL13)" << "\n /: ";
		getline(cin, gKey);

		return;
	}
}

 /// HASH MENU: Validate Menu Input
/* Validate user input for selecting a menu option */
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
			HT.InsertItem(gKey, gData);
			continue;

		 ///REMOVE ITEM
		// Remove an item from the hashtable
		case OptSelect::RemoveItem:
			optSelected = OptSelect::RemoveItem;
			flag = false;
			ValidateKey();
			HT.RemoveItem(gKey);
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