#pragma once
#include <string>
#include "raylib.h"

class Node {
	int mData;
	Node* mParent_ptr = nullptr;
	Node* mLeft_ptr = nullptr;
	Node* mRight_ptr = nullptr;

public:
	Node(Node* parent, int data);

	void Insert(int newData);

	Node* GetParent();
	Node* GetRight();
	Node* GetLeft();
	int   GetData();

	void SetParent(Node* parent);
	void SetRight(Node* right);
	void SetLeft(Node* left);
	void SetData(int data);

	void Display(int posX, int posY, int hor);
};