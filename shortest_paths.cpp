#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using namespace std;

static void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s,
		vector<long long> &dist, vector<int> &reachable, vector<int> &shortest)
{
	vector<int> previous(adj.size(), -1);
	int	neg_v = -1;

	dist[s] = 0;
	reachable[s] = 1;

	for (size_t i = 0; i < adj.size(); i++) {
		for (size_t j = 0; j < adj.size(); j++) {
			int u = j;

			for (size_t k = 0; k < adj[u].size(); k++) {
				int v = adj[u][k];

				if (dist[u] == numeric_limits<long long>::max()) continue;

				if (dist[v] > dist[u] + cost[u][k]) {
					dist[v] = dist[u] + cost[u][k];
					previous[v] = u;
					reachable[v] = 1;
					if (i == adj.size() - 1) {
						neg_v = v;
						break;
					}
				}
			}
		}
	}

	if (neg_v != -1) {
		int x = neg_v;
		int y = x;

		for (size_t i = 0; i < adj.size(); i++) {
			shortest[x] = 0;
			x = previous[x];
			y = x;
		}

		while ((x = previous[x]) != y) {
			shortest[x] = 0;
		}
	}
}

int main()
{
	int n, m, s;
	cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	vector<vector<int> > cost(n, vector<int>());

	for (int i = 0; i < m; i++) {
		int x, y, w;

		cin >> x >> y >> w;
		adj[x - 1].push_back(y - 1);
		cost[x - 1].push_back(w);
	}
	cin >> s;

	vector<long long> dist(n, numeric_limits<long long>::max());
	vector<int> reachable(n, 0);
	vector<int> shortest(n, 1);

	shortest_paths(adj, cost, s - 1, dist, reachable, shortest);

	for (int i = 0; i < n; i++) {
		if (!reachable[i]) {
			cout << "*" << endl;
		} else if (!shortest[i]) {
			cout << "-" << endl;
		} else {
			cout << dist[i] << endl;
		}
	}

	return 0;
}
