template<typename T, int H, int W>
struct matrix {

    T M[H][W];
    matrix(const T k = 0) { ident(k); }
    matrix(initializer_list<initializer_list<T>> v) : matrix() {
        for (int i = 0; i < v.size(); i++)
            copy(v.begin()[i].begin(), v.begin()[i].end(), M[i]);
    }

    T* operator[](const int i) { return M[i]; }
    const T* operator[](const int i) const { return M[i]; }

    void clear() { fill(&M[0][0], &M[0][0]+sizeof(M)/sizeof(T), 0); }
    void ident(const T k = 1) {
        clear(); for (int i = 0; i < min(H, W); i++) M[i][i] = k;
    }

    friend string to_string(const matrix& a) {
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

    matrix& operator*=(const T& r) {
        for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
            M[i][j] *= r;
        return *this;
    }
    matrix& operator/=(const T& r) {
        for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
            M[i][j] /= r;
        return *this;
    }
    matrix operator*(const T& r) const { return matrix(*this) *= r; }
    matrix operator/(const T& r) const { return matrix(*this) /= r; }
    friend matrix operator*(const T& r, const matrix& a) {
        return matrix(a) *= r;
    }

    matrix& operator+=(const matrix& a) {
        for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
            M[i][j] += a.M[i][j];
        return *this;
    }
    template<int C> matrix<T, H, C> operator*(const matrix<T, W, C>& b) {
        matrix<T, H, C> r(0);
        for (int i = 0; i < H; i++) for (int j = 0; j < C; j++)
            for (int k = 0; k < W; k++) r.M[i][j] += M[i][k]*b.M[k][j];
        return r;
    }

    matrix& operator*=(const matrix& b) { return *this = *this*b; }
    matrix operator+(const matrix& b) { return matrix(*this) += b; }
    matrix operator-(const matrix& b) { return matrix(*this) += -b; }
    matrix operator+() { return matrix(*this); }
    matrix operator-() { return matrix(*this) *= -1; }

    matrix transpose() const {
        matrix r(0);
        for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
            r.M[i][j] = M[j][i];
        return r;
    }

    // O(n^3logk) matrix exponentiation
    matrix pow(long long k) {
        matrix a(1), r(*this);
        for (int i = 1; i <= k; i <<= 1) {
            if (i&k) a *= r;
            r *= r;
        }
        return a;
    }

    // O(n^3) matrix determinant, uses operator/
    T det() const {
        matrix r(*this); T d = 1;
        for (int i = 0; i < H; i++) {
            if (r.M[i][i] == 0) for (int j = i+1; j < H; j++) if (r.M[j][i] != 0)
                { swap(r.M[i], r.M[j]); d = 0-d; break; }
            d *= r.M[i][i]; if (r.M[i][i] == 0) return 0;
            for (int j = i+1; j < H; j++) { T c = r.M[j][i]/r.M[i][i];
                for (int k = i; k < H; k++) r.M[j][k] -= r.M[i][k]*c;
        } } return d;
    }
    
    // O(n^3) matrix inversion, uses operator/, undefined behavior if det(*this) == 0
    matrix inv() const {
        matrix b(1), r(*this);
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