-
#include <bits/stdc++.h>
using namespace std;

// Accepts an adjecency list. Returns the vertices ordered in an Eulerian CIRCUIT.
// If no circuit exists, it returns an Eulerian path instead. If the adjacency list is
// sorted, then the resulting tour will be the lexicographically earliest one.
// Runs in O(E).

void tour_search(int i, vector<vector<int>>& adj, vector<int>& circuit) {

    // Hierholzer’s algorithm
    while (!adj[i].empty()) {
        int j = adj[i].back();
        adj[i].pop_back();
        for (int k = 0; k < adj[j].size(); k++)
            if (adj[j][k] == i) {
                adj[j].erase(adj[j].begin()+k);
                break;
            }
        tour_search(j, adj, circuit);
    }
    circuit.push_back(i);
}

vector<int> euleriantour(vector<vector<int>>& adj) {

    vector<int> odd, circuit;
    vector<vector<int>> copy(adj.size());

    for (int i = 0; i < adj.size(); i++)
        if (adj[i].size()%2 == 1)
            odd.push_back(i);

    for (int i = 0; i < adj.size(); i++)
        for (int j = adj[i].size()-1; j >= 0; j--)
            copy[i].push_back(adj[i][j]);

    // delete this part to remove print statements
    if (odd.size() == 0)
        cout << "[euleriantour] found a CIRCUIT" << endl;
    else if (odd.size() == 2)
        cout << "[euleriantour] found a PATH" << endl;
    else
        cout << "[euleriantour] found NOTHING" << endl;

    if (odd.size() == 0) {
        for (int i = 0; i < adj.size(); i++)
            if (!adj[i].empty()) {
                tour_search(i, copy, circuit);
                break;
            }
    } else if (odd.size() == 2)
        tour_search(odd[0], copy, circuit);

    // reverse the circuit to make it lexicographically earliest
    for (int i = 0; i < circuit.size()/2; i++)
        swap(circuit[circuit.size()-i-1], circuit[i]);

    return circuit;
}