#include "TreeNodeCore.h"
#include "raylib.h"

void TreeNode::DrawNode(int posX, int posY, bool isSelected = false) {
	static char buffer[10];
	sprintf(buffer, "%d", mNodeData);

	DrawCircle(posX, posY, 30, DARKGREEN);

	if (isSelected == true) {
		DrawCircle(posX, posY, 28, Fade(LIME, 0.5));
	}
	else {
		DrawCircle(posX, posY, 28, LIME);
	}

	DrawText(buffer, posX - 10, posY - 10, 18, BLACK);
}