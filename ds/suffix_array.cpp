#include <bits/stdc++.h>
using namespace std;

struct suffixarray {

    // s = original string, a = suffix array
    // r = inverse suffix array (i.e. a[r[i]] = i)
    // lcp[i] = length of longest common prefix of a[i] and a[i+1]
    vector<int> s, a, r, lcp;

    // runs in O(nlogn) time.
    template<typename it>
    suffixarray(it first, it last) : s(first, last) {

        // construct a, r
        int n = s.size()+1, c = 1, j = 1, b;
        map<int, vector<int>> grp;
        vector<int> rc(n);
        r.resize(n); a.resize(n);
        for (int i = 0; i < n-1; i++)
            grp[s[i]].push_back(i);
        a[0] = n-1, r[n-1] = 0;
        for (auto& [_, v] : grp) {
            for (auto& i : v)
                r[i] = c, a[j++] = i;
            c++;
        }
        vector<vector<int>> cnt(n);
        for (int k = 1; k < 2*n; k <<= 1) {
            for (int i = 0; i < n; i++)
                cnt[r[b = (a[i]+2*n-k)%n]].push_back(b);
            c = -1, j = 0;
            for (auto& v : cnt) {
                for (int i = 0; i < v.size(); i++) {
                    if (i == 0 || r[(v[i]+k)%n] != r[(v[i-1]+k)%n]) c++;
                    rc[v[i]] = c, a[j++] = v[i];
                } v.clear();
            } swap(r, rc);
        }
        a.erase(a.begin()), r.erase(r.end()-1);

        // construct lcp
        lcp.resize(--n-1), c = 0;
        for (int i = 0; i < n; i++) {
            if (--r[i] == 0) continue;
            j = a[r[i]-1];
            while (max(i, j)+c < n && s[i+c] == s[j+c]) c++;
            lcp[r[i]-1] = c, c = max(0, c-1);
        }
    }

    suffixarray(string str) : suffixarray(str.begin(), str.end()) {}

    // returns a pair [l, r] such that all suffixes starting at
    // indices in the suffix array a[l..r] contain the input as a prefix,
    // runs in O(mlogn) time where m is the input size.
    template<typename it>
    pair<int, int> interval(it first, it last) const {
        auto cmp = [&](int p) {
            for (int i = 0; first+i != last; i++) {
                if (p+i >= s.size() || s[p+i] < first[i]) return -1;
                if (s[p+i] > first[i]) return 1;
            } return 0;
        };
        int m, l, x = 0, y = s.size();
        while (x < y)
            if (cmp(a[m = (x+y)/2]) == -1) x = m+1;
            else y = m;
        l = x, x = -1, y = s.size()-1;
        while (x < y)
            if (cmp(a[m = (x+y+1)/2]) == 1) y = m-1;
            else x = m;
        return {l, x};
    }

    pair<int, int> interval(string str) const {
        return interval(str.begin(), str.end());
    }
};