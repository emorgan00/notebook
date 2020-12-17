// Returns a vector V where V[i] = minimum of the array from i to i+width-1.
// Runs in O(n) time.

template<typename it1, typename it2>
void fixedrangermq(it1 first, it1 last, it2 result, int width) {
    int n = distance(first, last);
    vector p(first, last), s(first, last);
    for (int i = n-1; i >= 0; i--)
        if (i%width != width-1 && i != n-1) s[i] = min(s[i], s[i+1]);
    for (int i = 0; i < n; i++)
        if (i%width) p[i] = min(p[i], p[i-1]);
    for (int i = 0; i <= n-width; i++, result++)
        *result = min(s[i], p[i+width-1]);
}