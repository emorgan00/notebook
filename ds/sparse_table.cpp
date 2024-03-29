template<typename it, typename bin_op>
struct sparse_table {

    using T = typename iterator_traits<it>::value_type;
    vector<vector<T>> t; bin_op f;

    void assign(it first, it last) {
        int n = distance(first, last);
        t.assign(32-__builtin_clz(n), vector<T>(n));
        t[0].assign(first, last);
        for (int i = 1; i < t.size(); i++)
            for (int j = 0; j < n-(1<<i)+1; j++)
                t[i][j] = f(t[i-1][j], t[i-1][j+(1<<(i-1))]);
    }

    sparse_table(bin_op op) : f(op) {}
    sparse_table(it first, it last, bin_op op) : f(op) {
        assign(first, last);
    }

    // returns f(a[l..r]) in O(1) time
    T operator()(int l, int r) {
        int h = floor(log2(r-l+1));
        return f(t[h][l], t[h][r-(1<<h)+1]);
    }
};