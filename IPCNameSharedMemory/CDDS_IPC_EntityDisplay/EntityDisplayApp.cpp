#include "EntityDisplayApp.h"

EntityDisplayApp::EntityDisplayApp(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight) {}

EntityDisplayApp::~EntityDisplayApp() {}

bool EntityDisplayApp::Startup() {
	InitWindow(m_screenWidth, m_screenHeight, "EntityDisplayApp");
	SetTargetFPS(60);

	fileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"SharedMemory");

	int* entCount = (int*)MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));

	int entCountForReal = *entCount;

	Entity* mySharedEnt = (Entity*)(entCount + 1);

	for (int i = 0; i < entCountForReal; i++) {
		cout << "pushing" << endl;
		cout << "data: " << mySharedEnt->x << " " << mySharedEnt->y << " " << mySharedEnt->x << endl;
		mEntities.push_back(*mySharedEnt);
		mySharedEnt++;
	}

	UnmapViewOfFile(entCount);

	return true;
}

void EntityDisplayApp::Shutdown() {
	CloseHandle(fileHandle);
	CloseWindow(); //Close window and OpenGL context
}

void EntityDisplayApp::Update(float deltaTime) {}

/// DRAW ENTITIES
void EntityDisplayApp::Draw() {
	BeginDrawing();

	ClearBackground(RAYWHITE);

	int* data = (int*)MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
	if (data) {
		mEntityCount = *data;
		mEntities = std::vector<Entity>();
		Entity* entityPointer = (Entity*)(data + 1);
		for (int i = 0; i < mEntityCount; i++) {

			mEntities.push_back(*entityPointer);
			entityPointer++;

		}
	}

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

	UnmapViewOfFile(data);
	EndDrawing();
}