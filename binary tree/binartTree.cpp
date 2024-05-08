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

BNode * get_left_grand_child(BNode* r)
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
	if(r->left != nullptr) return get_left_leaf(r->left);
	else if (r->right != nullptr) return get_left_leaf(r->right);
	else return r;
}
BNode* get_second_left_leaf(BNode* r)
{
	static BNode * parent = nullptr;
	if (r->right != nullptr)  
		parent = r; 
	if(r->left != nullptr) return get_second_left_leaf(r->left);
	else if (r->right != nullptr) return get_second_left_leaf(r->right);
	else {
		BNode * ans = get_left_leaf(parent->right);
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
struct BTree
{
	BNode* root; // корень дерева
	BTree(BNode* p) : root(p) {}

	// конструктор по указателю на узел
	void print() // метод печати
	{
		f_print(root); // вызывает рекурсивную функцию
	}
	BNode* getLeftNode() {
		return get_left_node(root);
	}
	BNode* getLeftGrandChild() {
		return get_left_grand_child(root);
	}	
	BNode* getLeftLeaf() {
		return get_left_leaf(root);
	}
	BNode* getSecondLeftLeaf() {
		return get_second_left_leaf(root);
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
};
int main()
{
	BNode* p10 = new BNode(10),
		* p9 = new BNode(9, nullptr, p10),
		* p8 = new BNode(8),
		* p7 = new BNode(7),
		* p6 = new BNode(6),
		* p5 = new BNode(5,p8,p9),
		* p4 = new BNode(4),
		* p3 = new BNode(3, p6, p7),
		* p2 = new BNode(2, nullptr, p5),
		* p1 = new BNode(1, p2, p3);
	BTree t(p1);
	t.print();
	cout << t.getSecondLeftLeaf()->data << endl;
	return EXIT_SUCCESS;
}
