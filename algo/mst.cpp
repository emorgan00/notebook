#include <bits/stdc++.h>
using namespace std;
#define inf 1e9

// Accepts an adjecency matrix. Returns the sum of the weights of the MST.
// Use inf to show that two vertices are NOT connected. Runs in O(V^2).
int mst(vector<vector<int>>& adj) {
	
	vector<bool> visited(adj.size(), 0);
	vector<int> cost(adj.size(), inf);

	cost[0] = 0;
	int out = 0;

	// Prim's algorithm
	for (int k = 0; k < adj.size(); k++) {

		int leastcost = inf, next = -1;
		for (int i = 0; i < adj.size(); i++)
			if (!visited[i] && cost[i] < leastcost) {
				leastcost = cost[i];
				next = i;
			}

		visited[next] = 1;
		out += leastcost;

		for (int i = 0; i < adj.size(); i++)
			cost[i] = min(cost[i], adj[next][i]);
	}
	return out;
}

// This is used for Kruskal's algorithm below.
struct unionfind {

	int length;
	vector<int> parent, rank;

	unionfind(int s) {
		length = s;
		rank = vector<int>(s, 0);
		parent = vector<int>(s);
		for (int i = 0; i < s; i++)
			parent[i] = i;
	}

	int rep(int x) {
		while (x != parent[x]) {
			parent[x] = parent[parent[x]];
			x = parent[x];
		}
		return x;
	}

	void unite(int a, int b) {
		a = rep(a);
		b = rep(b);
		if (a == b)
			return;
		if (rank[a] < rank[b])
			swap(a, b);
		parent[b] = a;
		if (rank[a] == rank[b])
			rank[a]++;
	}

	bool query(int a, int b) {
		return rep(a) == rep(b);
	}
};

// Accepts an EDGE LIST in the form {weight, start, end}. Returns the sum
// of the weights of the MST. The vertices should be labeled from 0..N.
// Runs in O(ElogE).
int mst(vector<tuple<int, int, int>>& adj) {

	// Kruskal's algorithm
	sort(adj.begin(), adj.end());
	int size = 0;
	for (int i = 0; i < adj.size(); i++)
		size = max(size, max(get<1>(adj[i]), get<2>(adj[i]))+1);

	unionfind UF(size);
	int out = 0;

	for (auto edge : adj) {
		int a = get<1>(edge), b = get<2>(edge);
		if (!UF.query(a, b)) {
			out += get<0>(edge);
			UF.unite(a, b);
		}
	}
	return out;
}

// Accepts an ADJACENCY LIST in the form {weight, end}. Requires the function above.
int mst(vector<vector<pair<int, int>>>& adj) {
	vector<tuple<int, int, int>> edges;
	for (int i = 0; i < adj.size(); i++)
		for (auto e : adj[i])
			edges.push_back({e.first, i, e.second});
	return mst(edges);
}