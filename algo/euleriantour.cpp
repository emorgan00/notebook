// this is for directed graphs, a modified version
// for undirected graphs is below

struct tour {

    vector<vector<int>> adj;
    vector<int> in, bad, circ;

    // n vertices
    tour(int n) : adj(n), in(n, 0) {}

    void clear(int n) {
        adj.assign(n, {}); in.assign(n, 0);
        bad.clear(); circ.clear();
    }

    // directed edge from i to j
    void edge(int i, int j) {
        adj[j].push_back(i); in[i]++;
    }

    void dfs(int i) {
        // Hierholzer’s algorithm
        while (!adj[i].empty()) {
            int j = adj[i].back();
            adj[i].pop_back();
            dfs(j);
        }
        circ.push_back(i);
    }

    // runs in O(E). one time use. assumes graph is connected.
    vector<int> solve() {
        for (int i = 0; i < adj.size(); i++)
            if (adj[i].size() != in[i])
                bad.push_back(i);
        if (bad.size() == 0) { // found a circuit
            for (int i = 0; i < adj.size(); i++)
                if (!adj[i].empty()) {
                    dfs(i); return circ;
                }
        } else if (bad.size() == 2) { // found a path
            for (int i : bad)
                if (adj[i].size() == in[i]+1) {
                    dfs(i); return circ;
                }
        }
        return {};
    }
};

// here is the modified version for undirected graphs

struct tour {

    vector<vector<pair<int, int>>> adj;
    vector<int> bad, circ;
    vector<bool> vis;
    int t = 0;

    // n vertices
    tour(int n) : adj(n) {}

    void clear(int n) {
        adj.assign(n, {});
        bad.clear(); circ.clear(); vis.clear();
    }

    // undirected edge between i and j
    void edge(int i, int j) {
        adj[j].push_back({i, t});
        adj[i].push_back({j, t++});
        vis.push_back(0);
    }

    void dfs(int i) {
        // Hierholzer’s algorithm
        while (!adj[i].empty()) {
            auto [j, e] = adj[i].back();
            adj[i].pop_back();
            if (!vis[e]) {
                vis[e] = 1;
                dfs(j);
            }
        }
        circ.push_back(i);
    }

    // runs in O(E). one time use. assumes graph is connected.
    vector<int> solve() {
        for (int i = 0; i < adj.size(); i++)
            if (adj[i].size()%2 != 0)
                bad.push_back(i);
        if (bad.size() == 0) { // found a circuit
            for (int i = 0; i < adj.size(); i++)
                if (!adj[i].empty()) {
                    dfs(i); return circ;
                }
        } else if (bad.size() == 2) { // found a path
            for (int i : bad) {
                dfs(i); return circ;
            }
        }
        return {};
    }
};