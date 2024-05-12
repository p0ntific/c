#include <iostream>
#include <algorithm>
#include <stdexcept>
using namespace std;



template <class T>
class AVLNode {
public:
	AVLNode<T>* parent, * left, * right;
	int key, height;
	T data;

	AVLNode(int k, T d, AVLNode<T>* l = nullptr, AVLNode<T>* r = nullptr) :parent(nullptr), left(l), right(r), key(k), data(d) {
		if (left != nullptr) left->parent = this;
		if (right != nullptr) right->parent = this;
		height = correct_h();
	}

	void print() {
		cout << key  << endl;
	}
	AVLNode<T>* clone() {
		if (left == nullptr && right == nullptr) return new AVLNode<T>(key, data);
		return new AVLNode<T>(
			key,
			data,
			left != nullptr ? left->clone() : nullptr,
			right != nullptr ? right->clone() : nullptr
			);
	}
	int defect_h() {
		return _defect_h(this);
	}
	int correct_h() {
		return _correct_h(this);
	}

private:
	int _defect_h(AVLNode<T>* p) {
		if (p == nullptr) return 0;
		return _correct_h(p->left) - _correct_h(p->right);
	}
	int _correct_h(AVLNode<T>* p) {
		if (p == nullptr) return 0;
		return 1 + max(_correct_h(p->left), _correct_h(p->right));
	}
};

template <class T>
void f_print(AVLNode<T>* r, int indent = 0) {
	if (r == nullptr) return;
	f_print(r->right, indent + 3);
	for (int i = 0; i < indent; ++i)
		cout << ' ';
	r->print();
	f_print(r->left, indent + 3);
}


template <class T>
class AVLTree {
private:
	AVLNode<T>* root;


public:
	AVLTree() : root(nullptr) {}

	AVLTree(AVLNode<T>* p) : root(p) {}

	~AVLTree() {
		this->destroy(root);
	}

	void destroy(AVLNode<T>*& p) {
		if (p == nullptr) // дерево пусто
			return;
		
		if (p->left != nullptr) {
			destroy(p->left);
			p->left = nullptr;
		}
		if (p->right != nullptr) {
			destroy(p->right);
			p->right = nullptr;
		}
		p = nullptr;
	}

	AVLTree(const AVLTree<T>& x): root(x.root){}

	AVLTree<T>& operator=(AVLTree<T>&& x)
	{
		AVLTree<T> tmp(move(x));
		swap(*this, tmp);
		return *this;
	}

	void RotateLeft(AVLNode<T>*& p);
	void RotateRight(AVLNode<T>*& p);	
	
	void correctm2(AVLNode<T>*& p);
	void correct2(AVLNode<T>*& p);

	void rebalance(AVLNode<T>*& p);

	void insert(int key, T data);

	AVLNode<T>* find(int key);

	AVLNode<T>* find_next(AVLNode<T>* p);

	void del(int key);

	bool test();
	bool test(AVLNode<T>* p);

	void print() { f_print(root); };
};

template <class T>
void AVLTree<T>::RotateRight(AVLNode<T>*& p)
{
	AVLNode<T>* prev_p = p;
	AVLNode<T>* leftTree = p->left;
	AVLNode<T>*& parent = p->parent;
	AVLNode<T>*& oldRight = leftTree->right;
	if (leftTree == nullptr) return;
	prev_p->left = oldRight;
	leftTree->right = prev_p; 
	leftTree->parent = parent;
	if (parent == nullptr) {
		root = leftTree;
		root->parent = nullptr;
		prev_p->parent = root;
		root->right = prev_p;
		return;
	}
	if ( parent->left == p) {
		parent->left = leftTree; 
	}
	else { 
		parent->right = leftTree; 
	}
	leftTree->right->parent = leftTree;
}

template <class T>
void AVLTree<T>::RotateLeft(AVLNode<T>*& p)
{
	AVLNode<T>* prev_p = p;
	AVLNode<T>* rightTree = p->right;
	AVLNode<T>*& parent = p->parent;
	AVLNode<T>*& oldLeft = rightTree->left;
	if (rightTree == nullptr) return;
	prev_p->right = oldLeft;
	if (oldLeft != nullptr) oldLeft->parent = prev_p;
	rightTree->left = prev_p;
	rightTree->parent = parent;
	if (parent == nullptr) {
		root = rightTree;
		root->parent = nullptr;
		prev_p->parent = root;
		root->left = prev_p;
		return;
	}
	if (parent->right == p) {
		parent->right = rightTree;
	}
	else {
		parent->left = rightTree;
	}
	rightTree->left->parent = rightTree;
}

