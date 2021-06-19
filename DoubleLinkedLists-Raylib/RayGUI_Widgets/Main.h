#pragma once
#include <iostream>
#include <string>

#include "DLLCore.h"

using namespace std;
using namespace DLL;

DLL::LinkedList dll;

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#define RAYGUI_STATIC

#include "raylib.h"
#include "raygui.h"

#undef RAYGUI_IMPLEMENTATION

/// VARIABLES
int selectionIndex = 0;


/// FUNCTION DECLARATIONS
void Init();
void DrawOptions();