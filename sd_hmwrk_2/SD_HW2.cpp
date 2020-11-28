#include "pch.h"
#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <sstream>
#include <chrono>

std::string decompress(std::string& input, char* argv[])
{
	std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();

	std::stack<int> numbers;
	std::stack<std::string> arrays;
	std::istringstream incomingStr(input);//break into words
	std::string arrToBeAdded; // store word
	std::ostringstream generatedArr("", std::ios::app | std::ios::out);

	int leftBracketsCounter = 0;//adding counters instead of bool
	int dataChecker = -1;

	char currChar;
	bool leftBracketsFlag = false;
	bool rightBracketsFlag = false;

	//using ignore() to "skip" the current element 

	while (!incomingStr.eof()) {

		int top = incomingStr.peek();

		if (top == '\\') {
			incomingStr.ignore();
			currChar = incomingStr.peek();
			generatedArr << currChar;
			incomingStr.ignore();
		}
		else if(top == '"'){
			incomingStr.ignore();

			while (!incomingStr.eof()) {
				if (incomingStr.peek() == '"') {
					incomingStr.ignore(); 
					break;
				}

				currChar = incomingStr.peek();
				generatedArr << currChar;
				incomingStr.ignore();

			}
		}
		else if (top >= 48 && top <= 57) {
			arrays.push(generatedArr.str());
			generatedArr.str("");
			int numberToBePushed;
			incomingStr >> numberToBePushed;
			numbers.push(numberToBePushed);
			//incomingStr.ignore();
		}
		else if (top == '(') {
			dataChecker++;
			leftBracketsCounter++;
			incomingStr.ignore();
		}
		else if (top == ')') {
			
			incomingStr.ignore();
			leftBracketsCounter--;
			if (leftBracketsCounter <0) {
				std::cout << "Invalid string! Program exiting... \n";
				exit(1);
			}

			arrToBeAdded = generatedArr.str();

			int num = numbers.top();
			numbers.pop();

			for (int i = 1; i < num; i++) {
				generatedArr << arrToBeAdded;
			}

			arrToBeAdded = generatedArr.str();
			generatedArr.str(arrays.top());
			arrays.pop();
			generatedArr << arrToBeAdded;
		}
		else if (top >= 97 && top <= 122 || top >= 65 && top <= 90) {

			incomingStr >> currChar;
			generatedArr << currChar;
		}
		else if (top == -1) {
			break; // stopping the cycle when reaching end of file
		}
		else {
			std::cout << "Invalid string! Program exiting... \n";
			exit(1);
		}
	}

	while (!numbers.empty()) {
		arrToBeAdded = generatedArr.str();
		for (int i = 1; i < numbers.top(); i++) {
			generatedArr << arrToBeAdded;
		}
		numbers.pop();
		arrToBeAdded = generatedArr.str();
		generatedArr.str(arrays.top());
		arrays.pop();
		generatedArr << arrToBeAdded;
	}

	std::ofstream outfile(argv[0], std::ios::trunc);
	//std::string toBeWritten = arrToBeAdded.
	outfile << generatedArr.str(); 

	std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
	std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();

}


int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		std::cout << "Enter the number of arguments:" << argc << std::endl
				  << "arg 1 " << argv[0] << std::endl
				  << "arg 2 " << argv[1] << std::endl
				  << "argv 3 " << argv[2] << std::endl;
	}
	else
	{
		std::cout << "Please enter file name! ";
		exit(1);
	}

	if (argc != 3) {
		std::cout << "Invalid number of arguments, program exiting... \n";
		exit(1);
	}

	std::ifstream infile(argv[1], std::ios::in);
	if (!infile) {
		std::cout << "File cannot be open! Exiting...";
		exit(1); 
	}

	std::string input;
	getline(infile, input);
	infile.close();

	decompress(input, &argv[2]);

	return 0;
}


