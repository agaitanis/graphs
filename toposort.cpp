#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

static void explore(int x, const vector<vector<int> > &adj, vector<int> &visited, vector<int> &order)
{
	visited[x] = 1;

	const vector<int> &neibs = adj[x];

	for (size_t i = 0; i < neibs.size(); i++) {
		int     y = neibs[i];

		if (!visited[y]) {
			explore(y, adj, visited, order);
		}
	}

	order.push_back(x);
}

static vector<int> toposort(const vector<vector<int> > &adj)
{
	vector<int> visited(adj.size(), 0);
	vector<int> order;

	for (size_t i = 0; i < adj.size(); i++) {
		int x = i;

		if (!visited[x]) {
			explore(x, adj, visited, order);
		}
	}

	reverse(order.begin(), order.end());

	return order;
}

int main()
{
	size_t n, m;
	cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());

	for (size_t i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;

		adj[x - 1].push_back(y - 1);
	}

	vector<int> order = toposort(adj);

	for (size_t i = 0; i < order.size(); i++) {
		cout << order[i] + 1 << " ";
	}
	cout << endl;

	return 0;
}
