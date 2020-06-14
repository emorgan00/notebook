#include <bits/stdc++.h>
using namespace std;

// Transform the contents of A into elements of [0..N],
// while preserving the ordering/equality relationship among indices into A.
// Runs in O(nlogn).

template<typename it1, typename it2>
void compress(it1 first, it1 last, it2 result) {
    typedef typename remove_reference<decltype(*first)>::type T;
    map<T, vector<it2>> m;
    for (it1 i = first; i != last; i++)
        m[*i].push_back(result+(i-first));
    int t = 0;
    for (auto& [x, v] : m) {
        for (auto& i : v)
            *i = t;
        t++;
    }
}

template<typename it1, typename it2, typename cmp>
void compress(it1 first, it1 last, it2 result, cmp ord) {
    typedef typename remove_reference<decltype(*first)>::type T;
    map<T, vector<it2>, cmp> m(ord);
    for (it1 i = first; i != last; i++)
        m[*i].push_back(result+(i-first));
    int t = 0;
    for (auto& [x, v] : m) {
        for (auto& i : v)
            *i = t;
        t++;
    }
}