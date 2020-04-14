#include <bits/stdc++.h>
using namespace std;

// Tarjan's bridge finding algorithm. Accepts an adjacency list.
// Returns an edge list containing all bridges. Runs in O(V+E).

vector<int> low, tin;
vector<pair<int, int>> bridges_out;
int bridges_t;

void bridges_dfs(vector<vector<int>>& adj, int i, int p) {

    // Tarjan's algorithm
    low[i] = tin[i] = ++bridges_t;
    for (int j : adj[i])
        if (j != p) {
            if (low[j] == -1) {
                bridges_dfs(adj, j, i);
                low[i] = min(low[i], tin[j]);
                if (low[j] > low[i])
                    bridges_out.emplace_back(i, j);
            } else
                low[i] = min(low[i], tin[j]);
        }
}

vector<pair<int, int>> bridges(vector<vector<int>>& adj) {

    int size = adj.size();
    low.assign(size, -1);
    tin.assign(size, -1);
    bridges_out.clear();
    bridges_t = 0;

    bridges_dfs(adj, 0, 0);
    return bridges_out;
}