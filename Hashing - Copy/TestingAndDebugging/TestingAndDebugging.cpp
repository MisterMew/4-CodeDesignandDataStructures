#include "pch.h"
#include "CppUnitTest.h"

#include "../Hashing/HashTableCore.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ht;

namespace TestingAndDebugging {
	TEST_CLASS(TestingAndDebugging) {
	public:
		HashTable hash;

		TEST_METHOD(TestTest) {}

		TEST_METHOD(TestHashElements) {
			static const int mHashElements = 10;
			Assert::AreEqual(10, ht::HashTable::GetHashElements()); //Expected 10 | Actual: mHashElements
		}

		TEST_METHOD(TestHashStr) {
			string key = "KittyFishtank.PNG";
			Assert::AreEqual(2823697703, ht::HashTable::HashFuncELF(key));
		}

		TEST_METHOD(TestHashInt) {
			unsigned int key = 420;
			Assert::AreEqual(420, ht::HashTable::HashFunction(key));
		}

		TEST_METHOD(TestInsertElement) {
			void InsertItem(string keyToInsert, int data);
		}
	};
}
