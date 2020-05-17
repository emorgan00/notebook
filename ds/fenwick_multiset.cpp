#include <bits/stdc++.h>
using namespace std;

// ordered statistic tree using fenwick tree.
// all operations take O(log(N)),
// where N is the limit on size of elements

template<int N>
struct fenwick_multiset {

    int s = 0, tree[N+1] = {};
    int size() { return s; }

    void insert(int x) {
        for (x++; x <= N; x += x & -x)
            tree[x]++;
        s++;
    }

    void remove(int x) {
        for (x++; x <= N; x += x & -x)
            tree[x]--;
        s--;
    }

    // returns the number of elements in
    // the set which are strictly lower than x
    int index(int x) {
        int i = 0;
        for (; x > 0; x -= x & -x)
            i += tree[x];
        return i;
    }

    // returns the x'th element of the set,
    // 0-based indexing
    int get(int x) {
        int i = 0;
        for (int m = 1<<(31-__builtin_clz(N)); m > 0; m >>= 1)
            if (i+m <= N && tree[i+m] <= x)
                x -= tree[i += m];
        return i;
    }
};

// see https://codeforces.com/blog/entry/61364