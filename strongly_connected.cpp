#include <algorithm>
#include <iostream>
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

static vector<vector<int> > get_reverse_graph(const vector<vector<int> > &adj)
{
	vector<vector<int> > r_adj(adj.size());

	for (size_t i = 0; i < adj.size(); i++) {
		int	x = i;

		for (size_t j = 0; j < adj[i].size(); j++) {
			int	y = adj[i][j];

			r_adj[y].push_back(x);
		}
	}

	return r_adj;
}

static void explore2(int x, const vector<vector<int> > &adj, vector<int> &visited)
{
	visited[x] = 1;

	const vector<int> &neibs = adj[x];

	for (size_t i = 0; i < neibs.size(); i++) {
		int     y = neibs[i];

		if (!visited[y]) {
			explore2(y, adj, visited);
		}
	}
}

static int number_of_strongly_connected_components(const vector<vector<int> > &adj)
{
	vector<vector<int> > r_adj = get_reverse_graph(adj);
	vector<int> order = toposort(r_adj);
	vector<int> visited(adj.size(), 0);
	int	cnt = 0;

	for (size_t i = 0; i < order.size(); i++) {
		int	x = order[i];

		if (!visited[x]) {
			explore2(x, adj, visited);
			cnt++;
		}
	}

	return cnt;
}

int main()
{
	size_t n, m;
	cin >> n >> m;
	vector<vector<int> > adj(n);

	for (size_t i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;

		adj[x - 1].push_back(y - 1);
	}

	cout << number_of_strongly_connected_components(adj) << endl;

	return 0;
}
