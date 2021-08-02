// Transform the contents of [first, last) into elements of [0..N],
// while preserving the relative ordering/equality of the data.
// Runs in O(nlogn).

template<typename it1, typename it2, typename cmp = less<>>
void compress(it1 first, it1 last, it2 result, cmp ord = less<>()) {
    using T = typename iterator_traits<it>::value_type;
    map<T, vector<it2>, cmp> m(ord);
    for (it1 i = first; i != last; i++)
        m[*i].push_back(result+(i-first));
    int t = 0;
    for (auto& [_, v] : m) {
        for (auto& i : v) *i = t;
        t++;
    }
}