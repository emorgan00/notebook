// given an array a of length n, returns an array b of length n-k+1
// such that b[i] = op(a[i], a[i+1], ..., a[i+k-1])
template<typename it1, typename it2, typename bin_op>
void sliding_window_fold(it1 first, it1 last, it2 result, int width, bin_op op) {
    int n = distance(first, last);
    vector p(first, last), s(first, last);
    for (int i = n-1; i >= 0; i--)
        if (i%width != width-1 && i != n-1) s[i] = op(s[i], s[i+1]);
    for (int i = 0; i < n; i++)
        if (i%width) p[i] = op(p[i], p[i-1]);
    for (int i = 0; i <= n-width; i++, result++)
        *result = i%width ? op(s[i], p[i+width-1]) : s[i];
}

// given an array a of length n, returns an array b of length n+k-1
// such that b[i] = op(a[i], a[i+1], ..., a[i+k-1]), not including invalid indices
template<typename it1, typename it2, typename bin_op>
void sliding_window_fold2(it1 first, it1 last, it2 result, int width, bin_op op) {
    int n = distance(first, last);
    vector p(first, last), s(first, last);
    for (int i = n-1; i >= 0; i--)
        if (i%width != width-1 && i != n-1) s[i] = op(s[i], s[i+1]);
    for (int i = 0; i < n; i++)
        if (i%width) p[i] = op(p[i], p[i-1]);
    for (int i = 0; i < width-1; i++, result++)
        *result = p[i];
    for (int i = 0; i <= n-width; i++, result++)
        *result = i%width ? op(s[i], p[i+width-1]) : s[i];
    int b = (n/width)*width;
    for (int i = n-width+1; i < n; i++, result++)
        *result = n%width && i < b ? op(s[i], p[n-1]) : s[i];
}