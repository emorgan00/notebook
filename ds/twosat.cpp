struct twosat {

    int size;
    vector<vector<int>> adj;

    vector<bool> on, out;
    vector<int> low, depth, stack, comp;
    int index, cur;

    twosat(int s) : size(s), adj(2*s), out(s, 0) {}

    bool connect(int i) {

        // Tarjan's strongly connected components algorithm
        low[i] = depth[i] = ++index;
        stack.push_back(i);
        on[i] = 1;
        for (int j : adj[i]) {
            if (depth[j] == -1) {
                connect(j);
                low[i] = min(low[i], low[j]);
            } else if (on[j])
                low[i] = min(low[i], depth[j]);
        }

        // Aspvall, Plass & Tarjan algorithm
        if (low[i] == depth[i]) {
            int j = -1;
            while (i != j) {
                j = stack.back(); stack.pop_back();
                int k = (j+size)%(2*size);
                if (comp[k] == cur)
                    return true;
                if (comp[j] == -1 && comp[k] == -1)
                    out[j%size] = j >= size;
                comp[j] = cur;
            }
            cur++;
        }
        return false;
    }

    // returns {} if no solution, otherwise returns
    // a vector of bools indicating a solution.
    // runs in O(V+E), where V is the number of variables,
    // and E is the number of restrictions.
    vector<bool> solve() {

        depth.assign(2*size, -1);
        low.assign(2*size, -1);
        comp.assign(2*size, -1);
        on.assign(2*size, 0);
        stack.clear();
        index = cur = 0;

        for (int i = 0; i < 2*size; i++)
            if (depth[i] == -1 && connect(i))
                return {};
        return out;
    }

    // declare that (x is a) implies (y is b)
    inline void implies(int x, bool a, int y, bool b) {
        adj[x+(a ? size : 0)].push_back(y+(b ? size : 0));
        adj[y+(b ? 0 : size)].push_back(x+(a ? 0 : size));
    }

    // declare that x is true/false
    inline void set(int x, bool a) {
        adj[x+(a ? 0 : size)].push_back(x+(a ? size : 0));
    }
};