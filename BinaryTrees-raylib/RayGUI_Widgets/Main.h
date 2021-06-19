#pragma once

//* TO DO *//
// Insert new value
// Remove a value
// Find a value
// Display binary tree

#include <iostream>
#include <string>

using namespace std;

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#define RAYGUI_STATIC

#include "raylib.h"
#include "raygui.h"

#include "BinaryTreeCore.h"
#include "TreeNodeCore.h"

#undef RAYGUI_IMPLEMENTATION


/// Variable Declarations
int valueBoxValue = 0;
bool valueBoxEditMode = false;


/// Function Declarations
void Init();
void DrawOptions();