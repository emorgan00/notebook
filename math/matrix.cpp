template<typename T, int H, int W>
struct matrix {

    T M[H][W];
    matrix() { clear(); }
    matrix(bool b) { b ? ident() : clear(); }

    matrix(initializer_list<initializer_list<T>> v) : matrix() {
        for (int i = 0; i < v.size(); i++)
            copy(v.begin()[i].begin(), v.begin()[i].end(), M[i]);
    }

    T* operator[](const int i) { return M[i]; }
    const T* operator[](const int i) const { return M[i]; }

    void clear() { fill(&M[0][0], &M[0][0]+sizeof(M)/sizeof(T), 0); }
    void ident() { assert(H == W), clear();
        for (int i = 0; i < W; i++) M[i][i] = 1;
    }

    friend string to_string(const matrix<T, H, W>& a) {
        string s = "";
        for (int i = 0; i < H; i++) {
            s += (i == 0 ? "[" : ", ");
            for (int j = 0; j < W; j++)
                s += (j == 0 ? "[" : ", ")+to_string(a.M[i][j]);
            s += "]";
        } return s+"]";
    }
    friend ostream& operator<<(ostream& o, const matrix<T, H, W>& a) {
        return o << to_string(a);
    }

    matrix<T, H, W>& operator*=(const T& r) {
        for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
            M[i][j] *= r;
        return *this;
    }
    friend matrix<T, H, W> operator*(const matrix<T, H, W>& a, const T& r) {
        return matrix(a) *= r;
    }
    friend matrix<T, H, W> operator*(const T& r, const matrix<T, H, W>& a) {
        return matrix(a) *= r;
    }

    matrix<T, H, W>& operator+=(const matrix<T, H, W>& a) {
        for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
            M[i][j] += a.M[i][j];
        return *this;
    }
    friend matrix<T, H, W> operator+(const matrix<T, H, W>& a, const matrix<T, H, W>& b) {
        return matrix(a) += b;
    }
    template<int C>
    friend matrix<T, H, C> operator*(const matrix<T, H, W>& a, const matrix<T, W, C>& b) {
        matrix<T, H, C> r(0);
        for (int i = 0; i < H; i++) for (int j = 0; j < C; j++) for (int k = 0; k < W; k++)
            r.M[i][j] += a.M[i][k]*b.M[k][j];
        return r;
    }

    // O(n^3logk) matrix exponentiation
    matrix<T, H, W> operator^(long long k) { assert(H == W);
        matrix<T, H, W> a(*this), r(1);
        if (k < 0) a = inv(a), k = -k;
        for (long long i = 1; i <= k; i <<= 1, a = a*a) if (i&k) r = r*a;
        return r;
    }

    // O(n^3) matrix determinant, uses operator/
    friend T det(const matrix<T, H, W>& a) { assert(H == W);
        matrix<T, H, W> r(a); T d = 1;
        for (int i = 0; i < H; i++) {
            if (r.M[i][i] == 0) for (int j = i+1; j < H; j++) if (r.M[j][i] != 0)
                { swap(r.M[i], r.M[j]); d = -d; break; }
            d *= r.M[i][i]; if (r.M[i][i] == 0) return 0;
            for (int j = i+1; j < H; j++) { T c = r.M[j][i]/r.M[i][i];
                for (int k = i; k < H; k++) r.M[j][k] -= r.M[i][k]*c;
        } } return d;
    }
    // O(n^3) matrix inversion, uses operator/, undefined behavior if det(a) == 0
    friend matrix<T, H, W> inv(const matrix<T, H, W>& a) { assert(H == W);
        matrix<T, H, W> b(1), r(a);
        for (int i = 0; i < H; i++) {
            if (r.M[i][i] == 0) for (int j = i+1; j < H; j++) if (r.M[j][i] != 0)
                { swap(b.M[i], b.M[j]), swap(r.M[i], r.M[j]); break; }
            for (int j = i+1; j < H; j++) { T c = r.M[j][i]/r.M[i][i];
                for (int k = 0; k < H; k++)
                    b.M[j][k] -= b.M[i][k]*c, r.M[j][k] -= r.M[i][k]*c;
        } }
        for (int i = H-1; i >= 0; i--) { T c = 1/r.M[i][i];
            for (int j = 0; j < H; j++) b.M[i][j] *= c, r.M[i][j] *= c;
            for (int j = 0; j < i; j++) { c = r.M[j][i];
                for (int k = 0; k < H; k++) b.M[j][k] -= b.M[i][k]*c;
        } } return b;
    }
};