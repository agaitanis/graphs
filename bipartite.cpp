#include <iostream>
#include <vector>
#include <queue>

using namespace std;

static int bipartite(vector<vector<int> > &adj)
{
	if (adj.empty()) return 1;

	vector<int> group(adj.size(), 0);
	queue<int> q;
	int s = 0;

	q.push(s);
	group[s] = 1;

	while (!q.empty()) {
		int u = q.front();

		q.pop();

		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];

			if (group[v] == 0) {
				group[v] = -group[u];
				q.push(v);
			} else if (group[v] == group[u]) {
				return 0;
			}
		}
	}

	return 1;
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());

	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;

		adj[x - 1].push_back(y - 1);
		adj[y - 1].push_back(x - 1);
	}
	cout << bipartite(adj) << endl;

	return 0;
}
