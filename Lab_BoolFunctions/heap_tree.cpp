#include "heap_tree.h"

void diagram_t::addelem(int n) {
	int i, parent;
	i = HeapSize;
	h[i] = n;
	/*parent = (i - 1) / 2;
	while (parent >= 0 && i > 0) {
		if (h[i] < h[parent]) {
			int temp = h[i];
			h[i] = h[parent];
			h[parent] = temp;
		}
		i = parent;
		parent = (i - 1) / 2;
	}*/
	HeapSize++;
};

void diagram_t::outHeap(void) {
	int i = 0;
	int k = 1;
	while (i < HeapSize) {
		while ((i < k) && (i < HeapSize)) {
			cout << h[i] << " ";
			i++;
		}
		cout << endl;
		k = k * 2 + 1;
	}
};

void diagram_t::out(void) {
	for (int i = 0; i< HeapSize; i++) {
		cout << h[i] << " ";
	}
	cout << endl;
};

void diagram_t::heapify(int i) {
	int left, right;
	int temp;
	left = 2 * i + 1;
	right = 2 * i + 2;
	if (left < HeapSize) {
		if (h[i] < h[left]) {
			temp = h[i];
			h[i] = h[left];
			h[left] = temp;
			heapify(left);
		}
	}
	if (right < HeapSize) {
		if (h[i] < h[right]) {
			temp = h[i];
			h[i] = h[right];
			h[right] = temp;
			heapify(right);
		}
	}
}

int diagram_t::getmax(void) {
	int x;
	x = h[0];
	h[0] = h[HeapSize - 1];
	HeapSize--;
	heapify(0);
	return(x);
}

char _depth[2056];
int _di = 0;
void diagram_t::Push(char c)
{
	_depth[_di++] = ' ';
	_depth[_di++] = c;
	_depth[_di++] = ' ';
	_depth[_di++] = ' ';
	_depth[_di++] = ' ';
	_depth[_di++] = ' ';
	_depth[_di++] = ' ';
	_depth[_di] = 0;
}
void diagram_t::Pop()
{
	_depth[_di -= 7] = 0;
}


void diagram_t::PrintTree(int i)
{
	if (2 * (i + 1) <HeapSize || 2 * (i + 1) - 1 < HeapSize)
		cout << "x"<<h[i] << endl;
	else
		cout << h[i] << endl;

	if (2*(i+1) <HeapSize)
	{
		printf("%s `-0->", _depth);
		Push('|');
		PrintTree(2*(i+1));
		Pop();
	}
	if (2*(i+1)-1 < HeapSize)
	{
		printf("%s `-1->", _depth);
		Push(' ');
		PrintTree(2 * (i + 1) - 1);
		Pop();
	}
}

void diagram_t::printHeapSolutionTree()
{
	cout<<endl<<endl;
	cout << "Diagram of solutions" << endl;
	PrintTree(0);
}

