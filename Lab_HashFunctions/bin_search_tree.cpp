#include <iostream>
#include "bin_search_tree.h"

int Eq(int a)
{
	return a;
}

bool BST::isLarger(int a, int b)
{
	return ((*hash)(a) > (*hash)(b));
}

bool BST::isEquivals(int a, int b)
{
	return ((*hash)(a) == (*hash)(b));
}

bin_tree_t* BST::InitTree(int x)
{
	tree = new bin_tree_t;
	tree->key = x;
	tree->left = tree->right = tree->next = NULL;
	return tree;
}

bin_tree_t* BST::Search(bin_tree_t* tree, int x)
{
	if (tree == NULL || tree->key == x)
		return tree;
	if (isEquivals(tree->key, x))
	{
		bin_tree_t* tmp = tree;
		while (tmp && tmp->key != x)
			tmp = tmp->next;
		if (tmp)
			return tmp;
	}
	if (isLarger(x, tree->key))
		return Search(tree->right, x);
	else if (isLarger(tree->key, x))
		return Search(tree->left, x);
}

bin_tree_t* BST::Add(bin_tree_t* tree, int x)
{
	if (tree == NULL) 
		return InitTree(x);
	if (isLarger(tree->key, x))
		tree->left = Add(tree->left, x);
	else if (isLarger(x, tree->key))
		tree->right = Add(tree->right, x);
	else 
	{
		bin_tree_t* tmp = tree;
		while (tmp->next)
			tmp = tmp->next;
		bin_tree_t* node = InitTree(x);
		tmp->next = node;
		return tree;
	}
	return tree;
}

bin_tree_t* BST::Delete(bin_tree_t* tree, int x)
{
	if (tree == NULL)
		return tree;
	if (isLarger(tree->key, x))
		tree->left = Delete(tree->left, x);
	else if (isLarger(x, tree->key))
		tree->right = Delete(tree->right, x);
	else if (tree->next != NULL)
	{
		bin_tree_t* tmp = tree->next;
		bin_tree_t* prev = tree;
		while (tmp->key != x)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		prev->next = tmp->next;
		free(tmp);
	}
	else if (tree->left != NULL && tree->right != NULL)
	{
		bin_tree_t* temp = tree->right;
		while (temp->left != NULL)
			temp = temp->left;
		tree->key = temp->key;
		tree->right = Delete(tree->right, tree->key);
	}
	else if (tree->left != NULL)
	{
		bin_tree_t *temp = tree;
		tree = tree->left;
		free(temp);
	}
	else
	{
		bin_tree_t *temp = tree;
		tree = tree->right;
		free(temp);
	}
	return tree;
}

void BST::FreeTree(bin_tree_t* tree)
{
	if (tree != NULL)
	{
		FreeTree(tree->left);
		FreeTree(tree->right);
		bin_tree_t* curr = tree->next;
		while (curr != NULL)
		{
			bin_tree_t* tmp = curr;
			curr = curr->next;
			free(tmp);
		}
		free(tree);
	}
}