// Accepts an adjacency list, and returns a vector of which component
// each vertex is in. Runs in O(V+E).

void visit(int i, vector<vector<int>>& adj, vector<int>& order, vector<bool>& visited) {
	visited[i] = 1;
	for (int j : adj[i])
		if (!visited[j])
			visit(j, adj, order, visited);
	order.push_back(i);
}

void partition(int i, int c, vector<int>& component, vector<vector<int>>& adj, vector<bool>& visited) {
	visited[i] = 1;
	component[i] = c;
	for (int j : adj[i])
		if (!visited[j])
			partition(j, c, component, adj, visited);
}

// accepts an adjacency list, unweighted.
vector<int> kosaraju(vector<vector<int>>& adj) {

	int size = adj.size();
	vector<int> order, out(size);
	vector<vector<int>> rev_adj(size);
	vector<bool> visited(size, 0);

	for (int i = 0; i < size; i++)
		if (!visited[i])
			visit(i, adj, order, visited);

	for (int i = 0; i < size; i++)
		visited[i] = 0;
	for (int i = 0; i < size; i++)
		for (int j : adj[i])
			rev_adj[j].push_back(i);

	int c = -1;
	for (int i = size-1; i >= 0; i--)
		if (!visited[order[i]])
			partition(order[i], ++c, out, rev_adj, visited);

	return out;
}

// Accepts an adjacency list, as well as the component vector produced by kosaraju.
// Returns an adjacency list, which is the component-wise DAG of the graph.
// Runs in O(E).
vector<vector<int>> kosaraju_dag(vector<vector<int>>& adj, vector<int>& components) {

    int count = 0;
    for (auto& x : components) count = max(count, x+1);

	vector<unordered_set<int>> dag(count);
	for (int i = 0; i < adj.size(); i++)
		for (int j : adj[i])
			if (components[i] != components[j])
				dag[components[i]].insert(components[j]);

	vector<vector<int>> out(count);
	for (int i = 0; i < count; i++)
		for (int j : dag[i])
			out[i].push_back(j);
	return out;
}