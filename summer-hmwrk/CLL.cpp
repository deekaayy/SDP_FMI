#include "pch.h"
#include "CLL.h"

Node::Node(std::string data): data(data), next(nullptr) {}

void Node::getNextAndConcat()
{
	data.append("-");
	data.append(next->data);
}

void CircularLinkedList::copy(const CircularLinkedList& other)
{
	firstElement = nullptr;
	Node* temp = other.firstElement;
	for (size_t i = 0; i < other.size; i++) {
		addAtEnd(temp->data);
		temp = temp->next;
	}
}

void CircularLinkedList::del()
{
	while (size != 0) {
		removeFirst();
	}
}

CircularLinkedList::CircularLinkedList() : firstElement(nullptr), lastElement(nullptr), size(0) {}

CircularLinkedList::CircularLinkedList(const CircularLinkedList & other)
{
	copy(other);
}

CircularLinkedList & CircularLinkedList::operator=(const CircularLinkedList & other)
{
	if (this != &other) {
		del();
		copy(other);
	}

	return *this;
}

CircularLinkedList::~CircularLinkedList()
{
	del();
}

void CircularLinkedList::addAtEnd(std::string newData)
{
	Node* temp = new Node(newData);
	if (isEmpty()) {
		firstElement = temp;
		lastElement = temp;
	}
	else {
		lastElement->next = temp;
		lastElement = temp;
		lastElement->next = firstElement;
	}
	size++;
}

void CircularLinkedList::addAtBeginning(std::string newData)
{
	Node* temp = new Node(newData);

	if (isEmpty()) {
		firstElement = temp;
		lastElement = temp;
	}
	else {
		temp->next = firstElement;
		firstElement = temp;
		lastElement->next = firstElement;
	}

	size++;
}

bool CircularLinkedList::removeFirst()
{
	if (isEmpty()) {
		return 0;
	}
	else if (size == 1) {
		delete firstElement;
		size--;
		return 1;
	}
	else {
		Node* temp = firstElement->next;
		delete firstElement;
		firstElement = temp;
		lastElement->next = firstElement;
		size--;
		return 1;
	}
}

void CircularLinkedList::removeLast()
{
	Node* temp = lastElement->next;
	while (temp->next != lastElement)
	{
		temp = temp->next;
	}

	temp->next = lastElement->next;
	delete lastElement;
	lastElement = temp;

	size--;
}

void CircularLinkedList::pop(Node * node)
{

	if (isEmpty()) {
		return;
	}

	Node* temp = firstElement;

	if (node == firstElement){
		removeFirst(); //size--
		return;
	}

	for (int i = 0; i < size; i++) {
		if (temp->next == lastElement && node == lastElement) {

			removeLast(); //size--

		}
		else if (temp->next == node){

			Node* toDel = temp->next;
			temp->next = toDel->next;
			size--;
		}
		temp = temp->next;
	}
}

void CircularLinkedList::print() //function should've been const but assert throwing errors
{
	assert(!isEmpty() && "Cannot print an empty list!\n");
	Node* temp = firstElement;
	std::cout<< " -> ";
	for (size_t i = 0; i < size; i++)
	{
		std::cout << temp->data << " -> ";
		temp = temp->next;
	}
	std::cout << std::endl;
}

void CircularLinkedList::concatAndDelNextNode(Node * current)
{
	Node* tempNode = current;
	current->getNextAndConcat();
	pop(current->next);
}

void CircularLinkedList::concatenateAllAvaiable()
{
	if (isEmpty()) {
		return;
	}
	else {
		Node* iterator = firstElement;
		int i = 0;
		while (  i<size+1 ) {
			char currChar = iterator->data.back();//getting the last char of the data
			char nextChar = iterator->next->data.front();//getting the first char of the data
			if (toupper(currChar) == toupper(nextChar) && iterator->next != iterator) { //securing if the list has only 1 element
				concatAndDelNextNode(iterator);
				//i++;
				continue; // if deleted, no need to jump to the next element 
			}
			i++;
			iterator = iterator->next;
		}
	}
}

void CircularLinkedList::sort()
{
															//current will point to the first element  
	Node* current = firstElement;
	Node* index = nullptr;
	std::string temp;

	if (isEmpty()) {
		std::cout << "List is empty!" << std::endl;
		return;
	}
	else {
		do {
															
			index = current->next; //Index will point to the next node after the current one
				while (index != firstElement) {
															//if current node data is greater than index data, swap
					if (current->data.length() > index->data.length()) {
						temp = current->data;
						current->data = index->data;
						index->data = temp;
					}

				index = index->next; //jump onto the next with the updated value
				}

			current = current->next;

		} while (current->next != firstElement);
	}
}

std::string CircularLinkedList::findLongest()
{
	Node* longest = firstElement;

	for (size_t i = 0; i < size; i++)
	{
		if (longest->data.length() <= longest->next->data.length()) {
			longest = longest->next;
		}
	}

	return longest->data;
}
