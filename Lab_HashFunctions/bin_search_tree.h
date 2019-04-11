#pragma once
struct bin_tree_t
{
	int key;
	bin_tree_t* left;
	bin_tree_t* right;
	bin_tree_t* next;
};

int Eq(int a);

class BST
{
public:
	BST() { tree = NULL; hash = &Eq; }
	BST(int(*ptr)(int)) { tree = NULL; hash = ptr; }
	BST(int x, int(*ptr)(int)) { InitTree(x); hash = ptr;}
	~BST() { FreeTree(tree); };
	void Add(int x) { tree = Add(tree, x); }
	void Delete(int x) { tree = Delete(tree, x); }
	void Search(int x, bin_tree_t** t) { *t = Search(tree, x); }
	void Free() { FreeTree(tree); tree = NULL; }
	bool isLarger(int a, int b);
	bool isEquivals(int a, int b);
private:
	bin_tree_t* InitTree(int x);
	bin_tree_t* Add(bin_tree_t* tree, int x);
	bin_tree_t* Search(bin_tree_t* tree, int x);
	bin_tree_t* Delete(bin_tree_t* tree, int x);
	void FreeTree(bin_tree_t* tree);
	bin_tree_t* tree;
	int(*hash) (int);
};
