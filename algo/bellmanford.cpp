#include <bits/stdc++.h>
using namespace std;


// NEGATIVE WEIGHT CYCLE DETECTION (shortest paths further below)


// Accepts an adjacency list. Returns true if the graph has a negative weight cycle.
// Pairs should be in the form {weight, destination}. Runs in O(EV).
template<typename T>
bool negcycle(vector<vector<pair<T, int>>> adj) {

    const static T inf_T = numeric_limits<T>::max();
    int n = adj.size();
    vector<T> c(n, 0);

    bool cyc;
    for (int v = 0; v < n; v++) {
        cyc = 0;
        for (int i = 0; i < n; i++)
            for (auto [w, j] : adj[i])
                if (c[i] != inf_T && c[j] > c[i]+w)
                    cyc = 1, c[j] = c[i]+w;
        if (!cyc) break;
    }
    return cyc;
}


// SINGLE ENDPOINT SHORTEST PATHS


// Accepts an adjacency list. Returns the shortest path from start to end.
// Returns -inf if there is a negative weight cycle on a path from start to end.
// Returns inf if there is no path from start to end.
// Pairs should be in the form {weight, destination}. Runs in O(EV).
int bellmanford(vector<vector<pair<int, int>>> adj, int start, int end) {

    int size = adj.size();
    vector<int> cost(size, inf);
    vector<bool> cycleflag(size, 0), visited(size, 0);
    cost[start] = 0;

    for (int v = 1; v < size; v++)
        for (int i = 0; i < size; i++)
            for (auto edge : adj[i])
                if (cost[edge.second] > cost[i]+edge.first && cost[i] != inf)
                    cost[edge.second] = cost[i]+edge.first;

    bool anycycle = 0;
    for (int i = 0; i < size; i++)
        for (auto edge : adj[i])
            if (cost[edge.second] > cost[i]+edge.first) {
                cycleflag[edge.second] = 1;
                anycycle = 1;
            }
    if (!anycycle)
        return cost[end];

    vector<int> stack;
    visited[start] = 1;
    stack.push_back(start);
    while (!stack.empty()) {
        int i = stack.back();
        stack.pop_back();
        for (auto edge : adj[i])
            if (!visited[edge.second]) {
                visited[edge.second] = 1;
                stack.push_back(edge.second);
            }
    }

    for (int i = 0; i < size; i++) {
        if (!cycleflag[i] && visited[i])
            visited[i] = 0;
        if (visited[i])
            stack.push_back(i);
    }
    while (!stack.empty()) {
        int i = stack.back();
        stack.pop_back();
        for (auto edge : adj[i])
            if (!visited[edge.second]) {
                visited[edge.second] = 1;
                stack.push_back(edge.second);
            }
    }

    if (visited[end])
        return -inf;
    return cost[end];
}


// ALL ENDPOINTS SHORTEST PATHS


// Accepts an adjacency list. Returns the minimum cost from start to all endpoints.
// Returns an empty vector if there is a negative weight cycle reachable from start.
// Pairs should be in the form {weight, destination}. Runs in O(EV).
vector<int> bellmanford(vector<vector<pair<int, int>>> adj, int start) {

    int size = adj.size();
    vector<int> cost(size, inf);
    cost[start] = 0;

    bool cycle;
    for (int v = 0; v < size; v++) {
        cycle = 0;
        for (int i = 0; i < size; i++)
            for (auto edge : adj[i])
                if (cost[edge.second] > cost[i]+edge.first && cost[i] != inf) {
                    cycle = 1;
                    cost[edge.second] = cost[i]+edge.first;
                }
        if (!cycle) break;
    }
    if (cycle)
        cost.clear();
    return cost;
}