#include "pch.h"
#include <iostream>

class Node {
private:
	Node* left = nullptr;
	Node *right = nullptr;
	int data;

public:
	Node() {
		data = 0;
	}

	Node(int data) {
		this->data = data;
	}

	void insert(int val) {
		if (val <= data) {
			if (left == nullptr) {
				left = new Node(val);

			}
			else {
				left->insert(val);
			}
		}
		else {
			if (right == nullptr) {
				right = new Node(val);
			}
			else {
				right->insert(val);
			}
		}
	}

	bool contains(int value) const {
		if (value == data) {
			return true;
		}
		else if (value <= data) {
			if (left == nullptr) {
				return false;
			}
			return left->contains(value);
		}
		else {
			if (right == nullptr) {
				return false;
			}
			return right->contains(value);
		}
	}

	//traversing in order
	void printInOrder() const {
		if (left != nullptr) {
			left->printInOrder();
		}
		std::cout << data<<" ";
		if (right != nullptr) {
			right->printInOrder();
		}
	}


	//like wtf is going on in here shit no work must fix

	void printBackwards() const {

		if (right != nullptr) {
			right->printBackwards();
		}
		
		std::cout << data << " ";

		if (left != nullptr) {
			left->printBackwards();
		}
		
	}

};




int main()
{
	//custom unit tests
	Node a;
	a.insert(5);
	a.insert(8);
	a.insert(25);
	a.insert(4);
	a.insert(28);
	a.printInOrder();
	std::cout << std::endl;
	a.printBackwards();
}
