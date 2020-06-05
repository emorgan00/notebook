#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct pt {
    T x, y;
};

template<typename T>
T dot(pt<T> a, pt<T> b) {
	return a.x*b.x + a.y*b.y;
}

// returns the point of intersection of lines AB and CD.
// only works for floats/doubles
template<typename T>
pt<T> intersection(pt<T> a, pt<T> b, pt<T> c, pt<T> d) {
    T t = ((a.x-c.x)*(c.y-d.y)-(a.y-c.y)*(c.x-d.x))/((a.x-b.x)*(c.y-d.y)-(a.y-b.y)*(c.x-d.x));
    return {a.x + t*(b.x-a.x), a.y + t*(b.y-a.y)};
}