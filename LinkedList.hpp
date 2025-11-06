#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {

	T data;
	Node* prev;
	Node* next;

	explicit Node(T data) : data(data), prev(nullptr), next(nullptr) {}

};


template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {

		if (head == nullptr) {
			return;
		}

		Node<T>* currNode = head;

		while (currNode->next != nullptr) {
			std::cout << currNode->data << " ";
			currNode = currNode->next;
		}

		std::cout << currNode->data << "\n";
	}

	void printReverse() const {

		if (tail == nullptr) {
			return;
		}
		Node<T>* currNode = tail;

		while (currNode->prev != nullptr) {
			std::cout << currNode->data << " ";
			currNode = currNode->prev;
		}

		std::cout << currNode->data << "\n";

	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const { return count; }
	Node<T>* getHead() { return head; }
	const Node<T>* getHead() const { return head; }
	Node<T>* getTail() { return tail; }
	const Node<T>* getTail() const { return tail; }

	// Insertion
	void addHead(const T& data) {

		count++;

		if (head == nullptr) {
			head = new Node(data);
			tail = head;
			return;
		}

		Node<T>* newHeadPtr = new Node(data);
		head->prev = newHeadPtr;
		newHeadPtr->next = head;
		head = newHeadPtr;

	}
	void addTail(const T& data) {

		if (head == nullptr) {
			addHead(data);
			return;
		}

		count++;

		Node<T>* newTailPtr = new Node(data);
		tail->next = newTailPtr;
		newTailPtr->prev = tail;
		tail = newTailPtr;

	}


	// Removal
	bool RemoveHead() {

		if (head == nullptr) {
			return false;
		}

		if (head->next == nullptr) {
			delete head;
			head = nullptr;
			count--;
			return true;
		}

		Node<T>* nextHead = head->next;
		nextHead->prev = nullptr;
		delete head;
		head = nextHead;
		count--;

		return true;
	}
	bool removeTail() {

		if (tail == nullptr || head == nullptr) {
			return false;
		}

		if (tail->prev == nullptr) {
			delete tail;
			tail = nullptr;
			head = nullptr;
			count--;
			return true;
		}

		Node<T>* nextTail = tail->prev;
		nextTail->next = nullptr;
		delete tail;
		tail = nextTail;
		count--;
		return true;
	}
	void clear() {

		if (head == nullptr) {
			return;
		}

		// Node<T>* currNode = head;
		//
		// while (currNode->next) {
		// 	if (currNode->prev) {
		// 		delete currNode->prev;
		// 	}
		// 	currNode = currNode->next;
		// }
		//
		// delete currNode;
		//
		// tail = nullptr;
		// head = nullptr;
		// count = 0;
		Node<T>* currNode = head;

		while (currNode) {
			Node<T>* temp = currNode->next;
			delete currNode;
			currNode = temp;
		}

		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {

		if (&other == this) {
			return *this;
		}
		clear();
		head = other.getHead();
		tail = other.getTail();
		count = other.getCount();
		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {

		if (&rhs == this) {
			return *this;
		}

		clear();

		const Node<T>* currNode = rhs.getHead();

		for (unsigned int i = 0; i < rhs.getCount(); i++) {
			addTail(currNode->data);
		}

		return *this;
	}

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}
	LinkedList(const LinkedList<T>& list) {

		const Node<T>* currNode = list.getHead();
		count = list.getCount();

		for (unsigned int i = 0; i < list.getCount(); i++) {
			addTail(currNode->data);
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept {
		head = other.getHead();
		tail = other.getTail();
		count = other.getCount();
	}
	~LinkedList() {
		clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;

};


