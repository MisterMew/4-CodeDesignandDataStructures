#pragma once
#include <iostream>
#include <cstring>
#include <list>

using namespace std;

namespace ht {
	/// HASH TABLE DECLARATIONS
	class HashTable {
	private:
		static const int hashGroups = 10; //constant amount of lists
		list<pair<int, string>> table[hashGroups]; //Store pairs

	public:
		bool isEmpty() const;
		int HashFunction(int key);
		void InsertItem(int key, string name);
		void RemoveItem(int key);
		int SearchKey(int key);
		void PrintTable();
	};
}