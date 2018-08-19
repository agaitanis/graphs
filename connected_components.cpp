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

static int number_of_components(vector<vector<int> > &adj)
{
	vector<int> visited(adj.size(), 0);
	int cnt = 0;

	for (size_t i = 0; i < adj.size(); i++) {
		int	x = i;

		if (!visited[x]) {
			explore(x, adj, visited);
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
		adj[y - 1].push_back(x - 1);
	}

	cout << number_of_components(adj) << endl;

	return 0;

}
