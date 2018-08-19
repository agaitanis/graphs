#include <iostream>
#include <vector>
#include <climits>

using namespace std;

static int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost)
{
	vector<long> dist(adj.size(), INT_MAX);

	dist[0] = 0;

	for (size_t i = 0; i < adj.size(); i++) {
		for (size_t j = 0; j < adj.size(); j++) {
			int u = j;

			for (size_t k = 0; k < adj[u].size(); k++) {
				int v = adj[u][k];

				if (dist[v] > dist[u] + cost[u][k]) {
					dist[v] = dist[u] + cost[u][k];
					if (i == adj.size() - 1) {
						return 1;
					}
				}
			}
		}
	}

	return 0;
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	vector<vector<int> > cost(n, vector<int>());

	for (int i = 0; i < m; i++) {
		int x, y, w;
		cin >> x >> y >> w;
		adj[x - 1].push_back(y - 1);
		cost[x - 1].push_back(w);
	}

	cout << negative_cycle(adj, cost) << endl;

	return 0;
}
