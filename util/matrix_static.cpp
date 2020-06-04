#include <bits/stdc++.h>
using namespace std;

template<typename T, int H, int W>
struct matrix {

    T M[H][W];

    matrix() {
        clear();
    }

    inline int width() const {
        return W;
    }
    inline int height() const {
        return H;
    }

    // overloaded 2D indexing
    inline T* operator[](const int i) {
        return M[i];
    }
    inline const T* operator[](const int i) const {
        return M[i];
    }

    // reset this matrix to the ZERO MATRIX
    inline void clear() {
        std::fill(&M[0][0], &M[0][0] + sizeof(M)/sizeof(T), 0.0);
    }

    // reset this matrix to the IDENTITY MATRIX
    inline void ident() {
        static_assert(H == W, "A matrix must be square to be reset.");
        std::fill(&M[0][0], &M[0][0] + sizeof(M)/sizeof(T), 0.0);
        for (int i = 0; i < W; i++)
            M[i][i] = 1.0;
    }

    // equivalent to this = A+this (note that A must be H by W)
    void add(const matrix<T, H, W>& A) {
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                M[i][j] += A.M[i][j];
    }

    // equivalent to this = A*this (note that A must be H by H)
    void multiply_left(const matrix<T, H, H>& A) {
        int temp[H];

        for (int j = 0; j < W; j++) {
            std::fill(temp, temp+H, 0.0);
            for (int i = 0; i < H; i++)
                for (int k = 0; k < H; k++)
                    temp[i] += A.M[i][k]*M[k][j];
            for (int i = 0; i < H; i++)
                M[i][j] = temp[i];
        }
    }

    // equivalent to this = this*A (note that A must be W by W)
    void multiply_right(const matrix<T, W, W>& A) {
        int temp[W];

        for (int i = 0; i < H; i++) {
            std::fill(temp, temp+W, 0.0);
            for (int j = 0; j < W; j++)
                for (int k = 0; k < W; k++)
                    temp[j] += M[i][k]*A.M[k][j];
            for (int j = 0; j < W; j++)
                M[i][j] = temp[j];
        }
    }
};

// to_string

template<typename T, int h, int w>
string to_string(const matrix<T, h, w>& A) {
    string out = "";
    for (int i = 0; i < h; i++) {
        out += (i == 0 ? "[" : ", ");
        for (int j = 0; j < w; j++) {
            out += (j == 0 ? "[" : ", ");
            out += to_string(A[i][j]).substr(0, 6);
        }
        out += "]";
    }
    out += "]";
    return out;
}

template<typename T, int h, int w>
inline ostream& operator<<(ostream& out, const matrix<T, h, w>& a) {
    out << to_string(a);
    return out;
}

// matrix arithmetic

template<typename T, int ah, int aw, int bh, int bw>
matrix<T, ah, aw> operator+(const matrix<T, ah, aw>& A, const matrix<T, bh, bw>& B) {

    static_assert(aw == bw && ah == bh, "A and B must have the same dimensions.");
    matrix<T, ah, aw> R;

    for (int i = 0; i < ah; i++)
        for (int j = 0; j < bw; j++)
            R.M[i][j] = A.M[i][j]+B.M[i][j];

    return R;
}

template<typename T, int ah, int aw, int bh, int bw>
matrix<T, ah, bw> operator*(const matrix<T, ah, aw>& A, const matrix<T, bh, bw>& B) {

    static_assert(aw == bh, "A.width() must equal B.height().");
    matrix<T, ah, bw> R;
    R.clear();

    for (int i = 0; i < ah; i++)
        for (int j = 0; j < bw; j++)
            for (int k = 0; k < aw; k++)
                R.M[i][j] += A.M[i][k]*B.M[k][j];

    return R;
}

template<typename T, int ah, int aw, int bh, int bw>
inline void operator+=(matrix<T, ah, aw>& A, const matrix<T, bh, bw>& B) {
    static_assert(aw == bw && ah == bh, "A and B must have the same dimensions.");
    A.add(B);
}

// zero matrix (example use: auto M = zero<int, 5, 5>();)

template<typename T, int h, int w>
inline constexpr matrix<T, h, w> zero() {
    matrix<T, h, w> M;
    M.clear();
    return M;
}

// identity matrix (example use: auto M = identity<int, 5, 5>();)

template<typename T, int h, int w>
inline constexpr matrix<T, h, w> identity() {
    matrix<T, h, w> M;
    M.ident();
    return M;
}