#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long

#define MOD 998244353

struct rational {
    ull p, q; // numerator, denominator

    rational() {
        p = 0; q = 1;
    }

    rational(ull n, ull d) {
        p = n; q = d;
    }

    rational(int n) {
        p = n; q = 1;
    }

    void reduce() {
        int g = __gcd(p, q);
        p /= g; q /= g;
    }

    // returns a unique integer x such that xq = p (mod MOD)
    ull mod() {
        ull r = 1, t = q, k = MOD-2;
        while (k) {
            if (k&1) r = (r*t)%MOD;
            t = (t*t)%MOD;
            k >>= 1;
        }
        return (p*r)%MOD;
    }

    template<typename T>
    operator T() { return T(p)/q; }
};

// to string

string to_string(rational r) {
    r.reduce();
    return to_string(r.p)+(r.q == 1 ? "" : "/"+to_string(r.q));
}

ostream& operator<<(ostream& out, rational r) {
    out << to_string(r);
    return out;
}

inline bool operator==(const rational a, const rational b) {
    return a.p == b.p && a.q == b.q;
}

// arithmetic

inline rational operator+(const rational a, const rational b) {
    ull an = (a.p*b.q)%MOD, bn = (b.p*a.q)%MOD;
    return rational((an+bn)%MOD, (a.q*b.q)%MOD);
}

inline rational operator-(const rational a, const rational b) {
    ull an = (a.p*b.q)%MOD, bn = (b.p*a.q)%MOD;
    return rational((an-bn+MOD)%MOD, (a.q*b.q)%MOD);
}

inline rational operator*(const rational a, const rational b) {
    return rational((a.p*b.p)%MOD, (a.q*b.q)%MOD);
}

inline rational operator/(const rational a, const rational b) {
    return rational((a.p*b.q)%MOD, (a.q*b.p)%MOD);
}

template<typename T>
inline rational operator+(const rational a, const T b) { return a+rational(b); };
template<typename T>
inline rational operator+(const T a, const rational b) { return rational(a)+b; };
template<typename T>
inline rational operator-(const rational a, const T b) { return a-rational(b); };
template<typename T>
inline rational operator-(const T a, const rational b) { return rational(a)-b; };
template<typename T>
inline rational operator*(const rational a, const T b) { return a*rational(b); };
template<typename T>
inline rational operator*(const T a, const rational b) { return rational(a)*b; };
template<typename T>
inline rational operator/(const rational a, const T b) { return a/rational(b); };
template<typename T>
inline rational operator/(const T a, const rational b) { return rational(a)/b; };