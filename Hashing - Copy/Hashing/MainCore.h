#pragma once

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <fstream>
#include <experimental/filesystem>

#include "HashTableCore.h"

using namespace std;
using namespace ht;

namespace fs = std::experimental::filesystem;

ht::HashTable HT;

/// NOTE*
// I have sinced gained a better understranding of hashing and how theyre supposed to work. 
// Considering this and the feedback I recieve for this piece, I will start a new hashing project
// that better demonstrates my understanding and submit that.

/// VARIABLES
bool exitConsole = false;
int userInput;

string filepath, filename;
string gKey;
int gData;

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
bool FileExists(string filepath);

void HashMenuOptions();
void ValidateKey();
void MenuValidation();