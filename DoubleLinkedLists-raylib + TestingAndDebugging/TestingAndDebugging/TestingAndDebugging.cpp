#include "pch.h"
#include "CppUnitTest.h"

#include "../RayGUI_Widgets/DLLCore.h"

using namespace DLL;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingAndDebugging {
	TEST_CLASS(TestingAndDebugging) {
	public:
		
		 /// TESTING INSERTION
		/* Testing DLL Insert to Head */
		TEST_METHOD(TestInsertHead) {
			DoubleLinkedList testList;

			for (int i = 0; i < 10; i++) {
				testList.InsertHead(i * 10);
			}

			Assert::AreEqual((9 * 10), testList.HeadData());
			Assert::AreEqual((0 * 10), testList.TailData());
		}

		/* Testing DLL Insert to Tail */
		TEST_METHOD(TestInsertTail) {
			DoubleLinkedList testList;

			for (int i = 0; i < 10; i++) {
				testList.InsertTail(i * 10);
			}

			Assert::AreEqual((0 * 10), testList.HeadData());
			Assert::AreEqual((9 * 10), testList.TailData());
		}

		/// TESTING DELETION
	   /* Testing DLL Delete from Head */
		TEST_METHOD(TestDeleteHead) {
			DoubleLinkedList testList;

			for (int i = 0; i < 10; i++) {
				testList.InsertHead(i * 10);
			}

			testList.DeleteHead();

			Assert::AreEqual((8 * 10), testList.HeadData());
		}

		/* Testing DLL Delete from Tail */
		TEST_METHOD(TestDeleteTail) {
			DoubleLinkedList testList;

			for (int i = 0; i < 10; i++) {
				testList.InsertHead(i * 10);
			}

			testList.DeleteTail();

			Assert::AreEqual((1 * 10), testList.TailData());
		}

		 /// TEST COUNT NODES
		/* Test the CountNodes function */
		TEST_METHOD(TestCountNodes) {
			DoubleLinkedList testList;

			for (int i = 0; i < 10; i++) {
				testList.InsertHead(testList.CreateData());
			}

			testList.DeleteHead();
			testList.DeleteTail();

			Assert::AreEqual((10 - 2), testList.CountNodes());
		}

	};
}
