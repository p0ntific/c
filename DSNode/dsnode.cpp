#include <iostream>
#include <stdexcept>
#include <bitset>
using namespace std;

int digit(int x, int n) {
	return (x >> n) % 2;
}

template <class T>
struct DSNode
{
	int key; //ключ
	T data;// элемент данных
	DSNode* left, * right; // указатели на сыновей
	DSNode(int k, DSNode* l = nullptr, DSNode* r = nullptr, T d = 0) :
		data(d), left(l), right(r), key(k) {} // конструктор
};

template <class T>
void f_print(DSNode<T>* r, int indent)
{
	if (r == nullptr) return;
	f_print(r->right, indent + 3);
	for (int i = 0; i < indent; ++i)
		cout << ' ';
	cout << bitset<6>(r->key) << endl;
	for (int i = 0; i < indent; ++i)
		cout << ' ';
	cout << '(' << r->data << ')' << endl;
	f_print(r->left, indent + 3);
}

template <class T>
void f_print_data(DSNode<T>* r)
{
	if (r == nullptr) return;
	f_print_data(r->right);

	cout << r->key << '-' << r->data << endl;
	f_print_data(r->left);
}

template <class T>
void f_insert(DSNode<T>* r,int deep, int key, T data)
{
	if (r == nullptr) 
		return;
	if (digit(key, deep)) 
	{
		if (r->right == nullptr) {
			int cur_digit = digit(key, deep);
			DSNode<T>* node = new DSNode<T>(key, nullptr, nullptr, data);
			r->right = node;
			return;
		}
		else f_insert(r->right, deep + 1, key, data);
	} 
	else 
	{
		if (r->left == nullptr) {
			int cur_digit = digit(key, deep);
			DSNode<T>* node = new DSNode<T>(key, nullptr, nullptr, data);
			r->left = node;
			return;
		}
		else f_insert(r->left, deep + 1, key, data);
	} 
}

template <class T>
DSNode<T>* f_search(DSNode<T>*p,int key)
{
	int deep = 0;
	while (p != nullptr) {
		if (p->key == key) break;
		else if (digit(key, deep)) p = p->right;
		else p = p->left;
		deep += 1;
	}
	return p;
}

template <class T>
DSNode<T>* f_search_parent(DSNode<T>*p,int key)
{
	int deep = 0;
	while (p != nullptr) {
		if (p->left->key == key || p->right->key == key) break;
		else if (digit(key, deep)) p = p->right;
		else p = p->left;
		deep += 1;
	}
	return p;
}

template <class T>
DSNode<T>* f_find_leaf(DSNode<T>* r)
{
	if (r->left != nullptr) return f_find_leaf(r->left);
	else if (r->right != nullptr) return f_find_leaf(r->right);
	else return r;
}


template <class T>
class DSTree {
public:
	DSTree()
		: root(nullptr)
	{
	}
	DSTree(DSNode<T>* p) : root(p) {}
	~DSTree() {
		DestroyNode(root);
	}

	void insert(int key, T data) { f_insert(root, 0, key, data); };

	DSNode<T>* search(int key) { return f_search(root, key); };
	DSNode<T>* search_parent(int key) { return f_search_parent(root, key); };

	void add(int key) {
		DSNode<T>* node = search(key);
		if (node == nullptr)
			f_insert(root, 0, key, 0);
		else {
			node->data += 1;
		}
	};

	void del_node(int key);

	void print(int indent = 0) { f_print(root, indent); };
	void print_data() { f_print_data(root); };

private:
	static void DestroyNode(DSNode<T>* node) {
		if (node) {
			DestroyNode(node->left);
			DestroyNode(node->right);
			delete node;
		}
	}

private:
	DSNode<T>* root;
};

template <class T>
void DSTree<T>::del_node(int key) {
	DSNode<T>* parent = search_parent(key);
	DSNode<T>* node = parent->left->key == key ? parent->left : parent->right;

	if (node->left != nullptr || node->right != nullptr) {
		DSNode<T>* leaf = f_find_leaf(node);
		del_node(leaf->key); 
		node->key = leaf->key;
		node->data = leaf->data;
	}
	else {
		if (parent->left->key == key) parent->left = nullptr;
		else parent->right = nullptr;
	}
}

int main()
{
	DSNode<int>
	* p1 = new DSNode<int>(8, nullptr, nullptr, 0);
	DSTree<int> t(p1);
	t.add(1);
	t.add(2);
	t.add(3);
	t.add(4);
	t.add(5);
	t.add(5);
	t.add(5);
	t.add(5);
	t.add(5);
	t.print_data();
	return EXIT_SUCCESS;
}
