#include <bits/stdc++.h>
using namespace std;

// copy this to allow pairs to be used with unordered_set
// note, this hash is weak but works fine for random inputs

template<typename T1, typename T2>
struct std::hash<pair<T1, T2>> {
    size_t operator()(const pair<T1, T2>& p) const {
        size_t h1 = std::hash<T1>()(p.first);
        size_t h2 = std::hash<T2>()(p.second);
        return (h1 << 1) ^ h2;
    }
};

// hack-resistant hashmaps

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template<typename T>
struct safe_hash {
    size_t operator()(const T& x) const {
        static const size_t fixed = chrono::steady_clock::now().time_since_epoch().count();
        size_t h = std::hash<T>()(x);

        // splitmix64
        h += 0x9e3779b97f4a7c15 + fixed;
        h = (h ^ (h >> 30)) * 0xbf58476d1ce4e5b9;
        h = (h ^ (h >> 27)) * 0x94d049bb133111eb;
        return h ^ (h >> 31);
    }
};

template<typename T1, typename T2>
using safe_map = gp_hash_table<T1, T2, safe_hash<T1>>;