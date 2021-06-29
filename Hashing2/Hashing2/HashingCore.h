#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <list>

namespace fs = std::experimental::filesystem;
using namespace std;

namespace ht {
	class HashTable {
		struct HashElement {
			/// Variables
			string mKey;
			int mValue;

		public:
			/// Hash Function Declarations
			string GetKey();
			int GetValue();

			string SetKey(string key);
			int SetValue(int value);
		};

	public:
		/// Function Declarations
		unsigned int HashFunction();
		void InsertItem();
		void RemoveItem();
		void PrintTable();
		bool isEmpty();
		string SearchKey();
	};
}