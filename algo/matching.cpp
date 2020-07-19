// computes maximum matching in a bipartite graph
// N vertices on the left, and M vertices on the right
template<int N, int M>
struct matcher {

    vector<int> adj[N];
    int ord[N], L[N], R[M];
    bool vis[N];

    // add an edge between i on the left, and j on the right
    void edge(int i, int j) {
        adj[i].push_back(j);
    }

    bool dfs(int i) {
        if (vis[i]) return 0;
        vis[i] = 1;
        for (int j : adj[i])
            if (R[j] == -1) {
                L[i] = j;
                R[j] = i;
                return 1;
            }
        for (int j : adj[i])
            if (dfs(R[j])) {
                L[i] = j;
                R[j] = i;
                return 1;
            }
        return 0;
    }

    // returns a list of edges {left, right}. runs in O(E \sqrt V) time.
    vector<pair<int, int>> solve() {
        iota(ord, ord+N, 0);
        random_shuffle(ord, ord+N);
        fill(L, L+N, -1);
        fill(R, R+M, -1);
        bool v = 1;
        while (v) {
            v = 0;
            fill(vis, vis+N, 0);
            for (int i : ord)
                if (!vis[i] && L[i] == -1)
                    v |= dfs(i);
        }
        vector<pair<int, int>> out;
        for (int i = 0; i < N; i++)
            if (L[i] != -1)
                out.emplace_back(i, L[i]);
        return out;
    }
};

// http://www.cs.tau.ac.il/~zwick/grad-algo-0910/match.pdf
// about the randomization trick, see https://codeforces.com/blog/entry/58048