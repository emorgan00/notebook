template<unsigned long long M>
struct polynomial : vector<modint<M>> {

    using T = modint<M>; using v = vector<T>;
    using v::vector;

    // access the coefficient of x^i
    T& operator[](const size_t i) {
        if (v::size() <= i) v::resize(i+1);
        return v::operator[](i);
    }

    // evaluate the polynomialnomial at x
    T operator()(const T x) const {
        T y(1), r(0);
        for (const T& a : *this) r += a*y, y *= x;
        return r;
    }

    polynomial substr(int l, int r) const {
        polynomial p(abs(r-l), 0);
        int l1 = max(0, min(int(v::size()), min(l, r)));
        int r1 = min(int(v::size()), max(l, r));
        copy(v::begin()+l1, v::begin()+r1, p.begin()+max(0, -min(l, r)));
        if (l > r) reverse(p.begin(), p.end()); return p;
    }

    polynomial& operator+=(const polynomial& p) {
        if (v::size() < p.size()) v::resize(p.size());
        auto it = v::begin(); for (const T& a : p) *(it++) += a;
        return *this;
    }
    polynomial& operator-=(const polynomial& p) { return *this += -p; }
    polynomial& operator*=(const T& x) { for (T& a : *this) a *= x; return *this; }
    polynomial& operator/=(const T& x) { *this *= 1/x; return *this; }
    polynomial operator+(const polynomial& p) const { return polynomial(*this) += p; }
    polynomial operator-(const polynomial& p) const { return polynomial(*this) -= p; }
    polynomial operator+() const { return polynomial(*this); }
    polynomial operator-() const { return polynomial(*this) *= -1; }
    polynomial operator*(const T& x) const { return polynomial(*this) *= x; }
    friend polynomial operator*(const T& x, const polynomial& p) { return p*x; }
    polynomial operator/(const T& x) const { return polynomial(*this) /= x; }

    // memoized roots of unity
    static array<vector<T>, 2>& compute_roots(int k = 21) {
        static array<vector<T>, 2> r;
        if (r[0].size() >= 1<<k) return r;
        T p = 2; while (p.pow(M>>1).v == 1) p += 1;
        r[0].resize(1<<k, 1), r[1].resize(1<<k, 1);
        for (int w = 0; w < k; w++) {
            int x = (1<<w)-1, t = (M-1)>>w;
            T g = p.pow(t), ig = p.pow(M-1-t);
            for (int i = 0; i < x; i++) {
                r[0][x+i+1] = g*r[0][x+i];
                r[1][x+i+1] = ig*r[1][x+i];
            }
        } return r;
    }

    // number theoretic transform in place, runs in O(nlogn)
    void ntt(bool inv = 0) {
        int n = v::size(); if (n == 1) return;
        auto& r = compute_roots()[inv];
        auto f = v::data();
        if (inv) {
            for (int i = 1; i < n; i <<= 1)
                for (int j = 0; j < n; j += i*2)
                    for (int k = 0; k < i; k++) {
                        f[i+j+k] *= r[i*2-1+k];
                        const T tmp = f[j+k]-f[i+j+k];
                        f[j+k] += f[i+j+k]; f[i+j+k] = tmp;
                    }
            const T ni = 1/T(n); for (int i = 0; i < n; i++) f[i] *= ni;
        } else
            for (int i = n>>1; i > 0; i >>= 1)
                for (int j = 0; j < n; j += i*2)
                    for (int k = 0; k < i; k++) {
                        const T tmp = f[j+k]-f[i+j+k];
                        f[j+k] += f[i+j+k]; f[i+j+k] = tmp*r[i*2-1+k];
                    }
    }

    polynomial& operator*=(polynomial p) {
        int m = v::size()+p.size()-1; int n = 1<<(32-__builtin_clz(m-1));
        v::resize(n), p.resize(n); ntt(), p.ntt();
        auto it = v::begin(); for (const T& a : p) *(it++) *= a;
        ntt(1), v::resize(m); return *this;
    }
    polynomial operator*(const polynomial& p) const { return polynomial(*this) *= p; }

    // inverse polynomialnomial mod x^n
    polynomial inv(size_t n) const { assert(v::data()[0] != 0);
        polynomial p = {1/v::data()[0]};
        for (size_t i = 1; i < n; i <<= 1)
            p -= (p*(p*substr(0, 2*i)).substr(i, 2*i)).substr(-i, i);
        p.resize(n); return p;
    }

    // square root polynomialnomial mod x^n
    polynomial sqrt(size_t n) const {
        polynomial p = {1};
        for (size_t i = 1; i < n; i <<= 1)
            p = (p.substr(0, 2*i)+*this*p.inv(n))/2;
        p.resize(n); return p;
    }

    // differentiation
    polynomial diff() const {
        polynomial p = substr(1, v::size()); T i = 0;
        for (auto& x : p) x *= i += 1; return p;
    }

    // integration with C = 0
    polynomial inte() const {
        polynomial p = substr(-1, v::size()); T i = -1;
        for (auto& x : p) x /= i += 1; return p;
    }

    // log(this) mod x^n
    polynomial log(size_t n) const { assert(v::data()[0] == 1);
        return (diff().substr(0, n)*inv(n)).inte().substr(0, n);
    }

    // e^this mod x^n
    polynomial exp(size_t n) const { assert(v::data()[0] == 0);
        polynomial p = {1};
        for (size_t i = 1; i < n; i <<= 1)
            p -= (p*(p.log(2*i).substr(i, 2*i)-substr(i, 2*i))).substr(-i, i);
        return p;
    }

    // exponentiation to the k power mod x^n
    polynomial pow(size_t n, size_t k) const {
        if (k < 0) return inv(n).pow(n, -k);
        if (k < 2) return k == 0 ? polynomial({1}) : polynomial(*this);
        if (k&1) return (*this*(this->pow(n, k-1))).substr(0, n);
        return (*this**this).substr(0, n).pow(n, k>>1);
    }
};

// 998244353