#include<iostream>
#include <fstream>
#include <list>
#include <queue>
#include <string>
#include <stack>
#include "2sat.h"
using namespace std;
class Graph
{
public:
	int V, E;    
	list <int> *adj;
	void DFSRec(int v, bool visited[]);
	Graph(int V);  
	void PrintAdj();
	void addEdge(int v, int w);
	void BFS(int s);
	void DFS1(int v);
	void DFS2(int v);
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list <int> [V+1];
}
void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
}
void Graph::PrintAdj()
{
	cout << "Adjacency list" << endl;
	for (int v = 1; v <= V; v++)
	{
		cout << v << " | ";
		for (list <int> ::iterator i = adj[v].begin(), j = adj[v].end(); i != j; ++i)
		{
			int& t = *i;
			cout << t << " ";
		}
		cout << endl;
	}
}
void Graph::DFSRec(int v, bool visited[])
{
	visited[v] = true;
	cout << v << " ";
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFSRec(*i, visited);
}
void Graph::DFS1(int v)
{
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	DFSRec(v, visited);
}
void Graph::BFS(int s)
{
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	queue <int> queue;
	visited[s] = true;
	queue.push(s);
	list<int>::iterator i;
	while (!queue.empty())
	{
		s = queue.front();
		cout << s << " ";
		queue.pop();
		for (i = adj[s].begin(); i != adj[s].end(); ++i)
		{
			if (!visited[*i])
			{
				visited[*i] = true;
				queue.push(*i);
			}
		}
	}
}
void Graph::DFS2(int s)
{
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	stack <int> stack;
	visited[s] = true;
	stack.push(s);
	list<int>::iterator i;
	while (!stack.empty())
	{
		s = stack.top();
		cout << s << " ";
		stack.pop();
		for (i = adj[s].begin(); i != adj[s].end(); ++i)
		{
			if (!visited[*i])
			{
				visited[*i] = true;
				stack.push(*i);
			}
		}
	}
}

void Create2CNF(int* a, int* b, int N, string s, Graph *g)
{
	int k = 0;
	for (int v = 1; v <= g->V; v++)
	{
		if (s[v - 1] == 'R')
		{
			a[k] = -(3 * (v - 1) + 2); b[k] = -(3 * (v - 1) + 3); k++;
			a[k] = (3 * (v - 1) + 2); b[k] = (3 * (v - 1) + 3); k++;
			a[k] = -(3 * (v - 1) + 1); b[k] = -(3 * (v - 1) + 1); k++;
		}
		else if (s[v - 1] == 'G')
		{
			a[k] = -(3 * (v - 1) + 1); b[k] = -(3 * (v - 1) + 3); k++;
			a[k] = (3 * (v - 1) + 1); b[k] = (3 * (v - 1) + 3); k++;
			a[k] = -(3 * (v - 1) + 2); b[k] = -(3 * (v - 1) + 2); k++;
		}
		else
		{
			a[k] = -(3 * (v - 1) + 1); b[k] = -(3 * (v - 1) + 2);k++;
			a[k] = (3 * (v - 1) + 1); b[k] = (3 * (v - 1) + 2);k++;
			a[k] = -(3 * (v - 1) + 3); b[k] = -(3 * (v - 1) + 3); k++;
		}
	}
	while (k < N)
	{
		for (int v = 1; v <= g->V; v++)
		{
			for (list <int> ::iterator i = g->adj[v].begin(), j = g->adj[v].end(); i != j; ++i)
			{
				int& t = *i;
				for (int p = 1; p <=3; p++)
				{ 
					a[k] = - (3 * (v - 1) + p);
					b[k] = - (3 * (t - 1) + p);
					k++;
				}
			}
		}
	}
}

int main()
{
	ifstream f("colored_graph.txt");
	int n, m;
	string s;
	f >> n >> m;
	f >> s;
	Graph g(n);
	int x, y;
	while (f >> x >> y)
		g.addEdge(x, y);
	f.close();

	int N = 3 * m + 3 * n;
	int *a = new int[N]();
	int *b = new int[N]();
	Create2CNF(a,b,N,s,&g);
	is2Satisfiable(3*n, N, a, b);

	system("pause");
	return 0;
}