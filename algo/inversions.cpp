// Returns the number of pairs (i, j) such that i < j and A[i] > A[j].
// Runs in O(nlogn). Will not mutate the array.

template<typename it>
long long inversions(it first, it last) {

    using T = typename iterator_traits<it>::value_type;
    long long n = last-first, out = 0;
    vector<T> A(first, last), B(n);

    for (int w = 1; w < n; w <<= 1) {
        for (int k = 0; k < n;) {
            int s = k, j = k+w;
            for (int i = k; i < s+w && i < n; i++) {
                while (j < s+(w<<1) && j < n && A[j] < A[i])
                    B[k++] = A[j++];
                B[k++] = A[i], out += j-(s+w);
            }
            while (j < s+(w<<1) && j < n)
                B[k++] = A[j++];
        }
        swap(A, B);
    }
    return out;
}