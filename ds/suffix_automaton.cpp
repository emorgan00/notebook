#include <bits/stdc++.h>
using namespace std;

// suffix automaton on a string of <= N characters, alphabet of size K

template<int N>
struct automaton {

    int n = 1, l = 0;
    int p[N], len[N];
    map<int, int> adj[N]; // transitions of form {char, destination}
    bool t[N]; // indicates whether a state is terminal

    automaton() { p[0] = -1, len[0] = 0; }

    // returns the number of vertices in the automaton
    int size() { return n; }

    // append character c (in the range [0..K-1]) to the string,
    // runs in O(log(min(n, K))) amortized, where K is the alphabet size.
    void append(int c) {
        int r = n++, x = l, y, z;
        len[r] = len[l]+1, l = r;
        for (; x != -1 && !adj[x].count(c); x = p[x])
            adj[x][c] = r;
        if (x == -1) p[r] = 0;
        else if (len[y = adj[x][c]] == len[x]+1)
            p[r] = y;
        else {
            len[z = n++] = len[x]+1, adj[z] = adj[y];
            p[z] = p[y], p[r] = p[y] = z;
            for (; x != -1 && adj[x][c] == y; x = p[x])
                adj[x][c] = z;
        }
    }

    // refreshes the t array, must be called after building the graph,
    // runs in O(n).
    void refresh_t() {
        fill(t, t+n, 0);
        for (int x = l; x != -1; x = p[x])
            t[x] = 1;
    }
};