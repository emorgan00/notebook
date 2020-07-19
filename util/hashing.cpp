// hack-resistant hashmaps

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct safe_hash {
    size_t operator()(long long x) const {
        static const size_t fixed = chrono::steady_clock::now().time_since_epoch().count();

        // splitmix64
        x += 0x9e3779b97f4a7c15 + fixed;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
};

// map from long long to T
template<typename T>
using safe_map = gp_hash_table<long long, T, safe_hash>;