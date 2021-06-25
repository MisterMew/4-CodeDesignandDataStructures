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
		static const int hashPairs = 10;			   //Constant number of lists
		list<pair<int, string>> hashTable[hashPairs]; //List that stores data || List 1, Index 0. List 2, Index 1 . . .

	public:
		/// FUNCTION DECLARATIONS
		bool isEmpty() const;
		unsigned int HashFunction(int key);
		unsigned int HashFunction(string key);
		void InsertItem(int key, string name);
		void RemoveItem(int key);
		string SearchKey(int key);
		void PrintTable();
	};
}