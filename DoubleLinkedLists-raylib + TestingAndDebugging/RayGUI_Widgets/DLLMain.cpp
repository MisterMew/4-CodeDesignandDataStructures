#include "DLLCore.h"

namespace DLL {
	DoubleLinkedList::Node* DoubleLinkedList::Get(int index) {
		Node* currentNode = mhead_ptr;

		if (index > mNodeCount) {
			return mtail_ptr;
		}
		if (index < 0) {
			return mhead_ptr;
		}

		for (int i = 0; i < index; i++) {		   //Loop through until we reach index
			if (currentNode->next != nullptr) {   //If the next node isn't null
				currentNode = currentNode->next; //Go to the next Node
			}
		}

		return currentNode;
	}

#pragma region // Insert Nodes //

	 /// INSERT to FRONT
	/* Insert a node to the front of the list */
	void DoubleLinkedList::InsertHead(int newData) {
		Node* newNode = new Node(newData, nullptr, nullptr); //Allocate memory for a new Node

		 /// Safety Flag
		/* Null Head */
		if (mhead_ptr == nullptr) {    //Check if the head is null
			newNode->prev = nullptr;  //Make newNodes previous node, null
			newNode->next = nullptr; //Make newNodes next node, null
			mhead_ptr = newNode;    //Make the head the new node.
			mtail_ptr = newNode;   //Make the tail the new node too.

			mNodeCount++;		 //Increment NodeCount
			return;			    //Exit Function
		}

		Node* currentNode = mhead_ptr;

		currentNode->prev = newNode;
		newNode->next = currentNode;
		newNode->prev = nullptr;
		mhead_ptr = newNode;
		
		mNodeCount++; //Increment NodeCount
	}

	 /// INSERT to ARBITRARY
	/* Insert a node to an arbitrary point in the list */
	void DoubleLinkedList::InsertNode(int newData, int nodePos) {
		Node* newNode = new Node(newData, nullptr, nullptr);

		 /// Safety Flags
		/* Null Head */
		if (mhead_ptr == nullptr || nodePos <= 0) {
			InsertHead(newData);
			return;
		}

		/* Null Tail */
		if (mtail_ptr == nullptr || nodePos >= mNodeCount) {
			InsertTail(newData);
			return;
		}

		Node* currentNode = Get(nodePos);

		newNode->next = currentNode;
		newNode->prev = currentNode->prev;
		currentNode->prev->next = newNode;
		currentNode->prev = newNode;

		mNodeCount++; //Increment NodeCount
	}

	 /// INSERT to END
	/* Insert a node to the end of the list */
	void DoubleLinkedList::InsertTail(int newData) {
		Node* newNode = new Node(newData, nullptr, nullptr);

		 /// SAFETY FLAGS 
		/* Null Head */
		if (mhead_ptr == nullptr) {   //Check if the head is null
			newNode->prev = nullptr; //Make newNodes previous node, null
			newNode->next = nullptr;//Make newNodes next node, null
			mhead_ptr = newNode;   //Make the head the new node.

			mNodeCount++;		 //Increment NodeCount
			return;				//Exit Function
		}

		/* Null Tail */
		if (mtail_ptr == nullptr) {		    //Check if the tail is null
			newNode->prev = mhead_ptr;	   //Make newNodes previous node, the head
			newNode->next = nullptr;	  //Make newNodes next node, the head
			mtail_ptr = newNode;		 //Make the tail the newNode.
			mhead_ptr->next = mtail_ptr;//Make the head's next node, the tail

			mNodeCount++;		      //Increment NodeCount
			return;					 //Exit Function
		}

		Node* currentNode = mtail_ptr;
		
		currentNode->next = newNode;  //Make currentNodes next node, the newNode
		newNode->prev = currentNode; //Make newNodes previous node, the current Node
		newNode->next = nullptr;    //Make newNodes next node, null
		mtail_ptr = newNode;	   //Make the tail the newNode

		mNodeCount++; //Increment NodeCount
	}

#pragma endregion

#pragma region // Delete Nodes //

