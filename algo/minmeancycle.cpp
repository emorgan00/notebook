#include <bits/stdc++.h>
using namespace std;
#define inf 1e9

// Accepts an adjacency list. Returns the minimum mean weight of a cycle in the graph.
// Note: this assumes that the graph is strongly connected. If it isn't, first subdivide
//       the graph w/ kosaraju and then run on the individual components. It also assumes
//       that all weights are non-negative.
// Pairs should be in the form {weight, destination}. Runs in O(EV).

double minmeancycle(vector<vector<pair<int, int>>>& adj) {

	int size = adj.size();
	vector<vector<int>> delta(size+1, vector<int>(size, inf));
	delta[0][0] = 0;

	// Karp's algorithm
	for (int k = 1; k <= size; k++) {
		for (int i = 0; i < size; i++)
			for (auto edge : adj[i])
				delta[k][edge.second] = min(delta[k][edge.second], delta[k-1][i]+edge.first); 
	}

	double out = inf;
	for (int i = 0; i < size; i++) {
		double cycle = 0;
		for (int k = 0; k < size; k++)
			cycle = max(cycle, double(delta[size][i]-delta[k][i])/(size-k));
		out = min(out, cycle);
	}
	return out;
}