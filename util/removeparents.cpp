#include <bits/stdc++.h>
using namespace std;

// Takes an adjacency list (tree), and modifies it in place so that
// children no longer point to their parents. Runs in O(E+V).
void removeparents(vector<vector<int>>& adj, int root) {

    vector<int> stack = {root};
    while (!stack.empty()) {
        int i = stack.back();
        stack.pop_back();
        for (int j : adj[i]) {
            stack.push_back(j);
            adj[j].erase(find(adj[j].begin(), adj[j].end(), i));
        }
    }
}