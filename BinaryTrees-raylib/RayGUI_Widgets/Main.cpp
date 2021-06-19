#include "Main.h"
#include "BinaryTreeCore.h"
#include "TreeNodeCore.h"

 /// INITIALISATION
/* Program initialisation */
void Init() {
	const int screenWidth = 1280;  //Set screen width
	const int screenHeight = 720; //Set screen height

	InitWindow(screenWidth, screenHeight, "Binary Trees - Raylib"); //Initialise raylib window dimensions and change title
	SetTargetFPS(60); //Set the target FPS

	SetExitKey(0);
}

 /// DRAW OPTIONS
/* Draw the menu options to interact with the DLL */
void DrawOptions() {
	
	GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_CENTER);

	if (GuiValueBox(Rectangle{ 5, 15, 125, 30 }, NULL, &valueBoxValue, 0, 100, valueBoxEditMode)) {
		valueBoxEditMode = !valueBoxEditMode;
	}

	if (GuiButton(Rectangle{ 5, 50, 125, 30 }, GuiIconText(RICON_OK_TICK, "INSERT NODE"))) {}
	if (GuiButton(Rectangle{ 5, 85, 125, 30 }, GuiIconText(RICON_CROSS, "DELETE NODE"))) {}
}

 /// Main
int main() {
	Init(); //Initialisation

	bool exitWindow = false;
	while (!exitWindow) {
		exitWindow = WindowShouldClose();
		
		/// Update
	#pragma region [ Update ]

	#pragma endregion

		/// Draw
	#pragma region [ Drawing ]

		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawOptions();

		EndDrawing();

	#pragma endregion
	}

	CloseWindow();
}