	 /// DELETE NODE: Head
	/* Delete the current head node */
	void DoubleLinkedList::DeleteHead() {
		if (mhead_ptr == nullptr) { return; }

		Node* currentNode = mhead_ptr;

		if (currentNode->next == nullptr) { //If there is only one node
			mhead_ptr = nullptr;		   //Set mhead_ptr to nullptr
			mtail_ptr = nullptr;		  //Set mtail_ptr to nullptr
			delete currentNode;		     //Delete the Node

			mNodeCount--;		   	   //Decrement NodeCount
			return;					  //Exit Function
		}

		currentNode->next->prev = nullptr;
		mhead_ptr = currentNode->next;
		delete currentNode;

		mNodeCount--; //Decrement NodeCount
	}

	 /// DELETE NODE: Middle
	/* Delete any body node */
	void DoubleLinkedList::DeleteNode(int nodeToDelete) {
		if (mhead_ptr == nullptr) { return;	}

		// Selected Node is the head
		if (nodeToDelete <= 0) {
			DeleteHead();
			return;
		}

		// Selected Node is the tail
		if (nodeToDelete >= mNodeCount - 1) {
			DeleteTail();
			return;
		}

		Node* currentNode = Get(nodeToDelete);

		currentNode->prev->next = currentNode->next;  //Set the current nodes previous nodes, next node | to the current nodes next node
		currentNode->next->prev = currentNode->prev; //Set the current nodes next nodes, previous node | to the current nodes previous node
		delete currentNode;							//Delete the current node

		mNodeCount--; //Decrement NodeCount
	}

	 /// DELETE NODE: Tail
	/* Delete the current tail node */
	void DoubleLinkedList::DeleteTail() {
		if (mtail_ptr == nullptr) { return; }

		Node* currentNode = mtail_ptr;

		if (currentNode->prev == nullptr) { //If there is only one node
			mhead_ptr = nullptr;		   //Set mhead_ptr to nullptr
			mtail_ptr = nullptr;		  //Set mtail_ptr to nullptr
			delete currentNode;			 //Delete the Node

			mNodeCount--;			   //Decrement NodeCount
			return;					  //Exit Function
		}

		currentNode->prev->next = nullptr;
		mtail_ptr = currentNode->prev;
		delete currentNode;

		mNodeCount--; //Decrement NodeCount
	}

#pragma endregion

#pragma region [ Sorting Algorithm ]
	 /// SORTING
	/*  sort the Linked List */
	void DoubleLinkedList::SortList() {
		if (mhead_ptr == nullptr) { return; }

		Node* currentNode = nullptr;
		Node* index = nullptr;
		int temp;

		for (currentNode = mhead_ptr; currentNode->next != nullptr; currentNode = currentNode->next) {
			for (index = currentNode->next; index != nullptr; index = index->next) {
				if (currentNode->data > index->data) {
					temp = currentNode->data;
					currentNode->data = index->data;
					index->data = temp;
				}
			}
		}
	}

#pragma endregion


	 /// CREATE NODE DATA
	/* Generates a random data value */
	int DoubleLinkedList::CreateData() {
		int newData;

		random_device rdm;                              //Obtains a random num from hardware  ||
		mt19937 genData(rdm());                        //Seed the generator                   || mt19937 is a pseudo-random generator of 32-bit numbers with a state size of 19937 bits.
		uniform_int_distribution<> dataRange(0, 999); //Defines the range to generate between ||

		newData = dataRange(genData);

		return newData;
	}

	 /// DISPLAY DL-LIST
	/* Iterates each node to display the list */
	void DoubleLinkedList::DisplayDLList() {
		Node* current = mhead_ptr;

		if (current == nullptr) {
			cout << " [NULL ERROR] " << endl;
			return;
		}

		while (current != nullptr) {
			current = current->next;
		}
	}
}