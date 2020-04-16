#include <bits/stdc++.h>
using namespace std;

#define gcd __gcd
#define lcm(a, b) a*b/__gcd(a, b)

// returns a vector of length n, containing 1 if a number is prime, else 0.
// runs in O(nlogn) time.
template<typename T>
vector<bool> primesieve(T n) {
    vector<bool> sieve(n, 1);
    for (T i = 2; i < n; i++)
        if (sieve[i])
            for (T j = 2*i; j < n; j += i)
                sieve[j] = 0;
    return sieve;
}


// returns a sorted list of all primes less than or equal to n.
// runs in O(nlogn) time.
template<typename T>
vector<T> primesupto(T n) {
    vector<bool> sieve(n+1, 1);
    for (T i = 2; i <= n; i++)
        if (sieve[i])
            for (T j = 2*i; j <= n; j += i)
                sieve[j] = 0;
    vector<T> out;
    for (T i = 2; i <= n; i++)
        if (sieve[i])
            out.push_back(i);
    return out;
}

// returns a sorted list of all prime factors of n in O(sqrt(n)) time.
template<typename T>
vector<T> primefactors(T n) {
    vector<T> out;
    for (T i = 2; i <= n; i++) {
        if (i >= (T)(sqrt(n))+1)
            i = n;
        if (n%i == 0) {
            out.push_back(i);
            n /= i;
            i--;
        }
    }
    return out;
}

// returns a sorted list of all unique prime factors of n in O(sqrt(n)) time.
template<typename T>
vector<T> uniqueprimefactors(T n) {
    vector<T> out;
    for (T i = 2; i <= n; i++) {
        if (i >= (T)(sqrt(n))+1)
            i = n;
        if (n%i == 0) {
            out.push_back(i);
            while (n%i == 0) n /= i;
        }
    }
    return out;
}

// returns a sorted list of all divisors (>1) of n in O(sqrt(n)) time.
template<typename T>
vector<T> divisors(T n) {
    vector<T> s, e;
    for (T i = 2; i <= (T)(sqrt(n)); i++)
        if (n%i == 0) {
            s.push_back(i);
            if (i*i != n) e.push_back(n/i);
        }
    for (int i = e.size()-1; i >= 0; i--)
        s.push_back(e[i]);
    return s;
}

// checks if a number is prime in O(sqrt(n)) time.
template<typename T>
bool isprime(T n) {
    for (T i = 2; i <= (T)(sqrt(n)); i++)
        if (n%i == 0)
            return false;
    return true;
}