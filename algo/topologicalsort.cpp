// Accepts an adjacency list. Assumes that the graph is connected and acyclic.
// Runs in O(V+E).

vector<int> toposort(vector<vector<int>> adj) {
    vector<int> out, stk, in(adj.size(), 0);
    for (int i = 0; i < n; i++)
        for (int j : adj[i]) in[j]++;
    for (int i = 0; i < n; i++)
        if (!in[i]) stk.push_back(i);
    while (!stk.empty()) {
        int i = stk.back(); stk.pop_back();
        for (int j : adj[i])
            if (!--in[j]) stk.push_back(j);
    }
    return out;
}