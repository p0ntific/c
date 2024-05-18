#include <iostream>
using namespace std;

struct BNode
{
	int data; // элемент данных
	BNode* left, * right; // указатели на сыновей
	BNode(int d, BNode* l = nullptr, BNode* r = nullptr) :
		data(d), left(l), right(r) {} // конструктор
};

void f_print(BNode* r, int indent = 0)
{
	if (r == nullptr) return;
	f_print(r->right, indent + 3);
	for (int i = 0; i < indent; ++i)
		cout << ' ';
	cout << r->data << endl;
	f_print(r->left, indent + 3);
}

BNode* get_left_node(BNode* r)
{
	if (r->left == nullptr) return r;
	return get_left_node(r->left);
}

BNode* get_left_grand_child(BNode* r)
{
	if (r == nullptr) return nullptr;
	BNode* left_child = r->left;
	BNode* right_child = r->right;
	if (left_child == nullptr || right_child == nullptr) return nullptr;
	else if (left_child->left != nullptr) return left_child->left;
	else if (left_child->right != nullptr) return left_child->right;
	else if (right_child->left != nullptr) return right_child->left;
	else return left_child->right;
}

BNode* get_left_leaf(BNode* r)
{
	if (r->left != nullptr) return get_left_leaf(r->left);
	else if (r->right != nullptr) return get_left_leaf(r->right);
	else return r;
}
BNode* get_second_left_leaf(BNode* r)
{
	static BNode* parent = nullptr;
	if (r->right != nullptr)
		parent = r;
	if (r->left != nullptr) return get_second_left_leaf(r->left);
	else if (r->right != nullptr) return get_second_left_leaf(r->right);
	else {
		BNode* ans = get_left_leaf(parent->right);
		parent = nullptr;
		return ans;
	}
}
BNode* get_left_leaf_parent(BNode* r)
{
	if (r->left != nullptr) {
		if (r->left->left == nullptr && r->left->right == nullptr) return r;
		return get_left_leaf_parent(r->left);
	}
	else if (r->right != nullptr) {
		if (r->right->left == nullptr && r->right->right == nullptr) return r;
		return get_left_leaf_parent(r->right);
	}
	else return r;

}

int f_count(BNode* p)
{
	
	if (p == nullptr)
		return 0;
	return 1 + f_count(p->left) + f_count(p->right);
}
int count_tree_sum(BNode* p)
{
	
	if (p == nullptr)
		return 0;
	return p->data + count_tree_sum(p->left) + count_tree_sum(p->right);
}
int count_negative_nodes(BNode* p)
{
	if (p == nullptr)
		return 0;
	return (p->data < 0 ? 1 : 0) + count_negative_nodes(p->left) + count_negative_nodes(p->right);
}

int f_height(BNode* p) {
	if (p == nullptr)
		return 0;
	else {
		int left_height = f_height(p->left);
		int right_height = f_height(p->right);

		return max(left_height, right_height) + 1;
	}
}
void f_reflect(BNode* p) {
	if (p == nullptr)
		return;
	else {
		BNode* tmp = p->left;
		p->left = p->right;
		p->right = tmp;
		f_reflect(p->left);
		f_reflect(p->right);
	}
}

int f_mult(BNode* p)
{
	if (p == nullptr)
		return 1;

	int total = (p->left != nullptr && p->right != nullptr) ? p->data : 1 ;

	return total * f_mult(p->left) * f_mult(p->right);
}
int f_min(BNode* p)
{
	if (p == nullptr)
		return 100000;

	return min( min(p->data , f_min(p->left)) , f_min(p->right));
}

void f_del(BNode*& p) // указатель p передается по ссылке
{
	if (p == nullptr) // дерево пусто
		return;
	f_del(p->left); // удалить левое поддерево
	f_del(p->right); // удалить правое поддерево
	delete p; // удалить сам узел
	p = nullptr; // обнулить указатель
}
void f_del_leaves(BNode*& p) // указатель p передается по ссылке
{
	if (p == nullptr) // дерево пусто
		return;
	if (p->left == nullptr && p->right == nullptr) {
		delete p; // удалить сам узел
		p = nullptr; // обнулить указатель
	}
	else {
		f_del_leaves(p->left); // удалить левое поддерево
		f_del_leaves(p->right); // удалить правое поддерево
	}
}
void f_del0(BNode*& p)
{
	if (p == nullptr) // дерево пусто
		return;
	f_del0(p->left); // удалить левое поддерево
	f_del0(p->right); // удалить правое поддерево
	if (p->data == 0) f_del(p);
}

void f_del1(BNode*& p)
{
	if (p == nullptr ) // дерево пусто
		return;
	
	if (p->left != nullptr && p->left->data == 1) {
		f_del(p->left->left);
		BNode * tmp = p->left->right;
		delete p->left;
		p->left = tmp;
		return;
	}
	if (p->right != nullptr && p->right->data == 1) {
		f_del(p->right->left);
		BNode * tmp = p->right->right;
		delete p->right;
		p->right = tmp;
		return;
	}
	f_del1(p->left);
	f_del1(p->right);
}



struct BTree
{
	BNode* root; // корень дерева
	BTree(BNode* p) : root(p) {}

	// конструктор по указателю на узел
	void print() // метод печати
	{
		f_print(root); // вызывает рекурсивную функцию
	}
	BNode* getLeftNode() 
	{
		return get_left_node(root);
	}
	BNode* getLeftGrandChild() 
	{
		return get_left_grand_child(root);
	}
	BNode* getLeftLeaf() 
	{
		return get_left_leaf(root);
	}
	BNode* getSecondLeftLeaf() 
	{
		return get_second_left_leaf(root);
	}

	int count()
	{
		return f_count(root);
	}
	int countTreeSum()
	{
		return count_tree_sum(root);
	}
	int countNegativeNodes()
	{
		return count_negative_nodes(root);
	}
	int height() 
	{
		return f_height(root);
	}
	void reflect() 
	{
		f_reflect(root);
	}
	int mult() 
	{
		return f_mult(root);
	}
	int min() 
	{
		return f_min(root);
	}

	void deleteLeftLeaf() {
		BNode* parent = get_left_leaf_parent(root);
		if (parent != nullptr) {
			if (parent->left != nullptr) parent->left = nullptr;
			else parent->right = nullptr;
		}
	}
	
	void rotateLeft() // метод печати
	{
		BNode* prev_root = root;
		BNode* right_node = root->right;
		BNode* left_node = root->left;
		prev_root->right = right_node->left;
		root = right_node;
		root->left = prev_root;
	}


	void del0() {
		f_del0(root);
	}

	void del1() {
		f_del1(root);
	}

	void delLeaves () {
		f_del_leaves(root);
	}

	~BTree()
	{
		f_del(root); // удалить дерево
	}
};

int main()
{
	BNode* p10 = new BNode(10),
		* p9 = new BNode(9, nullptr, p10),
		* p8 = new BNode(8),
		* p7 = new BNode(7),
		* p6 = new BNode(6),
		* p5 = new BNode(1, p8, p9),
		* p4 = new BNode(55),
		* p3 = new BNode(14, p6, p7),
		* p2 = new BNode(13, p4, p5),
		* p1 = new BNode(12, p2, p3);
	BTree t(p1);
	t.print();
	t.del1();
	cout << "============" << endl;
	t.print();
	return EXIT_SUCCESS;
}
