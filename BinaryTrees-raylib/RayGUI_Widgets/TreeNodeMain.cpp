#include "TreeNodeCore.h"
#include "raylib.h"

TreeNode::TreeNode(int value) {
	mNodeData = value;
	mLeft_ptr = nullptr;
	mRight_ptr = nullptr;
}

TreeNode::~TreeNode() {
	delete mLeft_ptr;
	delete mRight_ptr;
}

void TreeNode::InsertNode(int newData) {
	TreeNode* newNode = new TreeNode(newData, nullptr, nullptr, nullptr);
	TreeNode* currentNode = this;

	while (currentNode != nullptr) {
		if (newNode->NodeData() == currentNode->NodeData()) { return; } //Return same-value nodes

		// Branch Right
		if (newNode->NodeData() > currentNode->NodeData() && currentNode->RightNode() == nullptr) {
			currentNode->SetRight(newNode);
			return;
		}

		// Branch Left
		if (newNode->NodeData() < currentNode->NodeData() && currentNode->LeftNode() == nullptr) {
			currentNode->SetLeft(newNode);
			return;
		}

		// Right
		if (newNode->NodeData() > currentNode->NodeData()) {
			if (currentNode->RightNode() != nullptr) {
				currentNode->RightNode()->InsertNode(newData);
			}
			else {
				currentNode->SetRight(newNode);
			}
		}

		// Left
		if (newNode->NodeData() < currentNode->NodeData()) {
			if (currentNode->LeftNode() != nullptr) {
				currentNode->LeftNode()->InsertNode(newData);
			}
			else {
				currentNode->SetLeft(newNode);
			}
		}
	}
}

 /// DRAW NODE
/* Draws the nodes */
void TreeNode::DrawNode(int posX, int posY, bool isSelected = false) {
	static char buffer[10];
	sprintf(buffer, "%d", mNodeData);

	DrawCircle(posX, posY, 30, ORANGE);

	if (isSelected == true) {
		DrawCircle(posX, posY, 28, Fade(GOLD, 0.5));
	}
	else {
		DrawCircle(posX, posY, 28, GOLD);
	}

	DrawText(buffer, posX - 10, posY - 10, 18, RAYWHITE);
}