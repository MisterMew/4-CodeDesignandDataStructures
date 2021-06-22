#include "TreeNodeCore.h"
#include "raylib.h"

TreeNode::TreeNode(int value) {
	mNodeData = value;
	mLeft_ptr = nullptr;
	mRight_ptr = nullptr;
}

 /// INSERT NODE
/* Insert Node to tree */
void TreeNode::InsertNode(int newData) {
	TreeNode* currentNode = this;

	if (mParent_ptr != nullptr) {
		if (mParent_ptr->RightNode() == nullptr && newData > mParent_ptr->NodeData()) {
			mParent_ptr->SetRight(new TreeNode(newData, mParent_ptr, nullptr, nullptr));
			return;
		}

		if (mParent_ptr->LeftNode() == nullptr && newData < mParent_ptr->NodeData()) {
			mParent_ptr->SetLeft(new TreeNode(newData, mParent_ptr, nullptr, nullptr));
			return;
		}
	}

	// Right
	if (newData > currentNode->NodeData()) {
		if (currentNode->RightNode() != nullptr) {
			currentNode->RightNode()->InsertNode(newData);
		}
		else {
			currentNode->SetRight(new TreeNode(newData, this, nullptr, nullptr));
		}
	}

	// Left
	if (newData < currentNode->NodeData()) {
		if (currentNode->LeftNode() != nullptr) {
			currentNode->LeftNode()->InsertNode(newData);
		}
		else {
			currentNode->SetLeft(new TreeNode(newData, this, nullptr, nullptr));
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
		return;
	}

	/// DELETE with children
	if (nodeToDelete->RightNode() != nullptr && nodeToDelete->LeftNode() != nullptr) {
		DeleteParent(nodeToDelete);
		return;
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
}

 /// DELETE LEAF NODE
/* Delete Leaf node from tree */
void TreeNode::DeleteLeaf(TreeNode* mNodeToDelete) {
	TreeNode* nodeToDelete = mNodeToDelete;

	/// Right Node
	if (nodeToDelete->NodeData() > nodeToDelete->Parent()->NodeData()) { //If nodeToDelete is right of parent
		nodeToDelete->Parent()->SetRight(nullptr);                        //Detach from parent
	}

	/// Left Node
	if (nodeToDelete->NodeData() < nodeToDelete->Parent()->NodeData()) { //If nodeToDelete is left of parent
		nodeToDelete->Parent()->SetLeft(nullptr);                        //Detach from parent
	}

	delete nodeToDelete; //Delete the node
	nodeToDelete = nullptr;
}

 /// DELETE LEFT NODE
/* Delete node with left branch child */
void TreeNode::DeleteLeft(TreeNode* mNodeToDelete) {
	TreeNode* nodeToDelete = mNodeToDelete;

	if (nodeToDelete->NodeData() > nodeToDelete->Parent()->NodeData()) { //If nodeToDelete is right of parent
		nodeToDelete->LeftNode()->SetParent(nodeToDelete->Parent());    //Re-parent nodeToDeletes left node
		nodeToDelete->Parent()->SetRight(nodeToDelete->LeftNode());       //Set parents right node
	}

	else {                                                              //If nodeToDelete is left of parent
		nodeToDelete->LeftNode()->SetParent(nodeToDelete->Parent()); //Re-parent nodeToDeletes left node
		nodeToDelete->Parent()->SetLeft(nodeToDelete->LeftNode());  //Set parents left node
	}

	delete nodeToDelete; //Delete Node
	nodeToDelete = nullptr;
}

 /// DELETE RIGHT NODE
/* Delete node with right branch child */
void TreeNode::DeleteRight(TreeNode* mNodeToDelete) {
	TreeNode* nodeToDelete = mNodeToDelete;

	if (nodeToDelete->NodeData() > nodeToDelete->Parent()->NodeData()) { //If nodeToDelete is right of parent
		nodeToDelete->RightNode()->SetParent(nodeToDelete->Parent());    //Re-parent nodeToDeletes right node
		nodeToDelete->Parent()->SetRight(nodeToDelete->RightNode());   //Set parents right node
	}

	else {                                                               //If nodeToDelete is left of parent
		nodeToDelete->RightNode()->SetParent(nodeToDelete->Parent()); //Re-parent nodeToDeletes right node
		nodeToDelete->Parent()->SetLeft(nodeToDelete->RightNode());  //Set parents left node
	}

	nodeToDelete->mParent_ptr == nullptr;
	nodeToDelete->mRight_ptr == nullptr;
	nodeToDelete = nullptr;

	delete nodeToDelete; //Delete Node
}

 /// DELETE PARENT NODE
/* Delete node with two children */
void TreeNode::DeleteParent(TreeNode* mNodeToDelete) {
	TreeNode* minNode = mNodeToDelete->RightNode();

	while (minNode->LeftNode() != nullptr) { //Loop through all left nodes
		minNode = minNode->LeftNode();        //Set next node
	}

	mNodeToDelete->SetData(minNode->NodeData()); //Dynamically set the nodeToDelete to the end-most node

	if (minNode->RightNode() == nullptr) { //Check for no more children
		DeleteLeaf(minNode);              //Call function to delete leaf
		return;
	}

	DeleteRight(minNode); //Call function to delete with right
}

#pragma endregion

 /// DRAW NODE
/* Draws the nodes */
void TreeNode::DrawNode(int posX, int posY) {
	static char buffer[10];
	sprintf(buffer, "%d", mNodeData);

	DrawCircle(posX, posY, 30, ORANGE); //Draw outer edge
	DrawCircle(posX, posY, 28, GOLD);  //Draw inside

	DrawText(buffer, posX - 10, posY - 8, 18, RAYWHITE); //Draw node data
}