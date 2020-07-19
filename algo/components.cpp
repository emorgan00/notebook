// returns {number of connected components, vector of labels}
// where each label is an integer from 0 to c-1 (c is number of components)

pair<int, vector<int>> components(vector<vector<int>>& adj) {
    int size = adj.size();
    vector<bool> vis(size, 0);
    vector<int> c(size), s;
    int t = -1;
    for (int i = 0; i < size; i++)
        if (!vis[i]) {
            s.push_back(i); c[i] = ++t; vis[i] = 1;
            while (!s.empty()) {
                int j = s.back(); s.pop_back();
                for (auto k : adj[j])
                    if (!vis[k]) {
                        vis[k] = 1;
                        c[k] = t;
                        s.push_back(k);
                    }
            }
        }
    return make_pair(t+1, c);
}

// this is a conceptually trivial algorithm, but it comes
// up a lot so I have it here just for convenience