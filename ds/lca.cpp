#include <bits/stdc++.h>
using namespace std;

// O(nlogn) to set up, O(1) to query
struct lca {

	vector<pair<int, int>> euler_walk;
	vector<vector<pair<int, int>>> range_mins;
	vector<int> walk_index;
	vector<bool> visited;

	void _label_walk(vector<vector<int>>& edges, int i, int depth) {
		visited[i] = 1;
		walk_index[i] = euler_walk.size();
		euler_walk.push_back({depth, i});
		for (int j : edges[i]) {
			if (visited[j]) continue;
			_label_walk(edges, j, depth+1);
			euler_walk.push_back({depth, i});
		}
	}

	// Accepts an adjecency list. Can include or exlude parents, it works either way.
	lca(vector<vector<int>>& edges, int root) {

		// set up the euler walk
		walk_index.assign(edges.size(), 0);
		visited.assign(edges.size(), 0);
		_label_walk(edges, root, 0);

		// set up RMQ lookup table
		range_mins.push_back({});
		for (int i = 0; i < euler_walk.size(); i++)
			range_mins.back().push_back(euler_walk[i]);
		for (int len = 2; len <= euler_walk.size(); len <<= 1) {
			auto prev = range_mins.back();
			range_mins.push_back({});
			for (int i = 0; i < euler_walk.size()-len+1; i++)
				range_mins.back().push_back(min(prev[i], prev[i+len/2]));
		}
	}

	int query(int i, int j) {
		int a = min(walk_index[i], walk_index[j]);
		int b = max(walk_index[i], walk_index[j]);
		if (b == a) return i;
		int n = floor(log2(b-a));
		return min(range_mins[n][a], range_mins[n][b-pow(2, n)+1]).second;
	}
};