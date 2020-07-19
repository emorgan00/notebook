// Accepts an adjacency matrix. Returns a matrix where M[i][j]
// indicates whether vertex j is reachable from vertex i.
// Runs in O(EV). Note that if adj is a DAG, this is not optimal.
vector<vector<bool>> transitiveclosure(vector<vector<int>>& adj) {
    
    int size = adj.size();
    vector<vector<bool>> out(size, vector<bool>(size, 0));
    vector<int> stack;
    vector<bool> visited(size, 0);
    stack.reserve(size);

    for (int i = 0; i < size; i++) {
        stack.push_back(i);
        std::fill(visited.begin(), visited.end(), 0);
        while (!stack.empty()) {
            int j = stack.back();
            stack.pop_back();
            out[i][j] = 1;
            visited[j] = 1;
            for (int k : adj[j])
                if (!visited[k])
                    stack.push_back(k);
        }
    }
    return out;
}