#include <bits/stdc++.h>
using namespace std;

// note: this fenwick tree uses 0-based indexing.

template<typename T>
struct fenwick {

    int length;
    vector<T> tree;

    fenwick(int size) {
        length = size+1;
        tree.assign(length+1, 0);
    }

    fenwick(vector<T>& v) {
        length = v.size()+1;
        tree.assign(length+1, 0);
        for (int i = 0; i < v.size(); i++)
            update(i, v[i]);
    }

    // insert val at index i
    void update(int i, T val) {
        i++;
        while (i < length) {
            tree[i] += val;
            i += i & -i;
        }
    }

    // inclusive of i
    T prefix(int i) {
        i++;
        T out = 0;
        while (i > 0) {
            out += tree[i];
            i -= i & -i;
        }
        return out;
    }

    // sum over a..b, inclusive
    T query(int a, int b) {
        return prefix(b)-prefix(a-1);
    }
};