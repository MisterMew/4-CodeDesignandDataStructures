#include "HashTableCore.h"

#pragma region [ Hashing Functions ]

namespace ht {
	
	 /// CHECK EMPTY
    /* Check if the hashtable is empty */
	bool HashTable::isEmpty() const {
		int numListPairs{}; //Cumulative size of list

		for (int i{}; i < hashGroups; i++) {
			numListPairs += table[i].size();
		}

		if (!numListPairs) {
			cout << "\n [1]> Hashtable is empty." << endl;
			return true;
		}

		cout << "\n [1]> Hashtable is populated." << endl;
		return false;
	}

	 /// HASH FUNCTION
    /* Implement the hashing algorithm */
	int HashTable::HashFunction(int key) {
		return key % hashGroups;
	}

	 /// INSERT ITEM
    /* Insert an item into the hashtable */
	void HashTable::InsertItem(int key, string value) {
		int hashValue = HashFunction(key); //Hashing the key
		auto& cell = table[hashValue];	  //Signify the list the key will go into
		auto bIterator = begin(cell);	 //Iterate from the beginning
		bool keyExists = false;			//Check if key exists

		for (; bIterator != end(cell); bIterator++) { //Iterate to the end of the list
			if (bIterator->first == key) {			 //If the first element is equivelent to the key
				keyExists = true;					//Acknowledge it exists,
				bIterator->second = value;		   //and replace the keys corresponding value

				cout << "[2]INSERT> Item inserted." << endl;
				break;
			}
		}

		if (!keyExists) {					//If the key doesnt exist
			cell.emplace_back(key, value); //push key back into list
		}

		return;
	}

	 /// REMOVE ITEM
    /* Remove an item from the list */
	void HashTable::RemoveItem(int key) {
		int hashValue = HashFunction(key); //Hashing the key
		auto& cell = table[hashValue];	  //Signify the list the key will go into
		auto bIterator = begin(cell);	 //Iterate from the beginning
		bool keyExists = false;			//Assume key doesnt exist

		for (; bIterator != end(cell); bIterator++) { //Iterate to the end of the list
			if (bIterator->first == key) {			 //If the first element is equivelent to the key
				keyExists = true;					//Acknowledge it exists,
				bIterator = cell.erase(bIterator);			   //and erase where the iterator is pointing to

				cout << "[3]REMOVE> Item removed." << endl;
				break;
			}
		}

		if (!keyExists) {					//If the key doesnt exist
			cout << "[3]ERROR> Key not found." << endl;
		}

		return;
	}

	 /// SEARCH HASHTABLE
    /* Search the hashtable for a key */
	int HashTable::SearchKey(int key) { return NULL; }

	 /// PRINT HASHTABLE
    /* Print the hashtable to the console */
	void HashTable::PrintTable() {
		if (isEmpty()) {
			cout << "\n [4]> Table is empty." << endl;
			return;
		}

		for (int i{}; i < hashGroups; i++) {
			if (table[i].size() == 0) { continue; }

			auto bIterator = table[i].begin();
			for (; bIterator != table[i].end(); bIterator++) {
				cout << " |[4]PRINT> |Key: " << bIterator->first << " |Name: " << bIterator->second << endl;
			}
		}
		return;
	}
}

#pragma endregion