#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
struct DSNode
{
	int key; //ключ
	T data;// элемент данных
	DSNode* left, *right; // указатели на сыновей
	DSNode(int k,  DSNode* l = nullptr, DSNode* r = nullptr, T d = 0 ) :
		data(d), left(l), right(r), key(k) {} // конструктор
};

template <class T>
void f_print(DSNode<T>* r, int indent = 0)
{
	if (r == nullptr) return;
	f_print(r->right, indent + 3);
	for (int i = 0; i < indent; ++i)
		cout <<' ';
	cout << r->key <<'('<< r->data<< ')'<< endl;
	f_print(r->left, indent + 3);
}


template <class T>
class STree {
public:
	STree()
		: root(nullptr)
	{
	}
	STree(DSNode<T> * p) : root(p) {}
	~STree() {
		DestroyNode(root);
	}
	

	void print(int indent = 0) { f_print(root,indent); };

private:
	static void DestroyNode(DSNode<T1,T2>* node) {
		if (node) {
			DestroyNode(node->left);
			DestroyNode(node->right);
			delete node;
		}
	}

private:
	DSNode<T1,T2>* root;
};

int digit(int x, int n) {
	return (x & (1 << n)) != 0;
}

int main()
{
	DSNode<int>*p1 = new DSNode<int>(100);
	
	return EXIT_SUCCESS;
}
