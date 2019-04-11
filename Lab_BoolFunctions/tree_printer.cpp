#include <stdio.h>
#include <iostream>
#include "tree_printer.h"
using namespace std;
char depth[2056];
int di;

void Push(char c)
{
	depth[di++] = ' ';
	depth[di++] = c;
	depth[di++] = ' ';
	depth[di++] = ' ';
	depth[di] = 0;
}

void Pop()
{
	depth[di -= 4] = 0;
}

void PrintTree(tree_t* tree)
{
	if (tree->res != 205)
		printf("%d\n", tree->res);

	if (tree->l)
	{
		printf("%s `--", depth);
		Push('|');
		PrintTree(tree->l);
		Pop();
	}
	if (tree->r)
	{
		printf("%s `--", depth);
		Push(' ');
		PrintTree(tree->r);
		Pop();
	}
}

/*void PrintTree(vector <pair<bool, bool>> &tree, int i)
{
	if (i < tree.size())
		printf("(%d)\n", tree[i].first ? 1 : 0);

	if ((2 * i + 1) < tree.size() && tree[2 * i + 1].second)
	{
		printf("%s `--", depth);
		Push('|');
		PrintTree(tree, 2 * i + 1);
		Pop();

		printf("%s `--", depth);
		Push(' ');
		PrintTree(tree, 2 * i + 2);
		Pop();
	}
}*/