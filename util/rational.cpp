#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long

// numerator and denominator should not exceed 10^9.

struct rational {
	bool neg;
	ull p, q; // numerator, denominator

	rational() {
		neg = 0; p = 0; q = 1;
	}

	rational(bool s, ull n, ull d) {
		neg = s; p = n; q = d;
		reduce();
	}

	rational(int n, int d) {
		neg = (n >= 0) != (d >= 0);
		p = (ull)abs(n); q = (ull)abs(d);
		reduce();
	}

	rational(int n) {
		neg = n < 0;
		p = (ull)abs(n); q = 1;
	}

	void reduce() {
		int g = __gcd(p, q);
		p /= g; q /= g;
	}

	template<typename T>
	operator T() { return T(p)/q * (neg ? -1 : 1); }
};

// to string

string to_string(rational r) {
	return (r.neg ? "-" : "")+to_string(r.p)+(r.q == 1 ? "" : "/"+to_string(r.q));
}

ostream& operator<<(ostream& out, rational r) {
	out << to_string(r);
	return out;
}

// comparison

inline bool operator>(const rational a, const rational b) {
	if (a.neg != b.neg)
		return b.neg;
	return (a.p*b.q > b.p*a.q) != a.neg;
}

inline bool operator<(const rational a, const rational b) {
	return b > a;
}

inline bool operator==(const rational a, const rational b) {
	return a.neg == b.neg && a.p == b.p && a.q == b.q;
}

inline bool operator>=(const rational a, const rational b) {
	return a > b || a == b;
}

inline bool operator<=(const rational a, const rational b) {
	return b > a || a == b;
}

// arithmetic

inline rational operator+(const rational a, const rational b) {
	if (a.neg == b.neg)
		return rational(a.neg, a.p*b.q + b.p*a.q, a.q*b.q);
	else {
		ull an = a.p*b.q, bn = b.p*a.q;
		if (an > bn)
			return rational(a.neg, an-bn, a.q*b.q);
		return rational(b.neg, bn-an, a.q*b.q);
	}
}

inline rational operator-(const rational a, const rational b) {
	if (a.neg != b.neg)
		return rational(a.neg, a.p*b.q + b.p*a.q, a.q*b.q);
	else {
		ull an = a.p*b.q, bn = b.p*a.q;
		if (an > bn)
			return rational(a.neg, an-bn, a.q*b.q);
		return rational(!a.neg, bn-an, a.q*b.q);
	}
}

inline rational operator*(const rational a, const rational b) {
	return rational(a.neg != b.neg, a.p*b.p, a.q*b.q);
}

inline rational operator/(const rational a, const rational b) {
	return rational(a.neg != b.neg, a.p*b.q, a.q*b.p);
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