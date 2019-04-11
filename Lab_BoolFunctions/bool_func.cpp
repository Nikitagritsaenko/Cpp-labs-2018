#pragma once
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <map>
#include "parser.h"
#include "tree_printer.h"
#include "heap_tree.h"
#include <assert.h>
using namespace std;

bool Add2(bool x, bool y)
{
	return (x != y);
}

class truth_table_t
{
public:
	truth_table_t(FILE *in)
	{
		string str = Parser(in);
		n = GetVarNum(str);
		int columns = pow(2, n);
		vector <bool> bin(n);
		for (int i = 0; i < columns; ++i)
		{
			bin = Num2Bin(i, n);
			bool value = Eval(str, bin);
			table.push_back(value);
		}
	}
	truth_table_t(FILE *in, int i)
	{
		char c;
		int k = 0;
		while (fscanf(in, "%c", &c) != -1)
		{
			if (c != EOF)
			{
				if (c == '1')
					table.push_back(true);
				if (c == '0')
					table.push_back(false);
				k++;
			}

		}
		n = log(k) / log(2);
	}

	void Print()
	{
		int size = table.size();
		vector <bool> bin(n);
		cout << "The truth table" << endl;
		for (int i = 0; i < size; ++i)
		{
			bin = Num2Bin(i, n);
			for (int j = 1; j <= n; ++j)
			{
				cout << bin[j] << "  ";
			}
			cout << "| " << table[i] << endl;
		}
		cout << endl;
	};
	vector <bool> GetTable()
	{
		return table;
	};
	int GetN() { return n; };
private:
	vector <bool> table;
	int n;
};

class poly_zheg_t
{
public:
	poly_zheg_t(truth_table_t *table)
	{
		vector <bool> pasc = table->GetTable();
		n = table->GetN();
		int size = pasc.size();
		for (int i = 0; i < size; i++)
			coeff.push_back(0);
		if (pasc[0] == true)
			coeff[0] = 1;
		for (int i = 1; i < size; i++)
		{
			for (int j = 1; j <= size - i; j++)
			{
				pasc[j - 1] = Add2(pasc[j - 1], pasc[j]);
			}
			if (pasc[0] == true)
				coeff[i] = 1;
		}
	};
	void Print()
	{
		vector <bool> bin(n);
		int size = pow(2, n);
		char res;
		cout << "Zhegalkin polynom" << endl;
		if (coeff[0] == true)
			cout << "1 + ";

		for (int i = 1; i < size; i++)
		{
			bin = Num2Bin(i, n);

			if (coeff[i] == true)
			{
				for (int j = 1; j <= n; j++)
				{
					if (bin[j] == true)
					{
						res = 'a' + j - 1;
						cout << res;
					}
				}
				cout << " + ";
			}
		}
		cout << "\b\b  ";
	};
private:
	vector <bool> coeff;
	int n;
};

typedef struct
{
	LARGE_INTEGER t0, t1;
	LARGE_INTEGER frequency;
} timer_t;
void TimerCreate(timer_t* self)
{
	assert(self);
	QueryPerformanceFrequency(&self->frequency);
	QueryPerformanceCounter(&self->t1);
	self->t0 = self->t1;
}
double TimerTick(timer_t* self)
{
	assert(self);
	self->t0 = self->t1;
	QueryPerformanceCounter(&self->t1);
	return 1000.0 * (double)(self->t1.QuadPart - self->t0.QuadPart) / (double)self->frequency.QuadPart;
}

/*class diagram_t
{
public:
	diagram_t(truth_table_t *table) {
		ptr = new tree_t; ptr->l = NULL; ptr->r = NULL;
		vector <bool> results = table->GetTable();
		int n = table->GetN();
		vector <bool> bin(n);
		int size = pow(2, n);
		for (int i = 0; i < size; i++)
		{
			bin = Num2Bin(i, n);
			tree_t* curr = ptr;
			for (int j = 1; j <= n; j++) {
				if (bin[j] == true) {

					if (curr->r == NULL) {
						curr->r = new tree_t; curr->r->l = NULL; curr->r->r = NULL; curr->r->res = true;
					}
					curr = curr->r;
				}
				else
				{
					if (curr->l == NULL) {
						curr->l = new tree_t; curr->l->l = NULL; curr->l->r = NULL; curr->l->res = false;
					}
					curr = curr->l;
				}
			}
			if (curr->r == NULL) {
				curr->r = new tree_t; curr->r->l = NULL; curr->r->r = NULL;
			}
			curr = curr->r;
			curr->res = results[i];
		}
	};
	void Print()
	{
		cout << "\n\nThe diagram of solutions\n";
		PrintTree(ptr);
	}
	tree_t* ptr;
};*/

