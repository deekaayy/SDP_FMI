#include "pch.h"
#include <iostream>
#include <stack>
#include <string>

std::stack<int> stek;
int stek_stor[20]; //to store;

void insert_at_bottom(int kurec) {
	if (stek.size() == 0) {
		stek.push(kurec);
	}
	else {
		int a = stek.top();
		stek.pop();
		insert_at_bottom(kurec);
		stek.push(kurec);
	}
}

void reverse() {
	if (stek.size() > 0) {
		int x = stek.top();
		stek.pop();
		reverse();
		insert_at_bottom(x);
	}
}

void sortedInsert(std::stack<int>& stack, int key)
{
	if (stack.empty() || key > stack.top())
	{
		stack.push(key);
		return;
	}
	int top = stack.top();
	stack.pop();
	sortedInsert(stack, key);
	stack.push(top);
}

void sortstack(std::stack<int>& stack)
{
	if (stack.empty()) {
		return;
	}

	int top = stack.top();
	stack.pop();
	sortstack(stack);
	sortedInsert(stack, top);
}

int main()
{
	
	stek.push(1);
	stek.push(2);
	stek.push(3);
	stek.push(4);
	stek.push(5);
	stek.push(6);
	reverse();
	int a = 0;
	while (!stek.empty()) {
		int p = stek.top();
		stek.pop();
		stek_stor[a] = p;
	}
	for (auto x : stek_stor) {
		std::cout << x;
	}

}
