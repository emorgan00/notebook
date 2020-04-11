#include <bits/stdc++.h>
using namespace std;
#define inf 1000000000


// SINGLE END POINT (multiple end point algorithms further below)


// Accepts an adjacency matrix. Returns the minimum cost from start to end.
// Use inf to indicate no edge. Runs in O(V^2).
int dijkstra(vector<vector<int>> adj, int start, int end) {

	int size = adj.size();
	vector<int> cost(size, inf);
	vector<bool> visited(size, 0);
	cost[start] = 0;

	while (1) {
		int mincost = 0, n = -1;
		for (int i = 0; i < size; i++)
			if (!visited[i] && cost[i] <= mincost) {
				n = i;
				mincost = cost[i];
			}
		visited[n] = 1;
		if (n == end)
			return mincost;
		if (n == -1)
			break;
		for (int i = 0; i < size; i++)
			cost[i] = min(cost[i], mincost+adj[n][i]);
	}
	return inf;
}

// Accepts an adjacency list. Returns the minimum cost from start to end.
// Pairs should be in the form {weight, destination}. Runs in O(E+VlogV).
int dijkstra(vector<vector<pair<int, int>>> adj, int start, int end) {

	int size = adj.size();
	vector<bool> visited(size, 0);
	priority_queue<pair<int, int>> heap;
	heap.push({0, start});

	while (!heap.empty()) {
		int n = heap.top().second;
		int mincost = -heap.top().first;
		heap.pop();
		if (visited[n])
			continue;
		visited[n] = 1;
		if (n == end)
			return mincost;
		for (auto p : adj[n])
			if (!visited[p.second])
				heap.push({-(mincost+p.first), p.second});
	}
	return inf;
}


// ALL END POINTS


// Accepts an adjacency matrix. Returns the minimum cost from start to all endpoints.
// Use inf to indicate no edge.
// Runs in O(V^2).
vector<int> dijkstra(vector<vector<int>> adj, int start) {

	int size = adj.size();
	vector<int> cost(size, inf);
	vector<bool> visited(size, 0);
	cost[start] = 0;

	while (1) {
		int mincost = 0, n = -1;
		for (int i = 0; i < size; i++)
			if (!visited[i] && cost[i] <= mincost) {
				n = i;
				mincost = cost[i];
			}
		visited[n] = 1;
		if (n == -1)
			break;
		for (int i = 0; i < size; i++)
			cost[i] = min(cost[i], mincost+adj[n][i]);
	}
	return cost;
}

// Accepts an adjacency list. Returns the minimum cost from start to all endpoints.
// Pairs should be in the form {weight, destination}.
// Runs in O(E+VlogV)
vector<int> dijkstra(vector<vector<pair<int, int>>> adj, int start) {

	int size = adj.size();
	vector<bool> visited(size, 0);
	priority_queue<pair<int, int>> heap;
	heap.push({0, start});
	vector<int> out(size, inf);

	while (!heap.empty()) {
		int n = heap.top().second;
		int mincost = -heap.top().first;
		heap.pop();
		if (visited[n])
			continue;
		visited[n] = 1;
		out[n] = mincost;
		for (auto p : adj[n])
			if (!visited[p.second])
				heap.push({-(mincost+p.first), p.second});
	}
	return out;
}