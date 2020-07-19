// Accepts an adjacency list. Assumes that the graph is connected and acyclic.
// Runs in O(V+E).

vector<int> topologicalsort(vector<vector<int>>& adj) {

    int n = adj.size();
    vector<int> out, stk, in(n, 0);
    vector<bool> visited(n, 0);

    for (int i = 0; i < n; i++)
        for (int j : adj[i])
            in[j]++;
    for (int i = 0; i < n; i++)
        if (in[i] == 0)
            stk.push_back(i);

    while (!stk.empty()) {
        int i = stk.back();
        stk.pop_back();
        out.push_back(i);
        for (int j : adj[i])
            if (--in[j] == 0)
                stk.push_back(j);
    }
    return out;
}