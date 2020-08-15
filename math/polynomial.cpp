template<unsigned long long M>
struct poly : vector<modint<M>> {

    using T = modint<M>; using v = vector<T>;
    using v::vector;

    // access the coefficient of x^i
    T& operator[](const size_t i) {
        if (v::size() <= i) v::resize(i+1);
        return v::operator[](i);
    }

    // evaluate the polynomial at x
    T operator()(const T x) const {
        T y(1), r(0);
        for (const T& a : *this) r += a*y, y *= x;
        return r;
    }

    poly& operator+=(const poly& p) {
        if (v::size() < p.size()) v::resize(p.size());
        auto it = v::begin(); for (const T& a : p) *(it++) += a; return *this;
    }
    poly& operator-=(const poly& p) { return *this += -p; }
    poly& operator*=(const T& x) { for (T& a : *this) a *= x; return *this; }
    poly operator+(const poly& p) const { return poly(*this) += p; }
    poly operator-(const poly& p) const { return poly(*this) -= p; }
    poly operator+() const { return poly(*this); }
    poly operator-() const { return poly(*this) *= -1; }
    poly operator*(const T& x) const { return poly(*this) *= x; }
    friend poly operator*(const T& x, const poly& p) { return p*x; }

    // multiply by x^-i, discarding too small terms
    poly& operator>>=(const size_t i) {
        v::erase(v::begin(), v::size() < i ? v::end() : v::begin()+i); return *this;
    }
    // multiply by x^i
    poly& operator<<=(const size_t i) {
        v::insert(v::begin(), i, 0); return *this;
    }
    poly operator>>(const size_t i) const { return poly(*this) >>= i; }
    poly operator<<(const size_t i) const { return poly(*this) <<= i; }

    // memoized roots of unity, source: Um_nik
    static array<vector<T>, 2>& compute_roots(int k = 21) {
        static array<vector<T>, 2> r;
        if (r[0].size() >= 1<<k) return r;
        T p = 2; while (p.exp(M>>1).v == 1) p += 1;
        r[0].resize(1<<k, 1), r[1].resize(1<<k, 1);
        for (int w = 0; w < k; w++) {
            int x = (1<<w)-1, t = (M-1)>>w;
            T g = p.exp(t), ig = p.exp(M-1-t);
            for (int i = 0; i < x; i++) {
                r[0][x+i+1] = g*r[0][x+i];
                r[1][x+i+1] = ig*r[1][x+i];
            }
        } return r;
    }

    // number theoretic transform in place, runs in O(nlogn), source: Um_nik
    void ntt(bool inv = 0) {
        int n = v::size(); if (n == 1) return;
        auto& r = compute_roots()[inv];
        auto f = this->data();
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

    poly& operator*=(poly p) {
        int m = v::size()+p.size()-1; int n = 1<<(32-__builtin_clz(m-1));
        v::resize(n), p.resize(n); ntt(), p.ntt();
        auto it = v::begin(); for (const T& a : p) *(it++) *= a;
        ntt(1), v::resize(m); return *this;
    }
    poly operator*(const poly& p) const { return poly(*this) *= p; }

    // O(nlognlogk) exponentation
    poly exp(const ll k) const { assert(k >= 0);
        if (k < 2) return k == 0 ? poly({1}) : poly(*this);
        return k&1 ? *this*(this->exp(k-1)) : (*this**this).exp(k>>1);
    }
};