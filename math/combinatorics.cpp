// returns b^r mod m, runs in O(logr) time.
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
    T r = 1;
    for (T k = m-2; k; k >>= 1) {
        if (k&1) r = (r*a)%m;
        a = (a*a)%m;
    }
    return r%m;
}

// returns (n choose k) in O(k) time.
template<typename T>
T choose(T n, T k) {
    if (k < 0 || k > n) return 0;
    T a = 1, b = 1, r = n;
    for (T d = 1; d <= min(k, n-k); d++, r--)
        a *= r, b *= d;
    return a/b;
}

// returns (n choose k) mod m in O(k+logm) time.
template<typename T>
T choosemod(T n, T k, T m) {
    if (k < 0 || k > n) return 0;
    T a = 1, b = 1, r = n;
    for (T d = 1; d <= min(k, n-k); d++, r--)
        a = (a*r)%m, b = (b*d)%m;
    return (a*inv(b, m))%m;
}