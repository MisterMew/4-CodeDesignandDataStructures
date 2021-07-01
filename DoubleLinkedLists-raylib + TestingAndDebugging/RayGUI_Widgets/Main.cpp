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

#pragma region // Draw List //

/// DRAW NODES
/* Draw the dll nodes */
void DrawNodes(int selectedNode) {
	if (dll.GetNodeCount() <= 0) {													 //If the list is empty
		const string txtEmptyList = "[THE DOUBLE LINKED LIST IS EMPTY]";			//The message I want to display (below converted from string to char)
		DrawText(txtEmptyList.c_str(), 450, GetScreenHeight() / 2, 20, LIGHTGRAY); //Display at the screens center
		return;																	  //Exit Function
	}

	/// VARIABLES
	const int outerRadius = 30;
	const int innerRadius = 27;
	int i = 0;

	DoubleLinkedList::Node* node = dll.GetHead();

	while (node != nullptr) {
		if (node == nullptr) { return; }

		int posX = ((GetScreenWidth()) / dll.GetNodeCount()) * i + outerRadius; //Calculate x position
		int posY = (GetScreenHeight() / 2);							   //Calculate y position

		///Convert int to string for raylib use
		static char nodeText[10]; //Create a static char buffer
		sprintf(nodeText, "%d", node->data);

		//Draw HEAD node Red
		if (node == dll.GetHead()) {
			DrawCircle(posX, posY, outerRadius, MAROON);
			DrawCircle(posX, posY, innerRadius, RED);
		}

		//Draw TAIL node Orange
		if (node == dll.GetTail()) {
			DrawCircle(posX, posY, outerRadius, ORANGE);
			DrawCircle(posX, posY, innerRadius, GOLD);
		}

		//Draw every other Node Brown
		if (node != dll.GetHead() && node != dll.GetTail()) {
			DrawCircle(posX, posY, outerRadius, BROWN);
			DrawCircle(posX, posY, innerRadius, BEIGE);
		}

		//Draw selected Node Grey
		if (i == selectedNode) {
			DrawCircle(posX, posY, outerRadius, LIGHTGRAY);
			DrawCircle(posX, posY, innerRadius, GRAY);

			//Make the selected nodes data appear above the list
			DrawText(nodeText, ((GetScreenWidth() / 2) - (sizeof(nodeText))), ((GetScreenHeight() / 3)), 40, MAROON);
		}

		DrawText(nodeText, posX - (sizeof(nodeText) * 2), posY - 10, 20, RAYWHITE); //Draw each nodes data

		i++; //Increment
		node = node->next; //Iterate to next node
	}
}

#pragma endregion

 /// DRAW OPTIONS
/* Draw the menu options to interact with the DLL */
void DrawOptions() {
	//Menu Options
	DrawText("DOUBLE LINKED LISTS", 5, 0, 18, BLACK); 
	DrawText(("Use the < and > arrow keys to select a Node, then press any button from the options below. It's not perfect, but its there :)"), 5, 20, 16, DARKGRAY);
	DrawFPS(1200, 5);

	DrawText("Nodes Count:", 5, 700, 16, DARKGRAY);
	static char nodeCount[10];
	sprintf(nodeCount, "%d", dll.GetNodeCount());
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
		
	DrawNodes(selectionIndex);
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
				selectionIndex = dll.GetNodeCount() - 1;
			}
		}

		if (IsKeyPressed(KEY_RIGHT)) {
			selectionIndex++;
			if (selectionIndex > dll.GetNodeCount() - 1) {
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