// N vertices, flow and cost are measured with type T
template<int N, typename T>
struct mincostflow {

    const T inf_T = numeric_limits<T>::max();

    struct flow_edge { int v, u; T f, w, c; };
    vector<flow_edge> adj[N];
    T l[N]; int p[N], pv[N], pu[N], vis[N], s, t;

    // add an edge from i to j with capacity w and cost per unit flow c
    void edge(int i, int j, T w, T c, bool directed = true) {
        adj[i].push_back({j, int(adj[j].size()), 0, w, c});
        adj[j].push_back({i, int(adj[i].size())-1, 0, 0, -c});
        if (!directed) edge(j, i, w, c);
    }

    bool spfa() {
        fill(l, l+N, inf_T), l[s] = 0, pv[s] = -1;
        queue<int> q({s});
        while (!q.empty()) {
            int v = q.front(); q.pop();
            vis[v] = 0;
            for (int i = 0; i < adj[v].size(); i++) {
                auto& e = adj[v][i];
                if (l[v] != inf_T && e.f < e.w && l[v]+e.c < l[e.v]) {
                    l[e.v] = l[v]+e.c, pv[e.v] = v, pu[e.v] = i;
                    if (!vis[e.v]) q.push(e.v), vis[e.v] = 1;
                }
            }
        }
        return l[t] != inf_T;
    }

    T dfs(int v, T f) {
        if (v == t || !f)
            return f;
        for (; p[v] < adj[v].size(); p[v]++) {
            auto& e = adj[v][p[v]];
            if (v != pv[e.v] || p[v] != pu[e.v])
                continue;
            if (T x = dfs(e.v, min(f, e.w - e.f))) {
                e.f += x, adj[e.v][e.u].f -= x;
                return x;
            }
        }
        return 0;
    }

    // compute the maximum flow from s to t, and the minimum cost needed to do it, one-time use.
    // Dinic's algorithm, runs in O(V^2E), expected O(VE) on random sparse graphs
    pair<T, T> solve(int _s, int _t) {
        s = _s, t = _t; T f = 0, c = 0;
        while (spfa()) {
            fill(p, p+N, 0);
            while (T x = dfs(s, inf_T)) f += x;
        }
        for (int v = 0; v < N; v++)
            for (auto& e : adj[v])
                c += e.c*e.f;
        return {f, c/2};
    }

    // after calling solve(), return a component vector C s.t. C[i] \in {0, 1}
    // and i is reachable from s iff C[i] = 1. any edge from a 1 to a 0 is in the min cut
    vector<bool> cut() {
        vector<bool> out(N, 0); out[s] = 1;
        queue<int> q({s});
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto& e : adj[v])
                if (e.f < e.w && !out[e.v])
                    out[e.v] = 1, q.push(e.v);
        }
        return out;
    }
};