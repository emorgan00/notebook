#include <bits/stdc++.h>
using namespace std;

// returns (b^r)%m, runs in O(logr) time.
template<typename T>
T powmod(T b, T r, T m) {
    T out = 1;
    for (T t = 1; t <= r; t <<= 1) {
        if (r&t) out = (out*b)%m;
        b = (b*b)%m;
    }
    return out;
}

// returns a unique number b s.t. ab = 1 mod m in O(logm) time.
template<typename T>
T inv(T a, T m) {
    T r = 1, k = m-2;
    while (k) {
        if (k&1) r = (r*a)%m;
        a = (a*a)%m;
        k >>= 1;
    }
    return r%m;
}

// returns (n choose k) mod m in O(klogm) time.
template<typename T>
T choose(T n, T k, T m) {
    T out = 1, r = n, d = 1;
    for (int i = 0; i < k; i++) {
        out = (out*r)%m;
        out = (out*inv(d, m))%m;
        r--; d++;
    }
    return out;
}