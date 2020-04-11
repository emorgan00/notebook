#include <bits/stdc++.h>
using namespace std;

// Accepts an adjacency list. Assumes that the graph is connected and acyclic.
// Runs in O(V+E).
vector<int> topologicalsort(vector<vector<int>>& adj) {

	int size = adj.size(), back = adj.size()-1;
	vector<int> out, stack, indegree(size, 0);
	vector<bool> visited(size, 0);

	for (int i = 0; i < size; i++)
		for (int j : adj[i])
			indegree[j]++;

	// Kahn's algorithm
	for (int i = 0; i < size; i++)
		if (indegree[i] == 0)
			stack.push_back(i);

	while (!stack.empty()) {
		int i = stack.back();
		stack.pop_back();
		out.push_back(i);
		for (int j : adj[i]) {
			indegree[j]--;
			if (indegree[j] == 0)
				stack.push_back(j);
		}
	}
	return out;
}