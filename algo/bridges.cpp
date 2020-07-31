struct bridges {

    vector<int> low, tin;
    vector<bool> bridge;
    vector<vector<pair<int, int>>> adj;
    int e = 0, t = 0;

    bridges(int n) : adj(n), low(n, -1), tin(n, -1) {}

    // add an undirected edge between i and j
    void edge(int i, int j) {
        adj[i].push_back({j, e});
        adj[j].push_back({i, e++});
        bridge.push_back(0);
    }

    void dfs(int i, int p) {
        low[i] = tin[i] = ++t;
        for (auto& [j, k] : adj[i])
            if (k != p) {
                if (low[j] == -1) {
                    dfs(j, k);
                    low[i] = min(low[i], low[j]);
                    if (low[j] > low[i])
                        bridge[k] = 1;
                } else
                    low[i] = min(low[i], tin[j]);
            }
    }

    // returns a component vector for biconnected components in O(V+E).
    vector<int> components() {
        vector<int> comp(adj.size(), -1), stk;
        for (int i = 0; i < adj.size(); i++)
            if (low[i] == -1)
                dfs(i, -1);
        int c = 0;
        for (int i = 0; i < adj.size(); i++)
            if (comp[i] == -1) {
                stk.push_back(i);
                while (!stk.empty()) {
                    int j = stk.back(); stk.pop_back();
                    comp[j] = c;
                    for (auto& [k, l] : adj[j])
                        if (comp[k] == -1 && !bridge[l])
                            stk.push_back(k);
                }
                c++;
            }
        return comp;
    }
};