#include <bits/stdc++.h>
using namespace std;

// call randint() for a random integer, good for hashing
mt19937 randint(chrono::steady_clock::now().time_since_epoch().count());

// returns a random integer over [a, b] inclusive
inline int uniform_randint(const int a, const int b) {
    return uniform_int_distribution<int>(a, b)(randint);
}

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