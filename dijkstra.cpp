#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Vertex {
	Vertex(int index, int dist) : index(index), dist(dist) {}

	bool operator<(const Vertex &rhs) const { return dist > rhs.dist; }

	int	index;
	int	dist;
};

static int distance(const vector<vector<int> > &adj, const vector<vector<int> > &cost, int s, int t)
{
	vector<long> dist(adj.size(), INT_MAX);
	priority_queue<Vertex> q;

	dist[s] = 0;
	q.push(Vertex(s, 0));

	while (!q.empty()) {
		int u = q.top().index;

		if (u == t) break;

		q.pop();

		for (size_t i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];

			if (dist[u] + cost[u][i] < dist[v]) {
				dist[v] = dist[u] + cost[u][i];
				q.push(Vertex(v, dist[v]));
			}
		}
	}

	if (dist[t] == INT_MAX) return -1;

	return dist[t];
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

	int s, t;
	cin >> s >> t;
	cout << distance(adj, cost, s - 1, t - 1) << endl;

	return 0;
}
