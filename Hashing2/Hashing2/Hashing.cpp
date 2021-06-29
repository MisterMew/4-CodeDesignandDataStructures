#include "HashingCore.h"

namespace ht {

	/* Function GET Definitions */
	string HashTable::HashElement::GetKey() { return mKey; }
	int HashTable::HashElement::GetValue() { return mValue; }

	/* Function SET Definitions */
	string HashTable::HashElement::SetKey(string key) { mKey = key; }
	int HashTable::HashElement::SetValue(int value) { mValue = value; }
}