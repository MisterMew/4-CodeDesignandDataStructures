#pragma once
#include <iostream>

#include "HashTableCore.h"

using namespace std;
using namespace ht;

ht::HashTable HT;

/// VARIABLES
bool exitConsole = false;
int userInput;
string name;
int key;

/* Menu Switch */
int optSelected;
enum OptSelect {
	Exit = 0,
	CheckTable,
	InsertItem,
	RemoveItem,
	PrintTable
};

/// FUNCTION DECLARATIONS
void HashMenuOptions();
void MenuValidation();