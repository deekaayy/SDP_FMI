#pragma once
#include "pch.h"
#include<string>
#include<cassert>
#include<iostream>

struct Node
{
	std::string data;
	Node* next;

	Node(std::string data);

	void getNextAndConcat();
};


class CircularLinkedList {
private:
	Node* firstElement;
	Node* lastElement;

	size_t size;

	void copy(const CircularLinkedList& other);
	void del();
	bool isEmpty() { return size == 0; }

public:
	CircularLinkedList();
	CircularLinkedList(const CircularLinkedList& other);
	CircularLinkedList& operator=(const CircularLinkedList& other);
	~CircularLinkedList();

	void addAtEnd(std::string newData);
	void addAtBeginning(std::string newData);
	bool removeFirst();

	//getters

	Node* getFirst() const { return firstElement; }
	std::string getFirstData() const { return firstElement->data; }
	Node* getLast() const { return lastElement; }
	std::string getLastData() const { return lastElement->data; }

	void removeLast();

	void pop(Node* node); //remove a node and reroute the remaining nodes

	void print();

	void concatAndDelNextNode(Node* current); //concatenates the current node with the next one and removes the next node, rerouting in the process
											  //used as a helper funcion in @concatenateAllAvaiable();

	void concatenateAllAvaiable(); //concatenates all nodes which satisfy the conditions

	void sort(); //sorts the list in ascending order

	std::string findLongest();

};
