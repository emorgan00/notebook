#include <bits/stdc++.h>
using namespace std;

#define gcd __gcd
#define lcm(a, b) a*b/__gcd(a, b)

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

T modinv(T a, T m) {
    
}