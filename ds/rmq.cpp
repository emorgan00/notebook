// Preferable to generalized range associative-function query due to a much smaller constant factor.

template<typename T>
struct rmq {

    vector<vector<T>> tree;

    // runs in O(nlogn).
    rmq(vector<T> data = {}) {
        int n = data.size();
        int h = n == 0 ? 0 : ceil(log2(n));
        tree.assign(h+1, vector<T>(n));
        tree[0] = data;
        for (int i = 1; i <= h; i++)
            for (int j = 0; j < n-(1<<i)+1; j++)
                tree[i][j] = min(tree[i-1][j], tree[i-1][j+(1<<(i-1))]);
    }

    // returns the minimum of the array on the interval [a..b] in O(1) time.
    T query(int a, int b) {
        int n = floor(log2(b-a+1));
        return min(tree[n][a], tree[n][b-(1<<n)+1]);
    }
};
