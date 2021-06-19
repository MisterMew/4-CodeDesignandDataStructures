#include "EntityEditorApp.h"
#include <random>
#include <time.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

#include "raygui.h"


EntityEditorApp::EntityEditorApp(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight) {}

EntityEditorApp::~EntityEditorApp() {}

bool EntityEditorApp::Startup() {
	InitWindow(m_screenWidth, m_screenHeight, "EntityDisplayApp");
	SetTargetFPS(60);

	int sizeOfData = sizeof(int) + mEntityCount * sizeof(Entity);

	///Create Shared Memory Block
	//Handle to existing virtual file | optional security attributes | read/write acces | 0 to sizeof memory block
	fileHandle = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeOfData, L"SharedMemory");

	if (fileHandle == nullptr) {
		cout << "\n Shared Memory NOT Allocated." << endl;
		exit(0);
	}
	else {
		cout << "\n Shared Memory Allocated." << endl;
	}

	srand(time(nullptr));
	for (auto& entity : mEntities) {
		entity.x = rand() % m_screenWidth;
		entity.y = rand() % m_screenHeight;
		entity.size = rand() % 50;
		entity.speed = rand() % 100;
		entity.rotation = rand() % 360;
		entity.r = rand() % 255;
		entity.g = rand() % 255;
		entity.b = rand() % 255;
	}

	int* data = (int*)MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
	*data = ENTITY_COUNT;
	Entity* myEnt = (Entity*)(data + 1);

	myEnt->x = 21;
	myEnt->y = 69;
	myEnt->r = 1;
	myEnt->g = 2;
	myEnt->b = 3;
	myEnt->rotation = 360;
	myEnt->speed = 2145;

	UnmapViewOfFile(myEnt);
	
	return true;
}

void EntityEditorApp::Shutdown() {
	CloseHandle(fileHandle);
	CloseWindow(); // Close window and OpenGL context
}

void EntityEditorApp::Update(float deltaTime) {
	// select an entity to edit
	static int selection = 0;

	static bool selectionEditMode = false;
	static bool xEditMode = false;
	static bool yEditMode = false;
	static bool rotationEditMode = false;
	static bool sizeEditMode = false;
	static bool speedEditMode = false;

	static Color colorPickerValue = WHITE;

	if (GuiSpinner(Rectangle{ 90, 25, 125, 25 }, "Entity", &selection, 0, ENTITY_COUNT - 1, selectionEditMode)) selectionEditMode = !selectionEditMode;
	
	int intX = (int)mEntities[selection].x;	
	int intY = (int)mEntities[selection].y;
	int intRotation = (int)mEntities[selection].rotation;
	int intSize = (int)mEntities[selection].size;
	int intSpeed = (int)mEntities[selection].speed;


	// display editable stats within a GUI	
	GuiGroupBox(Rectangle{ 25, 70, 480, 220 }, "Entity Properties");

	if (GuiValueBox(Rectangle{ 90, 90, 125, 25 }, "x", &intX, 0, m_screenWidth, xEditMode)) xEditMode = !xEditMode;
	mEntities[selection].x = intX;

	if (GuiValueBox(Rectangle{ 90, 120, 125, 25 }, "y", &intY, 0, m_screenHeight, yEditMode)) yEditMode = !yEditMode;
	mEntities[selection].y = intY;

	mEntities[selection].rotation = GuiSlider(Rectangle{ 90, 150, 125, 25 }, "rotation", TextFormat("%2.2f", mEntities[selection].rotation), mEntities[selection].rotation, 0, 360);
	mEntities[selection].size = GuiSlider(Rectangle{ 90, 180, 125, 25 }, "size", TextFormat("%2.2f", mEntities[selection].size), mEntities[selection].size, 0, 100);
	mEntities[selection].speed = GuiSlider(Rectangle{ 90, 210, 125, 25 }, "speed", TextFormat("%2.2f", mEntities[selection].speed), mEntities[selection].speed, 0, 1000);
	
	colorPickerValue = GuiColorPicker(Rectangle{ 260, 90, 156, 162 }, Color{ mEntities[selection].r, mEntities[selection].g, mEntities[selection].b });
	mEntities[selection].r = colorPickerValue.r;
	mEntities[selection].g = colorPickerValue.g;
	mEntities[selection].b = colorPickerValue.b;


	// move entities

	for (int i = 0; i < ENTITY_COUNT; i++) {
		if (selection == i)
			continue;

		float s = sinf(mEntities[i].rotation) * mEntities[i].speed;
		float c = cosf(mEntities[i].rotation) * mEntities[i].speed;
		mEntities[i].x -= s * deltaTime;
		mEntities[i].y += c * deltaTime;

		// wrap position around the screen
		mEntities[i].x = fmod(mEntities[i].x, m_screenWidth);
		if (mEntities[i].x < 0)
			mEntities[i].x += m_screenWidth;
		mEntities[i].y = fmod(mEntities[i].y, m_screenHeight);
		if (mEntities[i].y < 0) {
			mEntities[i].y += m_screenHeight;
		}
	}

	int* data = (int*)MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
	if (data) {
		*data = mEntityCount;
		Entity* entityPointer = (Entity*)(data + 1);
		for (int i = 0; i < mEntityCount; i++) {

			*entityPointer = mEntities[i];
			entityPointer++;
		}
	}

}

void EntityEditorApp::Draw() {
	BeginDrawing();

	ClearBackground(RAYWHITE);

	// draw entities
	for (auto& entity : mEntities) {
		DrawRectanglePro(
			Rectangle{ entity.x, entity.y, entity.size, entity.size }, // rectangle
			Vector2{ entity.size / 2, entity.size / 2 }, // origin
			entity.rotation,
			Color{ entity.r, entity.g, entity.b, 255 });
	}

	// output some text, uses the last used colour
	DrawText("Press ESC to quit", 630, 15, 12, LIGHTGRAY);

	EndDrawing();
}