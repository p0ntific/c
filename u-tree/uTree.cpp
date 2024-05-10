#include <iostream>
using namespace std;

struct UNode
{
	int data; 
	UNode * left, * right, * parent;
	UNode(int d, UNode* l = nullptr, UNode* r = nullptr, UNode * p = nullptr) :
		data(d), left(l), right(r), parent(p) {
		if(l != nullptr) l->parent = this;
		if (r != nullptr) r->parent = this;
	}
};

void f_print(UNode* r, int indent = 0)
{
	if (r == nullptr) return;
	f_print(r->right, indent + 3);
	for (int i = 0; i < indent; ++i)
		cout << ' ';
	cout << r->data << endl;
	f_print(r->left, indent + 3);
}

struct UTree
{
	UNode* root; // корень дерева
	UTree(UNode* p) : root(p) {}

	void print() // метод печати
	{
		f_print(root); // вызывает рекурсивную функцию
	}
	void deleteNode(UNode * p) {
		if (p == nullptr) return;
		UNode* parent = p->parent;
		UNode* child = nullptr;
		if (p->left != nullptr) child = p->left;
		else if (p->right != nullptr) child = p->right;

		if (parent == nullptr) {
			p = nullptr;
			return;
		}

		if (parent->left == p) parent->left = child; 
		else if (parent->right == p) parent->right = child;
		if(child != nullptr)
			child->parent = parent;
	}
	void rotateLeft() // метод печати
	{
		UNode* prev_root = root;
		UNode* right_node = root->right;
		UNode* left_node = root->left;
		prev_root->right = right_node->left;
		right_node->left->parent = prev_root->right;
		root = right_node;
		root->parent = nullptr;
		prev_root->parent = root;
		root->left = prev_root;
	}
};
int main()
{
	UNode* p10 = new UNode(10),
		* p9 = new UNode(9, nullptr, p10),
		* p8 = new UNode(8),
		* p7 = new UNode(7),
		* p6 = new UNode(6),
		* p5 = new UNode(5,p8,p9),
		* p4 = new UNode(4),
		* p3 = new UNode(3, p6, p7),
		* p2 = new UNode(2, nullptr, p5),
		* p1 = new UNode(1, p2, p3);
	UTree t(p1);
	t.print();
	cout << "================" << endl;
	t.deleteNode(p7);
	t.print();
	return EXIT_SUCCESS;
}
