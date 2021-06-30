#pragma once
#include <iostream>
#include <cstring>
#include <list>

using namespace std;

namespace ht {
	/// HASH TABLE DECLARATIONS
	class HashTable {
	private:
		/// VARIABLES
		static const int mHashElements = 10;			      //Constant number of lists
		list<pair<string, int>> mHashTable[mHashElements]; //List that stores data || List 1, Index 0. List 2, Index 1 . . .

	public:
		 /// GET Functions
		/* Function GET Definitions */
		static const int GetHashElements() { return mHashElements; }

		 /// FUNCTION DECLARATIONS
		/* HashTable Function Declarations */
		unsigned int HashFuncELF(string key);
		unsigned int HashFunction(int key);

		void InsertItem(string keyToInsert, int data);
		void RemoveItem(string keyToRemove);
		void PrintTable();

		bool isEmpty() const;
	};
}