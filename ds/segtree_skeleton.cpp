struct segtree {

    struct node {
        int a, b;
        /* value and update */
    };

    vector<node> tree;
    int n;

    segtree(vector</* value type */>& a) {
        n = 1<<int(ceil(log2(a.size())));
        tree.resize(2*n);
        for (int i = 2*n-1; i > 0; i--) {
            if (i >= n) {
                tree[i].a = tree[i].b = i-n;
                if (i-n < a.size()) {
                    /* set value at tree[i] to a[i-n] */
                } else {
                    /* set value at tree[i] to identity */
                }
            } else {
                tree[i].a = tree[2*i].a;
                tree[i].b = tree[2*i+1].b;
                /* recalculate value at tree[i] */
            }
            /* clear update at tree[i] */
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
        push(i);
        if (l > tree[i].b || r < tree[i].a)
            return;
        if (l <= tree[i].a && r >= tree[i].b) {
            /* add an update at tree[i] */
            push(i);
        } else {
            update(l, r, /* new update value */, 2*i);
            update(l, r, /* new update value */, 2*i+1);
            /* recalculate value at tree[i] */
        }
    }

    /* query type */ query(int l, int r, int i = 1) {
        push(i);
        if (l <= tree[i].a && r >= tree[i].b)
            return /* value at tree[i] */;
        if (l > tree[i].b || r < tree[i].a)
            return /* identity */;
        return query(l, r, 2*i) /* combined with */ query(l, r, 2*i+1);
    }
};