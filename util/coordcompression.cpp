#include <bits/stdc++.h>
using namespace std;

// Transform the contents of A into elements of [0..N],
// while preserving the ordering/equality relationship among indices into A.
// Runs in O(nlogn).

template<typename it>
void compress(it start, it end) {
    typedef typename remove_reference<decltype(*start)>::type T;
    map<T, vector<it>> m;
    for (it i = start; i != end; i++)
        m[*i].push_back(i);
    int t = 0;
    for (auto& [x, v] : m) {
        for (auto& i : v)
            *i = t;
        t++;
    }
}

template<typename it, typename cmp>
void compress(it start, it end, cmp ord) {
    typedef typename remove_reference<decltype(*start)>::type T;
    map<T, vector<it>, cmp> m(ord);
    for (it i = start; i != end; i++)
        m[*i].push_back(i);
    int t = 0;
    for (auto& [x, v] : m) {
        for (auto& i : v)
            *i = t;
        t++;
    }
}