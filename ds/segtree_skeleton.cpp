struct node {
    int a, b;
    /* value and update */
};

const int maxn = 200000;
node tree[4*maxn+5];
int n;

void build(vector</* value type */>& a) {
    n = 1<<int(ceil(log2(a.size())));
    for (int i = 2*n; i > 0; i--) {
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

void update(int i, int l, int r, /* update type */ x) {
    push(i);
    if (l > tree[i].b || r < tree[i].a)
        return;
    if (l <= tree[i].a && r >= tree[i].b) {
        /* add an update at tree[i] */
        push(i);
    } else {
        update(2*i, l, r, /* new update value */);
        update(2*i+1, l, r, /* new update value */);
        /* recalculate value at tree[i] */
    }
}

/* query type */ query(int i, int l, int r) {
    push(i);
    if (l <= tree[i].a && r >= tree[i].b)
        return /* value at tree[i] */;
    if (l > tree[i].b || r < tree[i].a)
        return /* identity */;
    return query(2*i, l, r) /* combined with */ query(2*i+1, l, r);
}