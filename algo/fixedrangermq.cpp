#include <bits/stdc++.h>
using namespace std;

// Returns a vector V where V[i] = minimum of the array from i to i+width-1.
// Runs in O(n) time.

template<typename T>
vector<T> fixedrangermq(vector<T>& A, int width) {

    int n = A.size();
    vector<T> prefix(n, 0), suffix(n, 0);
    for (int i = 0; i < n; i++) {
        prefix[i] = A[i];
        if (i%width != 0)
            prefix[i] = min(prefix[i], prefix[i-1]);
    }
    for (int i = n-1; i >= 0; i--) {
        suffix[i] = A[i];
        if (i%width != width-1 && i != n-1)
            suffix[i] = min(suffix[i], suffix[i+1]);
    }
    vector<T> out(n-width+1);
    for (int i = 0; i <= n-width; i++)
        out[i] = min(suffix[i], prefix[i+width-1]);
    return out;
}