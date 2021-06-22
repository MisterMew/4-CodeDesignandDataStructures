#include "BinaryTreeCore.h"
#include "TreeNodeCore.h"
#include "raylib.h"

BinaryTree::BinaryTree() {
	mRoot_ptr = nullptr;
}

BinaryTree::~BinaryTree() {
	delete mRoot_ptr;
}

 /// INSERT NODE
/* Insert node from tree */
void BinaryTree::InsertNode(int newData) {
	if (mRoot_ptr == nullptr) { //If a rootNode doesnt exist
		mRoot_ptr = new TreeNode(newData, nullptr, nullptr, nullptr); //Create one
		return;
	}
	else {
		mRoot_ptr->InsertNode(newData); //Otherwise continue to insert conitions
	}
}

 /// DELETE NODE
/* Delete node from tree */
void BinaryTree::DeleteNode(int mNodeToDelete) {
	if (mRoot_ptr == nullptr) { return; }

	TreeNode* nodeToDelete = Get(mNodeToDelete);
	if (nodeToDelete != mRoot_ptr)
		mRoot_ptr->DeleteNode(nodeToDelete);
	else {
		delete mRoot_ptr;
		mRoot_ptr == nullptr;
	}
}

 /// FIND NODE
/* Search by a nodes value */
TreeNode* BinaryTree::Get(int dataToFind) { //Deleteing child nodes gets stick in the while loop
	TreeNode* currentNode = mRoot_ptr;
	TreeNode* parentNode = nullptr;

	while (currentNode != nullptr) {
		if (dataToFind == currentNode->NodeData()) { return currentNode; }

		if (dataToFind < currentNode->NodeData()) {
			currentNode = currentNode->LeftNode();
		}
		else {
			currentNode = currentNode->RightNode();
		}
	}
	return FindNode(dataToFind, currentNode, parentNode) ? currentNode : nullptr;
}

bool BinaryTree::FindNode(int dataToSearch, TreeNode*& outNode, TreeNode*& outParent) {
	return false;
}

 /// DRAW
/* Draw the binary trees root node */
void BinaryTree::DrawRoot(TreeNode* selectedNode) {
	if (mRoot_ptr == nullptr) { return; }

	DrawTree(mRoot_ptr, GetScreenWidth() / 2, 40, 400, selectedNode);
}

/* Draw the binary trees nodes */
void BinaryTree::DrawTree(TreeNode* currentNode, int posX, int posY, int nodeSeperation, TreeNode* selectedNode) {
	if (mRoot_ptr == nullptr || currentNode == nullptr) { return; }

	TreeNode* nodeToDraw = currentNode; //Just making it easier to see
	nodeSeperation /= 2;

	if (nodeToDraw) {
		if (nodeToDraw->BranchesLeft()) {
			DrawLine(posX, posY, (posX - nodeSeperation), (posY + 80), BROWN);
			DrawTree(nodeToDraw->LeftNode(), (posX - nodeSeperation), (posY + 80), nodeSeperation, selectedNode);
		}

		if (nodeToDraw->BranchesRight()) {
			DrawLine(posX, posY, (posX + nodeSeperation), (posY + 80), BEIGE);
			DrawTree(nodeToDraw->RightNode(), (posX + nodeSeperation), (posY + 80), nodeSeperation, selectedNode);
		}

		nodeToDraw->DrawNode(posX, posY);
	}
}