#include <bits/stdc++.h>
using namespace std;

struct euleriantour {

    vector<vector<int>> adj;
    vector<int> in, bad, circ;

    // n vertices
    euleriantour(int n) : adj(n), in(n, 0) {}

    // directed edge from i to j
    void edge(int i, int j) {
        adj[j].push_back(i);
        in[i]++;
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
                    dfs(i);
                    break;
                }
        } else if (bad.size() == 2) { // found a path
            for (int i : bad)
                if (adj[i].size() == in[i]+1)
                    dfs(i);
        }

        return circ;
    }
};