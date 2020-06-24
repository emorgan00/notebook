struct segtree {

    struct node {

    };

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
                    tree[i] = /* v[i-n] */
                } else {
                    tree[i] = /* identity */
                }
            } else {
                a[i] = a[2*i];
                b[i] = b[2*i+1];
                /* compute node at tree[i] */
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
        if (l > b[i] || r < a[i] || l <= a[i] && r >= b[i])
            return;
        update(l, r, /* new update value */, 2*i);
        update(l, r, /* new update value */, 2*i+1);
        /* recompute node at tree[i] */
    }

    /* query return type */ query(int l, int r, int i = 1) {
        push(i);
        if (l <= a[i] && r >= b[i])
            return /* tree[i] */
        if (l > b[i] || r < a[i])
            return /* identity */
        return query(l, r, 2*i) /* combined with */ query(l, r, 2*i+1);
    }
};