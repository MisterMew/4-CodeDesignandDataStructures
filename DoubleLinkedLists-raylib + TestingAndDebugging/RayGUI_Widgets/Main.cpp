#include "Main.h"

 /// INITIALISATION
/* Program initialisation */
void Init() {
	const int screenWidth = 1280;  //Set screen width
	const int screenHeight = 720; //Set screen height

	InitWindow(screenWidth, screenHeight, "Double Linked Lists - Visual Representation"); //Initialise raylib window dimensions and change title
	SetTargetFPS(60); //Set the target FPS

	SetExitKey(0);
}

 /// DRAW OPTIONS
/* Draw the menu options to interact with the DLL */
void DrawOptions() {
	//Menu Options
	DrawText("DOUBLE LINKED LISTS", 5, 0, 18, BLACK); 
	DrawText(("Use the < and > arrow keys to select a Node, then press any button from the options below. It's not perfect, but its there :)"), 5, 20, 16, DARKGRAY);
	DrawFPS(1200, 5);

	DrawText("Nodes Count:", 5, 700, 16, DARKGRAY);
	static char nodeCount[10];
	sprintf(nodeCount, "%d", dll.CountNodes());
	DrawText(nodeCount, 120, 700, 16, MAROON);

#pragma region [ Insert Node Buttons ]
	/// INSERT NODE BUTTONS
	if (GuiButton(Rectangle{ 5,  50, 125, 30 }, GuiIconText(RICON_OK_TICK, "INSERT HEAD"))) {
		dll.InsertHead(dll.CreateData());
	}

	if (GuiButton(Rectangle{ 5,  85, 125, 30 }, GuiIconText(RICON_OK_TICK, "INSERT NODE"))) {
		dll.InsertNode(dll.CreateData(), selectionIndex);
	}

	if (GuiButton(Rectangle{ 5, 120, 125, 30 }, GuiIconText(RICON_OK_TICK, "INSERT TAIL"))) {
		dll.InsertTail(dll.CreateData());
	}
#pragma endregion

#pragma region [ Delete Node Buttons ]
	/// DELETE NODE BUTTONS
	if (GuiButton(Rectangle{ 140, 50, 125, 30 }, GuiIconText(RICON_CROSS, "DELETE HEAD"))) {
		dll.DeleteHead();
	}

	if (GuiButton(Rectangle{ 140, 85, 125, 30 }, GuiIconText(RICON_CROSS, "DELETE NODE"))) {
		dll.DeleteNode(selectionIndex);
	}

	if (GuiButton(Rectangle{ 140, 120, 125, 30 }, GuiIconText(RICON_CROSS, "DELETE TAIL"))) {
		dll.DeleteTail();
	}
#pragma endregion

	/// OTHER BUTTONS
	if (GuiButton(Rectangle{ 280, 50, 125, 30 }, GuiIconText(RICON_FILTER, "SORT LIST  "))) {
		dll.SortList();
	}
		
	dll.DrawNodes(selectionIndex);
}

/// MAIN
int main() {
	Init(); //Initialisation
	
	bool exitWindow = false;
	while (!exitWindow)	{
		exitWindow = WindowShouldClose();

	#pragma region [ Update ]
		
		if (IsKeyPressed(KEY_LEFT)) {
			selectionIndex--;
			if (selectionIndex < 0) {
				selectionIndex = dll.CountNodes() - 1;
			}
		}

		if (IsKeyPressed(KEY_RIGHT)) {
			selectionIndex++;
			if (selectionIndex > dll.CountNodes() - 1) {
				selectionIndex = 0;
			}
		}

	#pragma endregion

	#pragma region [ Drawing ]

		BeginDrawing();
		
		ClearBackground(RAYWHITE);
		DrawOptions();
		
		EndDrawing();

	#pragma endregion
	}

	CloseWindow();
}