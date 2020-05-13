#include <bits/stdc++.h>
using namespace std;

// computes maximum matching in a bipartite graph
struct matcher {

    vector<vector<int>> adj;
    vector<int> ord, L, R;
    vector<bool> vis;

    // n edges on the left, and m edges on the right
    matcher(int n, int m) : adj(n), ord(n), vis(n), L(n, -1), R(m, -1) {
        std::iota(ord.begin(), ord.end(), 0);
        std::random_shuffle(ord.begin(), ord.end());
    }

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

    // returns a list of edges {left, right}. runs in O(E \sqrt V).
    vector<pair<int, int>> solve() {
        bool v = 1;
        while (v) {
            v = 0;
            fill(vis.begin(), vis.end(), 0);
            for (int i : ord)
                if (!vis[i] && L[i] == -1)
                    v |= dfs(i);
        }
        vector<pair<int, int>> out;
        for (int i = 0; i < adj.size(); i++)
            if (L[i] != -1)
                out.emplace_back(i, L[i]);
        return out;
    }
};

// http://www.cs.tau.ac.il/~zwick/grad-algo-0910/match.pdf
// about the randomization trick, see https://codeforces.com/blog/entry/58048