#include "HashTableCore.h"

#pragma region [ Hashing Functions ]

namespace ht {
	
	 /// CHECK EMPTY
    /* Check if the hashtable is empty */
	bool HashTable::isEmpty() const {
		int numListPairs{}; //Size of list.

		for (int i{}; i < hashPairs; i++) {  //Iterate through each list
			numListPairs += hashTable[i].size(); //Sum the size of the list within the array
		}

		if (!numListPairs) { //If the sum is 0
			cout << "\n [1]> Hashtable is empty." << endl;
			return true;  //return true
		}

		cout << "\n [1]> Hashtable is populated." << endl;
		return false; //Else return false
	}

	 /// HASH FUNCTION
    /* Implement the hashing algorithm */
	int HashTable::HashFunction(int key) {
		return key % hashPairs; //Return the modulus of key, with hashgroups | Key: 420, return 0. Key: 692, return 2.
	}

	 /// INSERT ITEM
    /* Insert an item into the hashtable */
	void HashTable::InsertItem(int key, string value) {
		int hashedValue = HashFunction(key);	 //The hashed value of the key

		auto& listPos = hashTable[hashedValue];//Identify the list that the hashed value will go in to
		auto begItr = begin(listPos);		  //Iterate from the beginning of the hashTable list

		bool keyExists = false;				//Check if key exists

		for (begItr; begItr != end(listPos); begItr++) { //Iterate to the end of the list
			if (begItr->first == key) {					//If the first element is equivelent to the key
				keyExists = true;					   //Acknowledge it exists,
				begItr->second = value;				  //and replace the keys corresponding value

				cout << "[2]INSERT> Item inserted." << endl;
				break;
			}
		}

		if (!keyExists) {					   //If the key doesnt exist
			listPos.emplace_back(key, value); //Push key, value back into list
		}

		return;
	}

	 /// REMOVE ITEM
    /* Remove an item from the list */
	void HashTable::RemoveItem(int keyToRemove) {
		int hashedValue = HashFunction(keyToRemove);	 //Use hashed value to locate the key to remove

		auto& listPos = hashTable[hashedValue];//Identify the list that the hashed value will go in to
		auto begItr = begin(listPos);		  //Iterate from the beginning of the hashTable list

		bool keyExists = false;				//Check if key exists

		for (begItr; begItr != end(listPos); begItr++) { //Iterate to the end of the list
			if (begItr->first == keyToRemove) {			//If the first element is equivelent to the key
				keyExists = true;					   //Acknowledge it exists,
				begItr = listPos.erase(begItr);		  //and erase where the iterator is pointing to

				cout << "[3]REMOVE> Item removed." << endl;
				break;
			}
		}

		if (!keyExists) { //If the key doesnt exist or wasn't removed
			cout << "[3]ERROR> Key not found." << endl;
		}
		return;
	}

	 /// SEARCH HASHTABLE
    /* Search the hashtable for a key */
	///string HashTable::SearchKey(int key) { return; }

	 /// PRINT HASHTABLE
    /* Print the hashtable to the console */
	void HashTable::PrintTable() {
		for (int i{}; i < hashPairs; i++) {				 //Iterate through the arrays lists
			if (hashTable[i].size() == 0) { continue; } //If the size of the list is 0, continue

			auto bItr = hashTable[i].begin();				  //Create a new iterator
			for (bItr; bItr != hashTable[i].end(); bItr++) { //iterate through the list
				cout <<										//Print each key and value
					" |[4]PRINT> |Key: " << bItr->first << " |Name: " << bItr->second << endl; 
			}
		}
		return;
	}
}

#pragma endregion