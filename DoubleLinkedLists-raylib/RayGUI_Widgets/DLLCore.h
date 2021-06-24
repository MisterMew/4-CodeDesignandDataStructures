#pragma once
#include <random>
#include <iostream>
using namespace std;

namespace DLL {
	/// Variables
	class LinkedList {
	public:
		struct Node {
			int data;

			Node* prev;
			Node* next;

			Node(int value, Node* nextNode, Node* prevNode) {
				data = value;
				prev = prevNode;
				next = nextNode;
			}
		};

	private:
		Node* mhead_ptr = nullptr;
		Node* mtail_ptr = nullptr;
		int mNodeCount = 0;

		/// Functions
	   /* Declare class functions */
	public:
		Node& operator[](int i) { return *Get(i); }
		Node* Get(int index);

		void InsertHead(int newData);
		void InsertNode(int newData, int pos);
		void InsertTail(int newData);

		void DeleteNode(int nodeToDelete);
		void DeleteHead();
		void DeleteTail();

		void DrawNodes(int selectedNode);

		void SortList();

		int CreateData();
		int CountNodes();

		void DisplayDLList();
	};
}