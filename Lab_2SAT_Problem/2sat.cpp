#include<iostream>
#include <queue>
#include <stack>
#include "2sat.h"
using namespace std;
const int MAX = 100000;
vector<int> adj[MAX];
vector<int> adjInv[MAX];
bool visited[MAX];
bool visitedInv[MAX];
stack<int> s;
int scc[MAX];
int counter = 1;

shift FillShift(int a, int b, int n)
{
	shift s;
	if (a > 0)
		s.a = n;
	else
		s.a = 0;
	if (b >= 0)
		s.b = 0;
	else
		s.b = n;
	return s;
}

void addEdges(int a, int b)
{
	adj[a].push_back(b);
}

void addEdgesInverse(int a, int b)
{
	adjInv[b].push_back(a);
}

void dfsFirst(int u)
{
	if (visited[u])
		return;

	visited[u] = 1;

	for (int i = 0; i < adj[u].size(); i++)
		dfsFirst(adj[u][i]);

	s.push(u);
}

void dfsSecond(int u)
{
	if (visitedInv[u])
		return;

	visitedInv[u] = 1;

	for (int i = 0; i < adjInv[u].size(); i++)
		dfsSecond(adjInv[u][i]);

	scc[u] = counter;
}

int sign(int a)
{
	if (a > 0)
		return 1;
	if (a < 0)
		return -1;
	return 0;
}

void is2Satisfiable(int n, int m, int a[], int b[])
{
	for (int i = 0; i < m; i++)
	{
		int x = a[i], y = b[i];
		shift s = FillShift(x, y, n);
		addEdges(sign(x)*x + s.a, sign(y)*y + s.b);
		addEdgesInverse(sign(x)*x + s.a, sign(y)*y + s.b);
		x = b[i]; y = a[i];
		s = FillShift(x, y, n);
		addEdges(sign(x)*x + s.a, sign(y)*y + s.b);
		addEdgesInverse(sign(x)*x + s.a, sign(y)*y + s.b);	

	}

	for (int i = 1; i <= 2 * n; i++)
		if (!visited[i])
			dfsFirst(i);

	while (!s.empty())
	{
		int n = s.top();
		s.pop();

		if (!visitedInv[n])
		{
			dfsSecond(n);
			counter++;
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (scc[i] == scc[i + n])
		{
			cout << "Impossible." << endl;
			return;
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		int ans = scc[i] > scc[i + n] ? 1 : 0;
		if (ans == 1)
		{
			if (i % 3 == 1)
				cout << "R";
			else if (i % 3 == 2)
				cout << "G";
			else
				cout << "B";
		}
	}
	cout << endl;
}

/*if (a[i] > 0 && b[i] > 0)
		{
			addEdges(a[i] + n, b[i]);
			addEdgesInverse(a[i] + n, b[i]);
			addEdges(b[i] + n, a[i]);
			addEdgesInverse(b[i] + n, a[i]);
		}

		else if (a[i] > 0 && b[i] < 0)
		{
			addEdges(a[i] + n, n - b[i]);
			addEdgesInverse(a[i] + n, n - b[i]);
			addEdges(-b[i], a[i]);
			addEdgesInverse(-b[i], a[i]);
		}

		else if (a[i] < 0 && b[i]>0)
		{
			addEdges(-a[i], b[i]);
			addEdgesInverse(-a[i], b[i]);
			addEdges(b[i] + n, n - a[i]);
			addEdgesInverse(b[i] + n, n - a[i]);
		}

		else
		{
			addEdges(-a[i], n - b[i]);
			addEdgesInverse(-a[i], n - b[i]);
			addEdges(-b[i], n - a[i]);
			addEdgesInverse(-b[i], n - a[i]);
		}*/