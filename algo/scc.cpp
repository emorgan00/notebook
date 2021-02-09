struct scc {

    vector<vector<int>> adj, c_adj, r_adj;
    vector<int> c, v, ord;

    scc(vector<vector<int>> _adj) : adj(_adj) {}

    void dfs(int i) {
        v[i] = 1;
        for (int j : adj[i])
            if (!v[j]) dfs(j);
        ord.pb(i);
    }

    void partition(int i, int t) {
        v[i] = 1, c[i] = t;
        for (int j : r_adj[i])
            if (!v[j]) partition(j, t);
    }

    // returns a component vector c s.t. c[i] == c[j] iff i and j
    // are in the same strongly connected component, runs in O(E).
    vector<int> components() {
        int n = adj.size(), t = 0;
        v.assign(n, 0), r_adj.resize(n);
        for (int i = 0; i < n; i++) {
            for (int j : adj[i]) r_adj[j].push_back(i);
            if (!v[i]) dfs(i);
        }
        v.assign(n, 0), c.assign(n, 0);
        for (int i = n-1; i >= 0; i--)
            if (!v[ord[i]]) partition(ord[i], t++);
        return c;
    }

    // returns an adjacency list over the scc's where an edge u->v means there is a
    // path i->j in the original graph if c[i] = u && c[j] = v, runs in O(E).
    vector<vector<int>> dag() {
        if (c.empty()) components();
        c_adj.resize(*max_element(c.begin(), c.end())+1);
        for (int i = 0; i < adj.size(); i++)
            for (int j : r_adj[i])
                if (c_adj[c[j]].empty() || i != c_adj[c[j]].back())
                    if (c[i] != c[j]) c_adj[j].push_back(i);
        return c_adj;
    }
};