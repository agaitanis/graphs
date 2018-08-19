#include <iostream>
#include <vector>

using namespace std;

static int explore(int x, const vector<vector<int> > &adj, vector<int> &visited, int &cnt, vector<int> &pre_visit, vector<int> &post_visit)
{
	visited[x] = 1;

	cnt++;
	pre_visit[x] = cnt;

	const vector<int> &neibs = adj[x];

	for (size_t i = 0; i < neibs.size(); i++) {
		int	y = neibs[i];

		if (pre_visit[y] && !post_visit[y]) return 1;

		if (!visited[y]) {
			if (explore(y, adj, visited, cnt, pre_visit, post_visit)) return 1;
		}
	}

	cnt++;
	post_visit[x] = cnt;

	return 0;
}

static int acyclic(const vector<vector<int> > &adj)
{
	vector<int> visited(adj.size(), 0);
	vector<int> pre_visit(adj.size(), 0);
	vector<int> post_visit(adj.size(), 0);
	int cnt = 0;

	for (size_t i = 0; i < adj.size(); i++) {
		int x = i;

		if (!visited[x]) {
			if (explore(x, adj, visited, cnt, pre_visit, post_visit)) return 1;
		}
	}

	return 0;
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
	cout << acyclic(adj) << endl;

	return 0;
}
