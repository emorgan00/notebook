#include <bits/stdc++.h>
using namespace std;
#define inf 1e9

// Accepts an adjacency matrix. Returns the maximum flow through the graph.
// Runs in O(VE^2)
template<typename T>
T maxflow(vector<vector<T>>& adj, int source, int sink) {

	T out = 0;
	int size = adj.size();

	// copy adj into flow. Delete this section and replace flow with adj if
	// you want to have the function alter the graph.
	vector<vector<T>> flow(size, vector<T>(size));
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			flow[i][j] = adj[i][j];
	
	vector<int> parent(size);
	vector<T> maxflow(size);
	vector<bool> visited(size);

	// Edmonds–Karp algorithm
	while (1) {

		for (int i = 0; i < size; i++) {
			visited[i] = 0;
			maxflow[i] = 0;
		}
		maxflow[source] = inf;

		// compute max-flow path w/ Dijkstra's
		while (1) {

			T best = sink;
			for (int i = 0; i < size; i++)
				if (!visited[i] && maxflow[i] > maxflow[best])
					best = i;
			if (best == sink)
				break;
			visited[best] = 1;

			for (int i = 0; i < size; i++) {
				if (best == i)
					continue;
				T newflow = min(maxflow[best], flow[best][i]);
				if (newflow > maxflow[i]) {
					parent[i] = best;
					maxflow[i] = newflow;
				}
			}
		}

		out += maxflow[sink];
		if (maxflow[sink] == 0)
			break;

		// create residual graph
		int cur = sink;
		while (cur != source) {
			int next = parent[cur];
			flow[cur][next] += maxflow[sink];
			flow[next][cur] -= maxflow[sink];
			cur = next;
		}
	}
	return out;
}