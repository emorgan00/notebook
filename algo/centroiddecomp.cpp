struct centroid {

    int c, s;
    vector<vector<int>> adj;
    vector<bool> vis;
    vector<int> sz;

    centroid(int n) : adj(n), vis(n, 0), sz(n) {}
    centroid(vector<vector<int>> _adj) :
        adj(_adj), vis(_adj.size(), 0), sz(_adj.size()) {}

    // add an edge between i and j
    void edge(int i, int j) {
        adj[i].push_back(j);
        adj[j].push_back(i);
    }

    void dfs1(int i, int p) {
        sz[i] = 1;
        for (int j : adj[i])
            if (j != p && !vis[j]) {
                dfs1(j, i);
                sz[i] += sz[j];
            }
    }

    void dfs2(int i, int p) {
        bool v = sz[i] >= s;
        for (int j : adj[i])
            if (j != p && !vis[j]) {
                dfs2(j, i);
                v &= sz[j] <= s;
            }
        if (v) c = i;
    }

    // returns the centroid of the unvisited
    // component of the tree containing r
    int find(int r) {
        dfs1(r, r);
        s = sz[r]/2;
        dfs2(r, r);
        return c;
    }

    // returns the vertices of the tree ordered in a
    // pre-order dfs traversal of the centroid tree in O(VlogV)
    vector<int> list() {
        vector<int> out, stk = {0};
        while (!stk.empty()) {
            int i = find(stk.back()); stk.pop_back();
            out.push_back(i);
            vis[i] = 1;
            for (int j : adj[i])
                if (!vis[j])
                    stk.push_back(j);
        }
        return out;
    }

    // returns {root, children-only adjacency list} of the centroid tree
    pair<int, vector<vector<int>>> tree() {
        int root = find(0);
        vector<vector<int>> out(adj.size());
        vector<int> stk = {root};
        while (!stk.empty()) {
            int i = stk.back(); stk.pop_back();
            vis[i] = 1;
            for (int j : adj[i])
                if (!vis[j]) {
                    int r = find(j);
                    out[i].push_back(r);
                    stk.push_back(r);
                }
        }
        return {root, out};
    }
};