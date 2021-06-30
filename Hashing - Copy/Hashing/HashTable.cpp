#include "HashTableCore.h"

#pragma region [ Hashing Functions ]

namespace ht {
	
	 /// CHECK EMPTY
    /* Check if the hashtable is empty */
	bool HashTable::isEmpty() const {
		int numListPairs{}; //Size of list.

		for (int i{}; i < GetHashElements(); i++) {  //Iterate through each list
			numListPairs += mHashTable[i].size(); //Sum the size of the list within the array
		}

		if (!numListPairs) { //If the sum is 0
			cout << "\n [1]> Hashtable is empty." << endl;
			return true;  //return true
		}

		cout << "\n [1]> Hashtable is populated." << endl;
		return false; //Else return false
	}

#pragma region [ Hashing Functions ]

	 /// HASHING FUNCTION
    /* PJWs ELF Hash is a non-cryptographic hash function */
	unsigned long HashTable::HashFuncELF(string key) {
		unsigned long hashedKey = 0;
		unsigned int high = 0;

		for (int i = 0; i < key.size(); i++) {
			hashedKey = (hashedKey << 4) + key[i];
			if (high = hashedKey & 0xF00000000L) {
				hashedKey ^= (high >> 24);
			}
			hashedKey &= ~high;
		}

		return (hashedKey & 0x7FFFFFFFFF) % GetHashElements();
	}

	/* Implement the hashing algorithm for a string */
	unsigned int HashTable::HashFunction(int key) {
		unsigned int hashedValue(0);

		hashedValue = key + (hashedValue << 4) + (hashedValue << 10) - hashedValue; //Hash each character!

		return hashedValue % GetHashElements();
	}

#pragma endregion

	 /// INSERT ITEM
    /* Insert an item into the hashtable */
	void HashTable::InsertItem(string keyToInsert, int data) {
		int hashedValue = HashFuncELF(keyToInsert);	 //The hashed value of the key

		auto& pairPos = mHashTable[hashedValue];//Identify the list that the hashed value will go in to
		auto bIter = begin(pairPos);		  //Iterate from the beginning of the hashTable list

		bool keyExists = false;				//Check if key exists

		for (bIter; bIter != end(pairPos); bIter++) { //Iterate to the end of the list
			if (bIter->first == keyToInsert) {		 //If the first element is equivelent to the key
				keyExists = true;				    //Acknowledge it exists,
				bIter->second = data;			   //and replace the keys corresponding value

				cout << "[2]INSERT> Item inserted." << endl;
				break;
			}
		}

		if (!keyExists) {							  //If the key doesnt exist
			pairPos.emplace_back(keyToInsert, data); //Push key, value back into list
		}

		return;
	}

	 /// REMOVE ITEM
    /* Remove an item from the list */
	void HashTable::RemoveItem(string keyToRemove) {
		int hashedValue = HashFuncELF(keyToRemove); //Use hashed value to locate the key to remove

		auto& listPos = mHashTable[hashedValue]; //Identify the list that the hashed value will go in to
		auto bIter = begin(listPos);		    //Iterate from the beginning of the hashTable list

		bool keyExists = false;				  //Check if key exists

		for (bIter; bIter != end(listPos); bIter++) { //Iterate to the end of the list
			if (bIter->first == keyToRemove) {			//If the first element is equivelent to the key
				keyExists = true;					   //Acknowledge it exists,
				bIter = listPos.erase(bIter);		  //and erase where the iterator is pointing to

				cout << "[3]REMOVE> Item removed." << endl;
				break;
			}
		}

		if (!keyExists) { //If the key doesnt exist or wasn't removed
			cout << "[3]ERROR> Key not found." << endl;
		}
		return;
	}

	 /// PRINT HASHTABLE
    /* Print the hashtable to the console */
	void HashTable::PrintTable() {
		cout << " |[4]PRINT> " << endl;

		for (int i{}; i < GetHashElements(); i++) {			 //Iterate through the arrays lists
			cout <<	" |[" << i << "]> |Key: - - " << " |Data: - - " << endl;

			auto bItr = mHashTable[i].begin();				  //Create a new iterator
			for (bItr; bItr != mHashTable[i].end(); bItr++) { //iterate through the list
				cout <<										//Print each key and value
					" |[" << i << "]> |Key: " << bItr->first << " |Data: " << bItr->second << endl;
			}
		}

		return;
	}
}

#pragma endregion