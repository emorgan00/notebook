#include <bits/stdc++.h>
using namespace std;

// Accepts an adjacency list. Assumes that the graph is connected and acyclic.
// Runs in O(V+E).

vector<int> topologicalsort(vector<vector<int>>& adj) {

	int size = adj.size();
	vector<int> out, stk, in(size, 0);
	vector<bool> visited(size, 0);

	for (int i = 0; i < size; i++)
		for (int j : adj[i])
			in[j]++;
	for (int i = 0; i < size; i++)
		if (in[i] == 0)
			stk.push_back(i);

	while (!stk.empty()) {
		int i = stk.back();
		stk.pop_back();
		out.push_back(i);
		for (int j : adj[i]) {
			in[j]--;
			if (in[j] == 0)
				stk.push_back(j);
		}
	}
	return out;
}