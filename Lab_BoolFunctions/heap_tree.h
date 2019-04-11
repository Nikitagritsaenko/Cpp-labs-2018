#pragma once
#include <iostream>
using namespace std;

class diagram_t 
{
	int SIZE;
	int *h;         
	int HeapSize; 
public:
	diagram_t(int n) {
		SIZE = n;
		h = new int[SIZE];
		HeapSize = 0;
	}
	diagram_t(diagram_t& p)
	{
		SIZE = p.SIZE;
		delete[] h;
		HeapSize = p.HeapSize;
		h = new int[SIZE];
		for (int i = 0; i < HeapSize; i++)
		{
			h[i] = p.h[i];
		}
	};
	~diagram_t() { delete[] h; };
	void addelem(int); 
	void outHeap();  
	void out(); 
	int getmax(); 
	void heapify(int);  
	void Push(char c);
	void Pop();
	void printHeapSolutionTree();
	void PrintTree(int i);
};
