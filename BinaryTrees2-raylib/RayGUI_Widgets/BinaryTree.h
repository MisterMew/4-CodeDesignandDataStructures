#pragma once
#include "Node.h"

class BinaryTree {
	Node* mRoot_ptr = nullptr;

	void DeleteLeaf(Node* nodeToDelete);
	void DeleteParent(Node* nodeToDelete);
	void DeleteRight(Node* nodeToDelete);
	void DeleteLeft(Node* nodeToDelete);

public:
	void Insert(int value);
	void Delete(int key);

	Node* GetRoot();

	Node* Search(int dataToFind);

	void Display();
};