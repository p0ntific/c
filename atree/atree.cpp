#include <iostream>
#include <vector>
using namespace std;

template<class T>
struct ANode
{
	T data;
	ANode<T>* child, * right;
	ANode(T d, ANode<T>* c = nullptr, ANode<T>* r = nullptr) :
		data(d), child(c), right(r) {}
};



template <class T>
void f_print(ANode<T>* p, int d = 0) 
{
	if (p == nullptr) return;
	for (int i = 0; i < d; i++)
		cout << ' ';
	cout << p->data << endl;
	f_print(p->child, d + 3);
	f_print(p->right, d);
}

template <class T>
int f_count(ANode<T>* p)
{
	int c = 0;
	if (p == nullptr) return c;
	p = p->child;
	while (p != nullptr)
	{
		c++;
		p = p->right;
	}
	return c;
}


template <class T>
int f_count_grand_childs(ANode<T>* p)
{
	ANode<T>* grand = nullptr;
	int c = 0;
	if (p == nullptr || p->child == nullptr) return c;
	p = p->child; //первый сын
	while (p != nullptr)
	{
		grand = p->child;
		while(grand != nullptr){
			c++;
			grand = grand->right;
		}
		p = p->right;
	}
	return c;
}

template <class T>
ANode<T>* find_with_d1_d2(ANode<T>* p, T d1, T d2)
{
	ANode<T>* grand = nullptr;
	if (p == nullptr || p->child == nullptr) return nullptr;
	p = p->child; //первый сын
	while (p != nullptr)
	{
		if(p->data == d1){
			grand = p->child;
			while (grand != nullptr) {
				if (grand->data == d2) return p;
				grand = grand->right;
			}
		}
		p = p->right;
	}
	return nullptr;
}
template <class T>
ANode<T>* find_with_array(ANode<T>* p, vector <int> arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (p == nullptr) return nullptr;
		p = p->child;
		int cur_index = arr[i];
		for (int i = 0; i < cur_index; i++)
		{
			if (p == nullptr) break;
			p = p->right;
		}
	}
	return p;
}

template<class T>
struct ATree
{
	ANode <T>* root;
	ATree(ANode<T>* p) : root(p) {}
	void print()
	{
		f_print(root);
	}
	int count()
	{
		return f_count(root);
	}
	int countGrandChilds()
	{
		return f_count_grand_childs(root);
	}
	ANode<T>* findWithD1D2(T d1, T d2) {
		return find_with_d1_d2(root, d1, d2);
	}
	ANode<T>* findWithArray(vector <int> arr) {
		return find_with_array(root, arr);
	}
	void add_first(T d);
	void del_first();
	void flatt();
};

template <class T>
void ATree<T>::add_first(T d) // d - данные узла
{
	ANode<T>* t;
	t = new ANode<T>(d, nullptr, root->child);
	root->child = t;
}


template<class T>
void ATree<T>::del_first()
{
	ANode<T>* t, * t1, * t2;
	t1 = root->child;
	t2 = t1->child;
	t = t2;
	while (t->right != 0)
		t = t->right;
	t->right = t1->right;
	root->child = t2;
	delete t1;
}

template<class T>
void ATree<T>::flatt()
{
	
}


int main()
{
	ANode <int>* p10 = new ANode <int>(10),
		* p9 = new ANode <int>(9, nullptr, p10),
		* p8 = new ANode <int>(8),
		* p7 = new ANode <int>(7),
		* p6 = new ANode <int>(6, nullptr, p7),
		* p5 = new ANode <int>(5, nullptr, p6),
		* p4 = new ANode <int>(4, p9),
		* p3 = new ANode <int>(3, p8, p4),
		* p2 = new ANode <int>(2, p5, p3),
		* p1 = new ANode <int>(1, p2);
	ATree<int> t(p1);
	t.print();
	ANode<int>* find_p = t.findWithArray({ 2,1 });
	if (find_p != nullptr) cout << find_p->data;
	return EXIT_SUCCESS;
}
