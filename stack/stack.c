#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class StackList {
private:
	unsigned int stackSize;
	int *array;

public:
	StackList(const int max) {
		stackSize = 0;
		array = new int[max];
	}

	~StackList() {
		delete[] array;
	}

	void push(const int newElement) {
		array[stackSize] = newElement;
		stackSize++;
	
	}

	int pop() {
		stackSize--;
		return array[stackSize];
	}

	unsigned int size() {
		return stackSize;
	}
};

struct Node {
	int value;
	Node *next;

	Node(int newValue, Node *nextNode) {
		value = newValue;
		next = nextNode;
	}
};

class StackNode {
private:
	unsigned int stackSize;
	Node *top;

public:
	StackNode() {
		stackSize = 0;
		top = NULL;
	}

	~StackNode() {
		while (size())
			pop();
	}

	void push(const int element) {
		Node *node = new Node(element, top);
		stackSize++;
		top = node;
	}

	int pop() {
		stackSize--;
		Node *node = top;
		int result = top->value;
		top = top->next;
		delete node;
		return result;
	}

	unsigned int size() {
		return stackSize;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	StackNode stack;
	stack.push(1);
	stack.push(51);
	stack.push(15);
	stack.push(2);
	stack.push(4);
	int a;
	int len = stack.size();
	for (int i = 0; i < len; i++)
	{
		a = stack.pop();
		cout << a << endl;
	}
	system("pause");
	return 0;
}

