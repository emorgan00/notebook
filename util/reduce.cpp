// utils for reducing vectors under an operation

template<typename T> inline T sum(vector<T> X)
{ T r = 0; for (const auto& x : X) r += x; return r; }

template<typename T> inline T min(vector<T> X)
{ T r = *X.begin(); for (const auto& x : X) r = min(r, x); return r; }

template<typename T> inline T max(vector<T> X)
{ T r = *X.begin(); for (const auto& x : X) r = max(r, x); return r; }