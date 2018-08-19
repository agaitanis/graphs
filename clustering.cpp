#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

class DisjointSet {
	public: 
		DisjointSet(int n);

		void merge(int i, int j);
		int find(int i);
		int get_size(int i);
		int get_num();

	private: 
		std::vector<int> m_parent;
		std::vector<int> m_ht;
		std::vector<int> m_sz;
		int m_num;
};

DisjointSet::DisjointSet(int n) :
	m_parent(n),
	m_ht(n),
	m_sz(n),
	m_num(n)
{
	for (int i = 0; i < n; i++) {
		m_parent[i] = i;
		m_ht[i] = 0;
		m_sz[i] = 1;
	}
}

int DisjointSet::get_size(int i)
{
	return m_sz[i];
}

int DisjointSet::get_num()
{
	return m_num;
}

int DisjointSet::find(int i)
{
	if (i != m_parent[i]) {
		m_parent[i] = find(m_parent[i]);
	}
	return m_parent[i];
}

void DisjointSet::merge(int i, int j)
{
	int i_id = find(i);
	int j_id = find(j);

	if (i_id == j_id) return;

	if (m_ht[i_id] > m_ht[j_id]) {
		m_parent[j_id] = i_id;
		m_sz[i_id] += m_sz[j_id];
	} else {
		m_parent[i_id] = j_id;
		if (m_ht[i_id] == m_ht[j_id]) {
			m_ht[j_id]++;
		}
		m_sz[j_id] += m_sz[i_id];
	}
	m_num--;
}

static double calc_dist(int x1, int y1, int x2, int y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

struct Edge {
	Edge(int u, int v, double d) : u(u), v(v), d(d) {}

	int u;
	int v;
	double d;
};

static bool EdgeCmp(const Edge &rhs, const Edge &lhs)
{
	return rhs.d < lhs.d;
}

static double clustering(vector<int> x, vector<int> y, int k)
{
	int n = (int)x.size();
	DisjointSet d_set(n);
	vector<Edge> edges;

	for (size_t i = 0; i < x.size(); i++) {
		for (size_t j = i + 1; j < x.size(); j++) {
			double d = calc_dist(x[i], y[i], x[j], y[j]);

			edges.push_back(Edge(i, j, d));
		}
	}

	sort(edges.begin(), edges.end(), EdgeCmp);

	for (size_t i = 0; i < edges.size(); i++) {
		Edge &edge = edges[i];

		if (d_set.find(edge.u) == d_set.find(edge.v)) continue;

		if (d_set.get_num() == k) {
			return edge.d;
		}

		d_set.merge(edge.u, edge.v);
	}

	return -1.;
} 

int main()
{
	size_t n;
	int k;
	cin >> n;
	vector<int> x(n), y(n);

	for (size_t i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}

	cin >> k;

	cout << setprecision(10) << clustering(x, y, k) << endl;
}
