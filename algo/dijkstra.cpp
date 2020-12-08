// Accepts an adjacency list. Returns the minimum cost from s to e.
// Pairs should be in the form {weight, destination}, runs in O(ElogV).
template<typename T>
T dijkstra(vector<vector<pair<T, int>>>& adj, int s, int e) {

    const static T inf_T = numeric_limits<T>::max();
    int n = adj.size();
    vector<bool> vis(n, 0);
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> heap;
    heap.push({0, s});

    while (!heap.empty()) {
        auto [c, i] = heap.top(); heap.pop();
        if (vis[i]) continue;
        vis[i] = 1;
        if (i == e) return c;
        for (auto& [w, j] : adj[i])
            if (!vis[j])
                heap.push({c+w, j});
    }
    return inf_T;
}

// Accepts an adjacency list. Returns the minimum cost from s to all vertices.
// Pairs should be in the form {weight, destination}, runs in O(ElogV).
template<typename T>
vector<T> dijkstra(vector<vector<pair<T, int>>>& adj, int s) {

    const static T inf_T = numeric_limits<T>::max();
    int n = adj.size();
    vector<bool> vis(n, 0);
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> heap;
    heap.push({0, s});
    vector<T> out(n, inf_T);

    while (!heap.empty()) {
        auto [c, i] = heap.top(); heap.pop();
        if (vis[i]) continue;
        vis[i] = 1;
        out[i] = c;
        for (auto& [w, j] : adj[i])
            if (!vis[j])
                heap.push({c+w, j});
    }
    return out;
}