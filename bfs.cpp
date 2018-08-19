#include <iostream>
#include <vector>
#include <queue>

using namespace std;

static int calc_dist(vector<vector<int> > &adj, int s, int t)
{
	vector<int> dist(adj.size(), -1);
	queue<int> q;

	dist[s] = 0;
	q.push(s);

	while (!q.empty()) {
		int u = q.front();

		q.pop();

		for (size_t i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];

			if (dist[v] == -1) {
				q.push(v);
				dist[v] = dist[u] + 1;
			}
		}
	}

	return dist[t];
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

	int s, t;
	cin >> s >> t;
	cout << calc_dist(adj, s - 1, t - 1) << endl;

	return 0;
}
