
#include "pch.h"
#include <iostream>

template<class T>
struct TreeNode {
	T data;
	TreeNode* successor;
	TreeNode* siblings;

	TreeNode(const T& data, TreeNode* succ = nullptr, TreeNode* sib = nullptr) : 
		data(data), 
		successor(succ), 
		siblings(sib) 
	{}
};

template<class T>
class Tree {
private:
	TreeNode<T>* root;

	TreeNode<T>* copy(const TreeNode<T> other) {

		if (!other) {
			return nullptr;
		}

		TreeNode<T>* tmpNode = new TreeNode<T>(other->data);
		tmpNode->successor = copy(other->successor);
		tmpNode->siblings = copy(other->siblings);

		return tmpNode;
	}

	void del(const TreeNode<T>* node) {

		if (!node) {
			return;
		}
		del(node->successor);
		del(node->siblings);

		delete node;
	}

};

int main()
{


    std::cout << "Hello World!\n"; 
}
