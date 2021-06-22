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

 /// INSERT NODE
/* Insert Node to tree */
void TreeNode::InsertNode(int newData) {
	TreeNode* newNode = new TreeNode(newData, nullptr, nullptr, nullptr);
	TreeNode* currentNode = this;

	if (mParent_ptr != nullptr) {
		if (mParent_ptr->RightNode() == nullptr && newData > mParent_ptr->NodeData()) {
			mParent_ptr->mRight_ptr = newNode;
			return;
		}

		if (mParent_ptr->LeftNode() == nullptr && newData < mParent_ptr->NodeData()) {
			mParent_ptr->mLeft_ptr = newNode;
			return;
		}
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


 /// DELETE NODE MANAGER
/* Decide how to delete nodes depending on parent/child conditions */
#pragma region [ Delete Nodes ]
void TreeNode::DeleteNode(TreeNode* mNodeToDelete) {
	TreeNode* nodeToDelete = mNodeToDelete;

	/// DELETE Leaf node
	if (nodeToDelete->RightNode() == nullptr && nodeToDelete->LeftNode() == nullptr) {
		DeleteLeaf(nodeToDelete);
	}

	/// DELETE with left child only
	if (nodeToDelete->RightNode() == nullptr) {
		DeleteLeft(nodeToDelete);
		return;
	}

	/// DELETE with right child only
	if (nodeToDelete->LeftNode() == nullptr) {
		DeleteRight(nodeToDelete);
	}

	/// DELETE with children
	if (nodeToDelete->RightNode() != nullptr && nodeToDelete->LeftNode() != nullptr) {
		DeleteParent(nodeToDelete);
		return;
	}
}

 /// DELETE LEAF NODE
/* Delete Leaf node from tree */
void TreeNode::DeleteLeaf(TreeNode* mNodeToDelete) {
	TreeNode* nodeToDelete = mNodeToDelete;

	/// Right Node
	if (nodeToDelete->NodeData() > nodeToDelete->Parent()->NodeData()) { //If nodeToDelete is right of parent
		nodeToDelete->Parent()->SetRight(nullptr);						//Detach from parent
	}

	/// Left Node
	if (nodeToDelete->NodeData() < nodeToDelete->Parent()->NodeData()) { //If nodeToDelete is left of parent
		nodeToDelete->Parent()->SetLeft(nullptr);						//Detach from parent
	}

	delete nodeToDelete; //Delete the node
}

 /// DELETE LEFT NODE
/* Delete node with left branch child */
void TreeNode::DeleteLeft(TreeNode* mNodeToDelete) {
	TreeNode* nodeToDelete = mNodeToDelete;

	if (nodeToDelete->NodeData() > nodeToDelete->Parent()->NodeData()) { //If nodeToDelete is right of parent
		nodeToDelete->LeftNode()->SetParent(nodeToDelete->Parent());	//Re-parent nodeToDeletes left node
		nodeToDelete->Parent()->SetRight(nodeToDelete->LeftNode());	   //Set parents right node
	}

	else {															  //If nodeToDelete is left of parent
		nodeToDelete->LeftNode()->SetParent(nodeToDelete->Parent()); //Re-parent nodeToDeletes left node
		nodeToDelete->Parent()->SetLeft(nodeToDelete->LeftNode());  //Set parents left node
	}

	delete nodeToDelete; //Delete Node
}

 /// DELETE RIGHT NODE
/* Delete node with right branch child */
void TreeNode::DeleteRight(TreeNode* mNodeToDelete) {
	TreeNode* nodeToDelete = mNodeToDelete;

	if (nodeToDelete->NodeData() > nodeToDelete->Parent()->NodeData()) { //If nodeToDelete is right of parent
		nodeToDelete->RightNode()->SetParent(nodeToDelete->Parent());	//Re-parent nodeToDeletes right node
		nodeToDelete->Parent()->SetRight(nodeToDelete->RightNode());   //Set parents right node
	}

	else {															   //If nodeToDelete is left of parent
		nodeToDelete->RightNode()->SetParent(nodeToDelete->Parent()); //Re-parent nodeToDeletes right node
		nodeToDelete->Parent()->SetLeft(nodeToDelete->RightNode());  //Set parents left node
	}

	delete nodeToDelete; //Delete Node
}

 /// DELETE PARENT NODE
/* Delete node with two children */
void TreeNode::DeleteParent(TreeNode* mNodeToDelete) {
	TreeNode* minNode = mNodeToDelete->RightNode();

	while (minNode->LeftNode() != nullptr) { //Loop through all left nodes
		minNode = minNode->LeftNode();		//Set next node
	}

	mNodeToDelete->SetData(minNode->NodeData()); //Dynamically set the nodeToDelete to the end-most node

	if (minNode->RightNode() == nullptr) { //Check for no more children
		DeleteLeaf(minNode);			  //Call function to delete leaf
		return;
	}

	DeleteRight(minNode); //Call function to delete with right
}

#pragma endregion

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

	DrawText(buffer, posX - 10, posY - 8, 18, RAYWHITE);
}