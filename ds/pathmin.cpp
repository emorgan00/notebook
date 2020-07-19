// unionfind and rmq are used for the pathmin struct below.
// there are some minor modifications to them, so copy over everything.

struct unionfind {

    int length;
    vector<int> parent;

    unionfind() {}

    unionfind(int s) {
        length = s;
        parent.assign(s, 0);
        std::iota(parent.begin(), parent.end(), 0);
    }

    int rep(int x) {
        while (x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void unite(int a, int b) {
        a = rep(a);
        b = rep(b);
        if (a == b)
            return;
        parent[b] = a;
    }

    // returns true if a and b are in the same set.
    inline bool query(int a, int b) {
        return rep(a) == rep(b);
    }
};

template<typename T>
struct rmq {

    vector<vector<T>> tree;

    rmq() {}

    rmq(vector<T>& data) {

        int n = data.size();
        int log2n = ceil(log2(n));
        tree.assign(log2n+1, vector<T>(n));
        tree[0] = data;

        for (int i = 1; i <= log2n; i++)
            for (int j = 0; j < n-(1<<i)+1; j++)
                tree[i][j] = min(tree[i-1][j], tree[i-1][j+(1<<i-1)]);
    }

    T query(int a, int b) {
        int n = floor(log2(b-a+1));
        return min(tree[n][a], tree[n][b-(1<<n)+1]);
    }
};

template<typename T>
struct pathmin {

    rmq<T> RMQ;
    vector<int> index;

    // Accepts an adjacency list with pairs in the form {weight, destination}.
    // Must be a tree. There can only be one edge between two vertices.
    // O(VlogV) to set up, O(1) to query.
    pathmin(vector<vector<pair<T, int>>>& adj) {

        int length = adj.size();
        unionfind UF(length);
        vector<int> pre(length), post(length), succ(length, -1);
        vector<T> weight(length);

        for (int i = 0; i < length; i++)
            pre[i] = post[i] = i;

        vector<tuple<T, int, int>> edges;
        edges.reserve(length-1);
        for (int i = 0; i < length; i++)
            for (auto p : adj[i])
                edges.push_back({p.first, i, p.second});

        sort(edges.begin(), edges.end(), greater<tuple<T, int, int>>());
        for (auto& edge : edges) {
            T w;
            int a, b;
            tie(w, a, b) = edge;
            if (UF.query(a, b))
                continue;

            int Arep = UF.rep(a), Brep = UF.rep(b);

            weight[post[Arep]] = w;
            succ[post[Arep]] = pre[Brep];
            UF.unite(Arep, Brep);

            int rep = UF.rep(Arep);
            pre[rep] = pre[Arep];
            post[rep] = post[Brep];
        }

        index.assign(length, 0);
        vector<T> values(length);
        int cur = pre[UF.rep(0)], i = 0;
        while (cur != -1) {
            index[cur] = i;
            values[i] = weight[cur];
            cur = succ[cur];
            i++;
        }

        RMQ = rmq(values);
    }

    // minimum edge along the path from a to b.
    T query(int a, int b) {
        a = index[a]; b = index[b];
        if (a > b) swap(a, b);
        return RMQ.query(a, b-1);
    }
};