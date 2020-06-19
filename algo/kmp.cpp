#include <bits/stdc++.h>
using namespace std;

// Knuth-Morris-Pratt algorithm. Returns a list of all indices at which W appears in S.
// Runs in O(|S|+|W|) time.
template<typename it>
vector<int> kmp(it S_first, it S_last, it W_first, it W_last) {
    int n = S_last-S_first, m = W_last-W_first;
    vector<int> out, ptr(m+1);
    ptr[0] = -1;
    for (int i = 1, j = 0; i < m; i++, j++) {
        if (W_first[i] == W_first[j])
            ptr[i] = ptr[j];
        else {
            ptr[i] = j;
            do
                j = ptr[j];
            while (j >= 0 && W_first[i] != W_first[j]);
        }
        if (i == m-1) ptr[m] = j+1;
    }
    for (int i = 0, j = 0; i < n;) {
        if (W_first[j] == S_first[i]) {
            i++, j++;
            if (j == m) {
                out.push_back(i-j);
                j = ptr[j];
            }
        } else {
            j = ptr[j];
            if (j < 0) i++, j++;
        }
    }
    return out;
}