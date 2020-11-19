struct dsu {

    vector<int> p, sz;
    vector<array<int, 2>> stk;

    dsu(int n) : p(n), sz(n, 1) {
        iota(p.begin(), p.end(), 0);
    }

    int rep(int x) {
        while (x != p[x]) x = p[x];
        return x;
    }

    void unite(int a, int b) {
        a = rep(a), b = rep(b);
        if (sz[a] < sz[b]) swap(a, b);
        stk.pb({a, b});
        if (a != b) p[b] = a, sz[a] += sz[b];
    }

    // returns true if a and b are in the same set.
    bool query(int a, int b) {
        return rep(a) == rep(b);
    }

    // returns the size of the set containing x
    int size(int x) {
        return sz[rep(x)];
    }

    // pop a change off of the stack and undo it
    void undo() {
        auto [a, b] = stk.back(); stk.pop_back();
        if (a != b) p[b] = b, sz[a] -= sz[b];
    }
};