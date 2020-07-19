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
    T r = 1;
    for (T k = m-2; k; k >>= 1) {
        if (k&1) r = (r*a)%m;
        a = (a*a)%m;
    }
    return r%m;
}

// based on something from KACTL, requires 64bit C++
struct fastmod {
    __int128_t b, m;
    fastmod(int64_t x) : b(x), m(((__int128_t)1<<64) / x) {}
    int64_t reduce(int64_t x) {
        __int128_t q = (m*x)>>64;
        __int128_t r = x - q*b;
        return r >= b ? r - b : r;
    }
};