#include <iostream>
#include <stdexcept>
using namespace std;

template <class T1, class T2>
struct SNode
{
	T1 key; //ключ
	T2 data;// элемент данных
	SNode* left, *right; // указатели на сыновей
	SNode(T1 k,  SNode* l = nullptr, SNode* r = nullptr, T2 d = 0 ) :
		data(d), left(l), right(r), key(k) {} // конструктор
};

template <class T1 = int, class T2 = int>
void f_print(SNode<T1,T2>* r, int indent = 0)
{
	if (r == nullptr) return;
	f_print(r->right, indent + 3);
	for (int i = 0; i < indent; ++i)
		cout <<' ';
	cout << r->key << endl;
	f_print(r->left, indent + 3);
}

template <class T1 = int, class T2 = int>
void f_add(SNode<T1,T2>*& p, T1 key, T2 data)
{
	if (p == nullptr) {
		p = new SNode<T1, T2>(key, nullptr, nullptr, data);
	}
	else {
		SNode<T1, T2> * node = p;
		if (key < node->key) {
			f_add(node->left, key, data);
		}
		else if (key > node->key) {
			f_add(node->right, key, data);
		}
		else {
			throw invalid_argument("node with this key already exists!");
		}
	}
}

template <class T1 = int, class T2 = int>
SNode<T1,T2>* f_find(SNode<T1,T2>* p, T1 key)
{
	if (p == nullptr) return p;
	else {
		if (p->key == key) return p;
		else if (p->key > key) f_find(p->left, key);
		else f_find(p->right,key);
	}
}

template <class T1 = int, class T2 = int>
class STree {
public:
	STree()
		: root(nullptr)
	{
	}
	STree(SNode<T1,T2> * p) : root(p) {}
	~STree() {
		DestroyNode(root);
	}
	SNode<T1, T2> * findR(T1 key);
	SNode<T1, T2> * findC(T1 key);	
	SNode<T1, T2> * findParent(T1 key);	

	SNode<T1, T2> * find_left_node(SNode<T1, T2> * node);

	void addR(T1 key, T2 data);
	void addC(T1 key, T2 data);

	void del_node(T1 key);

	void print(int indent = 0) { f_print(root,indent); };

private:
	static void DestroyNode(SNode<T1,T2>* node) {
		if (node) {
			DestroyNode(node->left);
			DestroyNode(node->right);
			delete node;
		}
	}

private:
	SNode<T1,T2>* root;
};


template<class T1, class T2>
SNode<T1,T2> * STree<T1, T2>::findC(T1 key)
{
	SNode<T1,T2> * p = root;
	while (p != nullptr) {
		if (p->key == key) break;
		else if (p->key > key) p = p->left;
		else p = p->right;
	}
	return p;
}

template<class T1, class T2>
SNode<T1,T2> * STree<T1, T2>::findParent(T1 key)
{
	SNode<T1,T2> * p = root;
	while (p != nullptr) {
		if (p->left != nullptr && p->left->key == key) break;
		if (p->right != nullptr && p->right->key == key) break;
		else if (p->key > key) p = p->left;
		else p = p->right;
	}
	return p;
}

template<class T1, class T2>
SNode<T1, T2> * STree<T1, T2>::findR(T1 key)
{
	return f_find(root, key);
}

template<class T1, class T2>
void STree<T1, T2>::addC(T1 key, T2 data)
{
	SNode<T1,T2>** p = &root;
	while (*p != nullptr) {
		SNode<T1,T2> * node = *p;
		if (key < node->key) {
			p = &node->left;
		}
		else if (key > node->key) {
			p = &node->right;
		}
		else {
			throw invalid_argument("node with this key already exists!");
		}
	}
	*p = new SNode<T1, T2>(key, nullptr,nullptr, data);
}

template<class T1, class T2>
void STree<T1, T2>::addR(T1 key, T2 data)
{
	return f_add(root, key, data);
}


template<class T1, class T2>
SNode<T1, T2> * STree<T1, T2>::find_left_node(SNode<T1, T2> * node)
{
	SNode<T1, T2> * p = node;
	while (p->left != nullptr) 
		p = p->left;
	return p;
}


template<class T1, class T2>
void STree<T1, T2>::del_node(T1 key)
{
	SNode<T1, T2> * parent = findParent(key);
	SNode<T1, T2> * node = findC(key);
	if(node == nullptr) throw invalid_argument("no node with this key!");
	else if (parent == nullptr || parent == node) {
		root = nullptr;
		return;
	}
	SNode<T1, T2> * grand = nullptr;
	if (node->left == nullptr && node->right != nullptr)
		grand = node->right;
	else if (node->left != nullptr && node->right == nullptr)
		grand = node->left;
	else if (node->left == nullptr && node->right == nullptr)
		grand = nullptr;
	else if(node->left != nullptr && node->right != nullptr){
		SNode<T1, T2> * next = find_left_node(node->right);
		del_node(next->key);
		node->key = next->key;
		node->data = next->data;
		return;
	}

	if (parent->left == node) parent->left = grand;
	else if (parent->right == node) parent->right = grand;
	node = nullptr;
}


int main()
{
	SNode<int,int>*p1 = new SNode<int, int>(100);
	STree<int,int> t(p1);
	t.addC(123, 0);
	t.addC(55, 0);
	t.addC(13, 0);
	t.addC(45, 0);
	t.addC(88, 0);
	t.addC(8, 0);
	t.addC(233, 0);
	t.addC(14, 0);
	t.addC(60, 0);
	t.addC(50, 0);
	t.addC(66, 0);
	t.print();
	t.del_node(55);
	cout << "==================" << endl;
	t.print();
	return EXIT_SUCCESS;
}
