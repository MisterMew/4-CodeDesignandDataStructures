#include "BinaryTreeCore.h"
#include "TreeNodeCore.h"
#include "raylib.h"

BinaryTree::BinaryTree() {
	mRoot_ptr = nullptr;
}

BinaryTree::~BinaryTree() {
	while (mRoot_ptr) {
		DeleteNode(mRoot_ptr->NodeData());
	}
}


void BinaryTree::InsertNode(int newData) {
	TreeNode* newNode = new TreeNode();
}

void BinaryTree::DeleteNode(int nodeToDelete) {}

 /// FIND NODE
/* Search by a nodes value */
TreeNode* BinaryTree::SearchFor(int dataToFind) {
	TreeNode* currentNode = mRoot_ptr;
	TreeNode* parentNode = nullptr;

	while (currentNode != nullptr) {
		if (dataToFind == currentNode->NodeData()) { return currentNode, parentNode; }

		if (dataToFind < currentNode->NodeData()) {
			currentNode->LeftNode();
		}
		else {
			currentNode->RightNode(); 
		}
	}

	return FindNode(dataToFind, currentNode, parentNode) ? currentNode : nullptr;
}

bool BinaryTree::FindNode(int dataToSearch, TreeNode*& outNode_dblptr, TreeNode*& OutParent_dblptr) {
	return false;
}

 /// DRAW
/* Draw the binary trees root node */
void BinaryTree::DrawRoot(TreeNode* selectedNode) {
	DrawTree(mRoot_ptr, 400, 40, 400, selectedNode);
}

/* Draw the binary trees nodes */
void BinaryTree::DrawTree(TreeNode* currentNode, int posX, int posY, int horizontalSpacing, TreeNode* selectedNode) {
	if (mRoot_ptr == nullptr) { return; }
	horizontalSpacing /= 2;

	if (currentNode) {
		if (currentNode->BranchesLeft()) {
			DrawLine(posX, posY, (posX - horizontalSpacing), (posY + 80), BEIGE);

			DrawTree(currentNode->LeftNode(), posX - horizontalSpacing, posY + 80, horizontalSpacing, selectedNode);
		}

		if (currentNode->BranchesRight()) {
			DrawLine(posX, posY, (posX + horizontalSpacing), (posY + 80), BEIGE);

			DrawTree(currentNode->RightNode(), posX + horizontalSpacing, posY + 80, horizontalSpacing, selectedNode);
		}

		currentNode->DrawNode(posX, posY, (selectedNode == currentNode));
	}
}