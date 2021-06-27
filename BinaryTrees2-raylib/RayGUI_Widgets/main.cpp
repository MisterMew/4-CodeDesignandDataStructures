#include <iostream>

using namespace std;

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#define RAYGUI_STATIC

#include "raygui.h"
#include "BinaryTree.h"

#undef RAYGUI_IMPLEMENTATION

int valueBoxValue = 0;
bool valueBoxEditMode = false;

/// INITIALISATION
/* Program initialisation */
void Init() {
	const int screenWidth = 1280;  //Set screen width
	const int screenHeight = 720; //Set screen height

	InitWindow(screenWidth, screenHeight, "Binary Trees - Raylib"); //Initialise raylib window dimensions and change title
	SetTargetFPS(60); //Set the target FPS

	SetExitKey(0);
}

int main() { 
	Init();

	BinaryTree binaryTree;

	bool exitWindow = false;
	while (!exitWindow) {
		exitWindow = WindowShouldClose();

#pragma region [ Drawing ]

		BeginDrawing();

		ClearBackground(RAYWHITE);

		/// DRAW OPTIONS
	   /* Draw the menu options to interact with the DLL */
		GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_CENTER);

		if (GuiValueBox(Rectangle{ 5, 15, 125, 30 }, NULL, &valueBoxValue, 0, 100, valueBoxEditMode)) {
			valueBoxEditMode = !valueBoxEditMode;
		}

		if (GuiButton(Rectangle{ 5, 50, 125, 30 }, GuiIconText(RICON_OK_TICK, "INSERT NODE"))) {
			binaryTree.Insert(valueBoxValue);
		}
		if (GuiButton(Rectangle{ 5, 85, 125, 30 }, GuiIconText(RICON_CROSS, "DELETE NODE"))) {
			binaryTree.Delete(valueBoxValue);
		}
		if (binaryTree.GetRoot() != nullptr) {
			binaryTree.Display();
		}

		EndDrawing();

#pragma endregion
	}

	CloseWindow();
}