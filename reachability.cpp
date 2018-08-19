#include <iostream>
#include <vector>

using namespace std;

static void explore(int x, const vector<vector<int> > &adj, vector<int> &visited)
{
	const vector<int> &neibs = adj[x];

	visited[x] = 1;

	for (size_t i = 0; i < neibs.size(); i++) {
		int	neib = neibs[i];

		if (!visited[neib]) {
			explore(neib, adj, visited);
		}
	}
	
}

static int reach(const vector<vector<int> > &adj, int x, int y)
{
	vector<int> visited(adj.size(), 0);

	explore(x, adj, visited);

	return visited[y];
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
		adj[y - 1].push_back(x - 1);
	}

	int x, y;
	cin >> x >> y;

	cout << reach(adj, x - 1, y - 1) << endl;

	return 0;
}