template <class T>
void AVLTree<T>::correctm2(AVLNode<T>*& p) {
	if (p == nullptr) return;
	AVLNode<T>* pr = p->right;
	if (pr != nullptr && pr->defect_h()>0) RotateRight(pr);
	RotateLeft(p);
}

template <class T>
void AVLTree<T>::correct2(AVLNode<T>*& p) {
	if (p == nullptr) return;
	AVLNode<T>* pl = p->left;
	if (pl != nullptr && pl->defect_h() > 0) RotateLeft(pl);
	RotateRight(p);
}

template <class T>
void AVLTree<T>::rebalance(AVLNode<T>*& p) {
	AVLNode<T>* parent = p->parent;
	int defect = p->defect_h();
	
	if (defect == 2) correct2(p);
	else if (defect == -2) correctm2(p);
	if (parent != nullptr) {
		
		rebalance(parent);
	}
}

template <class T>
void AVLTree<T>::insert(int key, T data) {
	AVLNode<T>* p = root;
	while (p != nullptr) {
		if (p->key == key) return;
		else if (p->key < key) {
			if (p->right == nullptr) break;
			p = p->right;
		}
		else {
			if (p->left == nullptr) break;
			p = p->left;
		}
	}
	if (p == nullptr) throw exception("something went wrong!");
	AVLNode<T> * new_p = new AVLNode<T>(key, data);
	if (p->key < key) {
		p->right = new_p;
	}
	else{
		p->left = new_p;
	}
	new_p->parent = p;
	AVLNode<T>* parent = p->parent;
	if (parent != nullptr) { 
		rebalance(parent); 
	}
}


template <class T>
AVLNode<T>* AVLTree<T>::find(int key) {
	AVLNode<T> * p = root;
	while (p != nullptr) {
		if (p->key == key) return p;
		else if (p->key < key) p = p->right;
		else p = p->left;
	}
	return p;
}

template <class T>
AVLNode<T>* AVLTree<T>::find_next(AVLNode<T>*p) {
	while (p->left != nullptr) {
		p = p->left;
	}
	return p;
}

template <class T>
void AVLTree<T>::del(int key) {
	AVLNode<T> * p = find(key);
	AVLNode<T> * parent = p->parent;
	if (parent == nullptr) {
		destroy(root);
		return;
	}
	//нет детей
	if (parent->left == p && p->left == nullptr && p->right == nullptr) {
		p->left = nullptr;
		parent->left = nullptr;
	}
	else if (parent->right == p && p->left == nullptr && p->right == nullptr) {
		p->left = nullptr;
		parent->right = nullptr;
	}

	//есть левый сын
	else if (parent->left == p && p->left != nullptr && p->right == nullptr) {
		parent->left = p->left;
		p->left->parent = parent;
	}
	else if (parent->right == p && p->left != nullptr && p->right == nullptr) {
		parent->right = p->left;
		p->left->parent = parent;
	}

	//есть правый сын
	else if (parent->left == p && p->left == nullptr && p->right != nullptr) {
		parent->left = p->right;
		p->right->parent = parent;
	}
	else if (parent->right == p && p->left == nullptr && p->right != nullptr) {
		parent->right = p->right;
		p->right->parent = parent;
	}

	//есть оба сына
	else if (p->left != nullptr && p->right != nullptr) {
		AVLNode<T>* next = find_next(p->right);
		del(next->key);
		p->key = next->key;
		p->data = next->data;
		
	}
	rebalance(parent);
	p = nullptr;
}


template <class T>
bool AVLTree<T>::test() {
	return test(root);
}

template <class T>
bool AVLTree<T>::test(AVLNode<T> *p) {
	if (p == nullptr) return true;
	return (abs(p->defect_h()) <=1)*test(p->left)*test(p->right);
}

int main()
{
	AVLNode<int>
	* p1 = new AVLNode<int>(1, 10);
	
	AVLTree<int> t(p1);
	t.insert(1231,1);
	t.insert(55,1);
	t.insert(123,1);
	t.insert(12,1);
	t.insert(5253,1);
	t.insert(11,1);
	t.insert(58,1);
	t.print();
	cout << "================" << endl;
	t.insert(60,1);
	t.print();
	cout << t.test() << endl;
	return EXIT_SUCCESS;
}
