struct segtree {

    struct node {

    };

    node combine(node x, node y) {

    }

    constexpr static node identity = /* identity node */;

    vector<int> a, b;
    vector<node> tree;
    vector</* update type */> u;
    int n;

    segtree(vector</* value type */>& v) {

        n = 1<<int(ceil(log2(v.size())));
        tree.resize(2*n);
        a.resize(2*n); b.resize(2*n);
        u.assign(2*n, /* value corresponding to no update */);

        for (int i = 2*n-1; i > 0; i--) {
            if (i >= n) {
                a[i] = b[i] = i-n;
                if (i-n < v.size()) {
                    /* set value at tree[i] to v[i-n] */
                } else {
                    tree[i] = identity;
                }
            } else {
                a[i] = a[2*i];
                b[i] = b[2*i+1];
                tree[i] = combine(tree[2*i], tree[2*i+1]);
            }
        }
    }

    void push(int i) {
        if (/* there is no update */) return;
        /* perform the update at tree[i] */
        if (i < n) {
            /* propogate updates to children (children may already have updates) */
        }
        /* clear update at tree[i] */
    }

    void update(int l, int r, /* update type */ x, int i = 1) {
        if (l <= a[i] && r >= b[i]) {
            /* add an update at tree[i] (may already have update) */
        }
        push(i);
        if (l > b[i] || r < a[i] || (l <= a[i] && r >= b[i]))
            return;
        update(l, r, /* new update value */, 2*i);
        update(l, r, /* new update value */, 2*i+1);
        tree[i] = combine(tree[2*i], tree[2*i+1]);
    }

    node query(int l, int r, int i = 1) {
        push(i);
        if (l <= a[i] && r >= b[i])
            return tree[i];
        if (l > b[i] || r < a[i])
            return identity;
        return combine(query(l, r, 2*i), query(l, r, 2*i+1));
    }
};