#include "BinaryTree.h"

/* Get Root Node */
Node* BinaryTree::GetRoot() {
	return mRoot_ptr;
}

 /// INSERT NODE
/* Insert node from tree */
void BinaryTree::Insert(int newData) {
	if (mRoot_ptr == nullptr) {				     //If a rootNode doesn't exist
		mRoot_ptr = new Node(nullptr, newData); //Create a new root node
	}
	else {
		mRoot_ptr->Insert(newData); //Otherwise check for Insert conditions
	}
}

#pragma region [ Node Deletion Functions ]

 /// DELETE NODE
/* Delete node from tree */
void BinaryTree::Delete(int key) {
	Node* nodeToDelete = Search(key); //Search for the node via its data

	if (GetRoot() == nullptr || nodeToDelete == nullptr) { return; } //Check if node doesn't exist

	if (nodeToDelete->GetData() == GetRoot()->GetData()) { //If the node is the root
		delete mRoot_ptr;	  //Delete the root pointer
		mRoot_ptr = nullptr; //Set the root pointer to null
		return;				//Exit function
	}

	/// Delete Leaf node
	if (nodeToDelete->GetRight() == nullptr && nodeToDelete->GetLeft() == nullptr) {
		DeleteLeaf(nodeToDelete);
		return;
	}

	/// Delete Parent node
	if (nodeToDelete->GetRight() != nullptr && nodeToDelete->GetLeft() != nullptr) {
		DeleteParent(nodeToDelete);
		return;
	}

	/// Delete Right node
	if (nodeToDelete->GetRight() != nullptr) {
		DeleteRight(nodeToDelete);
		return;
	}

	/// Delete Left node
	if (nodeToDelete->GetLeft() != nullptr) {
		DeleteLeft(nodeToDelete);
	    //return;
	}
}

 /// DELETE LEAF NODE
/* Delete Leaf node from tree */
void BinaryTree::DeleteLeaf(Node* nodeToDelete) {
	///Delete Right leaf
	if (nodeToDelete->GetData() > nodeToDelete->GetParent()->GetData()) { //Validate leaf node is right
		nodeToDelete->GetParent()->SetRight(nullptr);					 //Set to null (for right)
	}

	///Delete Left leaf
	if (nodeToDelete->GetData() < nodeToDelete->GetParent()->GetData()) { //Validate leaf node is left
		nodeToDelete->GetParent()->SetLeft(nullptr);					 //Set to null (for left)
	}

	delete nodeToDelete; //Delete the node
}

 /// DELETE PARENT NODE
/* Delete node with two children */
void BinaryTree::DeleteParent(Node* nodeToDelete) {
	Node* minNode = nodeToDelete->GetRight(); //Go right once

	while (minNode->GetLeft() != nullptr) { //While the smaller Node has a left child node
		minNode = minNode->GetLeft();	   //Go to the next left child node
	}

	int swapValue = minNode->GetData(); //Temporary var used to swap the values

	if (minNode->GetRight() == nullptr) {   //If the min Node has no right child
		DeleteLeaf(minNode);			   //We can safely delete the node
		nodeToDelete->SetData(swapValue); //Swap the value back
		return;							 //and exit the function
	}
	
	DeleteRight(minNode);			   //Otherwise we need to delete its right child
	nodeToDelete->SetData(swapValue); //Swap the values back
}

 /// DELETE RIGHT NODE
/* Delete node with right branch child */
void BinaryTree::DeleteRight(Node* nodeToDelete) {
	if (nodeToDelete->GetData() > nodeToDelete->GetParent()->GetData()) { //If nodeToDeletes data is larger than its paretns data
		nodeToDelete->GetRight()->SetParent(nodeToDelete->GetParent());  //Set the nodeToDeletes right childs PARENT, to be the nodeToDeletes parent
		nodeToDelete->GetParent()->SetRight(nodeToDelete->GetRight());  //Then set the nodeToDeletes parents RIGHT node to the nodeToDeletes right node
	}
	else {
		nodeToDelete->GetRight()->SetParent(nodeToDelete->GetParent());
		nodeToDelete->GetParent()->SetLeft(nodeToDelete->GetRight());
	}

	delete nodeToDelete;
}

 /// DELETE LEFT NODE
/* Delete node with left branch child */
void BinaryTree::DeleteLeft(Node* nodeToDelete) {
	if (nodeToDelete->GetData() > nodeToDelete->GetParent()->GetData()) {
		nodeToDelete->GetLeft()->SetParent(nodeToDelete->GetParent());
		nodeToDelete->GetParent()->SetRight(nodeToDelete->GetLeft());
	}
	else {
		nodeToDelete->GetLeft()->SetParent(nodeToDelete->GetParent());
		nodeToDelete->GetParent()->SetLeft(nodeToDelete->GetLeft());
	}

	delete nodeToDelete;
}

#pragma endregion


Node* BinaryTree::Search(int dataToFind) {
	Node* nodeToFind = mRoot_ptr;

	while (nodeToFind != nullptr) {
		if (nodeToFind == nullptr) { break; }

		if (nodeToFind->GetData() == dataToFind) {
			return nodeToFind;
		}

		if (nodeToFind->GetData() < dataToFind) {
			nodeToFind = nodeToFind->GetRight();
			continue;
		}

		if (nodeToFind->GetData() > dataToFind) {
			nodeToFind = nodeToFind->GetLeft();
		}
	}
	return nullptr;
}

void BinaryTree::Display() {
	if (GetRoot() == nullptr) {
		return;
	}
	else {
		mRoot_ptr->Display(GetScreenWidth() / 2, 40, 400);
	}
}
