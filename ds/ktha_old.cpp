#include <bits/stdc++.h>
using namespace std;

// k-th ancestor finder. Uses the jump-pointer algorithm.
// O(nlogn) to set up, O(logk) to query.
struct ktha {

    vector<vector<int>> parent;
    vector<bool> visited;

    void _label_parent(int i, vector<vector<int>>& adj) {
        visited[i] = 1;
        for (int j : adj[i])
            if (!visited[j]) {
                parent[0][j] = i;
                _label_parent(j, adj);
            }
    }

    // Accepts an adjecency list. Can include or exlude parents, it works either way.
    ktha(vector<vector<int>>& adj, int root) {

        int maxexp = floor(log2(adj.size()));
        parent.assign(maxexp+1, vector<int>(adj.size()));
        visited.assign(adj.size(), 0);

        _label_parent(root, adj);
        for (int exp = 1; exp <= maxexp; exp++)
            for (int i = 0; i < adj.size(); i++)
                parent[exp][i] = parent[exp-1][parent[exp-1][i]];
    }

    // Returns the k-th ancestor of node i.
    int query(int i, int k) {
        for (int j = 0; (1<<j) <= k; j++)
            if (k&(1<<j))
                i = parent[j][i];
        return i;
    }
};