class k_map_t
{
public:
	k_map_t(truth_table_t *table)
	{
		vector <bool> results = table->GetTable();
		n = table->GetN();
		map = results;
	}
	vector <bool> Kmap2Table() { return map; }
	void Print()
	{
		int columns = n / 2;
		int rows = n - columns;
		int size_columns = pow(2, columns);
		int size_row = pow(2, rows);
		cout << "\nk-Map" << endl;
		for (int i = 0; i < size_columns; i++)
		{
			for (int j = 0; j < size_row; j++)
			{
				cout << map[i * size_row + j] << ' ';
			}
			cout << endl;
		}
	}
	vector <bool> map;
	int n;
};

void createHeapSolutionTree(diagram_t* p, truth_table_t* table)
{
	int n = table->GetN();
	int size = (int)pow(2, n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < (int)pow(2, i); j++)
		{
			p->addelem(i + 1);
		}
	}
	for (int i = 0; i < size; i++)
		p->addelem(table->GetTable().at(size - i - 1));
}

class bool_func_t
{
public:
	bool_func_t(FILE *in)
	{
		table = new truth_table_t(in);
		//zheg = new poly_zheg_t(table);
		//kMap = new k_map_t(table);
		//diagram = new diagram_t((int)pow(2, table->GetN() + 1) - 1);
	};
	bool_func_t(FILE *in, int i)
	{
		table = new truth_table_t(in, i);
		//zheg = new poly_zheg_t(table);
		//diagram = new diagram_t(table);
		//kMap = new k_map_t(table);
	};
	void PrintSDNF()
	{
		vector <bool> results = table->GetTable();
		int n = table->GetN();
		int size = pow(2, n);
		vector <bool> bin(n);
		cout << "\nSDNF\n";
		for (int i = 0; i < size; i++)
		{
			bin = Num2Bin(i, n);
			if (results[i] == true)
			{
				cout << '(';
				for (int j = 1; j <= n; j++)
				{
					char res = 'a' + j - 1;
					if (bin[j] == true)
						cout << res;
					else
						cout << '!' << res;
					if (j != n)
						cout << "&";
				}
				cout << ")v";
			}
		}
		cout << "\b ";
	}
	void PrintSKNF()
	{
		vector <bool> results = table->GetTable();
		int n = table->GetN();
		int size = pow(2, n);
		vector <bool> bin(n);
		cout << "\nSDNF\n";
		for (int i = 0; i < size; i++)
		{
			bin = Num2Bin(i, n);
			if (results[i] == false)
			{
				cout << '(';
				for (int j = 1; j <= n; j++)
				{
					char res = 'a' + j - 1;
					if (bin[j] == false)
						cout << res;
					else
						cout << '!' << res;
					if (j != n)
						cout << "v";
				}
				cout << ")&";
			}
		}
		cout << "\b ";
	}
	void PrintTree()
	{
		createHeapSolutionTree(diagram, table);
		diagram->printHeapSolutionTree();
	}
	truth_table_t* table;
	poly_zheg_t* zheg;
	diagram_t* diagram;
	k_map_t* kMap;
};

int main(void)
{
	int i = 0;
	FILE* in = fopen("bool.txt", "r");
	timer_t timer;
	double dt = 0.0;
	TimerCreate(&timer);
	TimerTick(&timer);
	bool_func_t* func = new bool_func_t(in);
	dt = TimerTick(&timer);
	printf("Time: %lf", dt);
	//func->table->Print();
	//func->zheg->Print();
	/*func->PrintTree();
	func->kMap->Print();
	func->PrintSDNF();
	func->PrintSKNF();*/

	//experiment
	/*int i = 0;
	FILE* in = fopen("picture.txt", "r");
	bool_func_t* func = new bool_func_t(in, i);
	func->kMap->Print();
	func->PrintSDNF();*/
	delete func;
	system("pause");
	return 0;
}