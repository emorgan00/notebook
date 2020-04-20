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

// returns a unique number b s.t. ab = 1 mod m
template<typename T>
T modinv(T a, T m) {
    T r = 1, k = m-2;
    while (k) {
        if (k&1) r = (r*a)%m;
        a = (a*a)%m;
        k >>= 1;
    }
    return r%m;
}