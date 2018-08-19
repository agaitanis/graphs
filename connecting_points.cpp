#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <climits>
#include <set>

using namespace std;

static double calc_dist(int x1, int y1, int x2, int y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

static double minimum_distance(vector<int> x, vector<int> y)
{
	double result = 0.;
	size_t n = x.size();
	vector<double> cost(n, INT_MAX);
	vector<int> parent(n, -1);
	set<pair<double, int> > q;

	cost[0] = 0;
	q.insert(make_pair(cost[0], 0));

	for (size_t i = 1; i < n; i++) {
		q.insert(make_pair(cost[i], i));
	}

	while (!q.empty()) {
		set<pair<double, int> >::iterator it = q.begin();
		int	v = it->second;

		q.erase(it);

		for (size_t z = 0; z < n; z++) {
			if (z == v) continue;

			set<pair<double, int> >::iterator it2 = q.find(make_pair(cost[z], z));
			if (it2 == q.end()) continue;

			double d = calc_dist(x[v], y[v], x[z], y[z]);
			if (cost[z] <= d) continue;

			cost[z] = d;
			parent[z] = v;

			q.erase(it2);
			q.insert(make_pair(cost[z], z));
		}
	}

	for (size_t i = 0; i < n; i++) {
		result += cost[i];
	}

	return result;
} 

int main()
{
	size_t n;
	cin >> n;
	vector<int> x(n), y(n);

	for (size_t i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}
	cout << setprecision(10) << minimum_distance(x, y) << endl;
}
