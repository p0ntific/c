#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#define SIZE 1000
using namespace std;

class Queue
{
	int *arr;
	int max_size;
	int front;
	int back;
	int cur_size;

public:
	Queue(int size = SIZE){
		arr = new int[size];
		max_size = size;
		front = 0;
		back = -1;
		cur_size = 0;
	}
	~Queue() {
		delete[] arr;
	};

	int pop(){
		if (cur_size == 0) return -1;
		int x = arr[front];
		front += 1;
		cur_size -= 1;
		return x;
	};
	void push(int x){
		if (cur_size == max_size) cout << "no space" << endl;
		back += 1;
		arr[back] = x;
		cur_size += 1;
	};
	int size(){
		return cur_size;
	};
};



int main()
{
	// create a queue of capacity 5
	Queue q(5);
	
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	cout << q.pop() << endl;
	cout << q.pop() << endl;
	cout << q.pop() << endl;
	cout << q.pop() << endl;
	system("pause");
	return 0;
}

