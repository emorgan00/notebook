// computes maximum matching in a bipartite graph
// N vertices on the left, and M vertices on the right
template<int N, int M>
struct matching {

    vector<int> adj[N];
    int ord[N], vis[N], R[N], t;

    // add an edge between i on the left, and j on the right
    void edge(int i, int j) {
        adj[i].push_back(j);
    }

    bool dfs(int i) {
        vis[i] = t;
        for (int j : adj[i])
            if (R[j] == -1)
                return R[j] = i, 1;
        for (int j : adj[i])
            if (vis[R[j]] < t && dfs(R[j]))
                return R[j] = i, 1;
        return 0;
    }

    // returns a list of edges {left, right}. runs in O(E \sqrt V) time.
    vector<pair<int, int>> solve() {
        iota(ord, ord+N, 0);
        random_shuffle(ord, ord+N);
        fill(R, R+M, -1); t = 0;
        for (int i = 0; i < N; i++)
            if (!dfs(i)) break;
            else t++;
        vector<pair<int, int>> out;
        for (int i = 0; i < N; i++)
            if (R[i] != -1)
                out.emplace_back(R[i], i);
        return out;
    }
};

// http://www.cs.tau.ac.il/~zwick/grad-algo-0910/match.pdf
// about the randomization trick, see https://codeforces.com/blog/entry/58048