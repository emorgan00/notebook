#include <bits/stdc++.h>
using namespace std;

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
    void ident() {
        assert(H == W), clear();
        for (int i = 0; i < W; i++) M[i][i] = 1;
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
    friend matrix<T, H, W> operator*(const matrix<T, H, C>& a, const matrix<T, C, W>& b) {
        matrix<T, H, W> r(0);
        for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) for (int k = 0; k < C; k++)
            r.M[i][j] += a.M[i][k]*b.M[k][j];
        return r;
    }

    friend string to_string(const matrix<T, H, W>& a) {
        string out = "";
        for (int i = 0; i < H; i++) {
            out += (i == 0 ? "[" : ", ");
            for (int j = 0; j < W; j++)
                out += (j == 0 ? "[" : ", ")+to_string(a.M[i][j]);
            out += "]";
        }
        return out+"]";
    }
    friend ostream& operator<<(ostream& out, const matrix<T, H, W>& a) {
        return out << to_string(a);
    }
};