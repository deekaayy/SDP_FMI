#include "pch.h"
#include "CLL.h"

void doTests() {

	std::cout << "Running test data... \n\n";

	CircularLinkedList ll;

	ll.addAtEnd("Street");
	ll.addAtEnd("Taxi");
	ll.addAtEnd("Ink");
	ll.addAtEnd("Kongo");
	ll.addAtEnd("Dog");
	ll.addAtEnd("Smile");
	ll.addAtEnd("Eat");
	ll.addAtEnd("Tall");
	ll.addAtEnd("Ker");
	ll.addAtEnd("Rer");
	ll.addAtEnd("Pass");
	ll.addAtEnd("Sap");
	///////////////////////////
	ll.print();
	ll.concatenateAllAvaiable();
	ll.print();

	///////////////////////////
	ll.sort();
	std::cout << "\nPost-sort...\n";
	ll.print();

	//////////////////////////////////
	std::cout << "The biggest element is...\n"
			  << ll.findLongest() << "\n\n";
}

void mainFunc() {
	std::cout << "Enter as many elements as you wish, if you want to stop, type \"exit\"...\n";

	CircularLinkedList ll;
	std::string command;
	while (true)
	{
		std::cin >> command;
		if (command == "exit")
		{
			break;
		}
		ll.addAtEnd(command);
	}

	ll.print();
	ll.concatenateAllAvaiable();
	std::cout << "\nAfter the concatenation...\n";
	ll.print();

	ll.sort();
	std::cout << "\nPost-sort...\n";
	ll.print();

	std::cout << "The biggest element is...\n"
			  << ll.findLongest() << "\n\n";
}

int main()
{
	//doTests();

	mainFunc();

	return 0;
}
