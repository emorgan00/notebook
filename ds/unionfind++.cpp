#include <bits/stdc++.h>
using namespace std;

// provides all the utility of normal unionfind, and also includes
// size(i): returns the size of the component which i is in
struct unionfind {

    int length;
    vector<int> parent, sz;

    unionfind(int s) {
        length = s;
        parent = vector<int>(s);
        sz = vector<int>(s, 1);
        for (int i = 0; i < s; i++)
            parent[i] = i;
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
        sz[a] += sz[b];
    }

    // returns true if a and b are in the same set.
    inline bool query(int a, int b) {
        return rep(a) == rep(b);
    }

    inline int size(int x) {
        return sz[rep(x)];
    }
};