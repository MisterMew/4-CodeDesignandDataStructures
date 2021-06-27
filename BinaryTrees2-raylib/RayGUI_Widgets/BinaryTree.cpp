#include "BinaryTree.h"

void BinaryTree::Insert(int value) {
	if (mRoot_ptr == nullptr) { 
		mRoot_ptr = new Node(nullptr, value);
	}
	else {
		mRoot_ptr->Insert(value);
	}
}

#pragma region [ Node Deletion Functions ]

void BinaryTree::Delete(int key) {
	Node* nodeToDelete = Search(key);

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
	if (nodeToDelete->GetLeft() == nullptr) {
		DeleteRight(nodeToDelete);
		return;
	}

	/// Delete Left node
	if (nodeToDelete->GetRight() == nullptr) {
		DeleteLeft(nodeToDelete);
	    return;
	}
}

Node* BinaryTree::GetRoot() {
	return mRoot_ptr;
}

 /// DELETE LEAF NODE
/* Delete Leaf node from tree */
void BinaryTree::DeleteLeaf(Node* nodeToDelete) {
	//Right
	if (nodeToDelete->GetData() > nodeToDelete->GetParent()->GetData()) {
		nodeToDelete->GetParent()->SetRight(nullptr);
	}

	//Left
	if (nodeToDelete->GetData() < nodeToDelete->GetParent()->GetData()) {
		nodeToDelete->GetParent()->SetLeft(nullptr);
	}

	delete nodeToDelete;
}

 /// DELETE PARENT NODE
/* Delete node with two children */
void BinaryTree::DeleteParent(Node* nodeToDelete) {
	Node* minNode = nodeToDelete->GetRight(); //Go right once

	//Get the smallest number that is larger than the node we want to delete
	//Loop through all left-side nodes
	while (minNode->GetLeft() != nullptr) { //Keep going left to get the smallest node than the nodeToDelete
		minNode = minNode->GetLeft();
	}

	nodeToDelete->SetData(minNode->GetData()); // Copy data into the 

	if (minNode->GetRight() == nullptr) {
		DeleteLeaf(minNode);
		return;
	}

	DeleteRight(nodeToDelete);
}

 /// DELETE RIGHT NODE
/* Delete node with right branch child */
void BinaryTree::DeleteRight(Node* nodeToDelete) {
	if (nodeToDelete->GetData() > nodeToDelete->GetParent()->GetData()) {
		nodeToDelete->GetRight()->SetParent(nodeToDelete->GetParent());
		nodeToDelete->GetParent()->SetRight(nodeToDelete->GetRight());
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
	mRoot_ptr->Display(GetScreenWidth() / 2, 40, 400);
}
