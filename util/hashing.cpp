#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct splitmix64 {
    size_t operator()(long long x) const {
        static const size_t fixed = chrono::steady_clock::now().time_since_epoch().count();
        x += 0x9e3779b97f4a7c15 + fixed;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
};

// gp_hash_table<A, B>;

// if A is integral, better to use this option:
// gp_gash_table<long long, B, splitmix64>