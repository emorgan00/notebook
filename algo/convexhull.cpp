// see https://cp-algorithms.com/geometry/grahams-scan-convex-hull.html
// (basically copied from there, this version works with integers)
// requires math/geometry.cpp

// returns the convex hull sorted in CCW order
template<typename T>
vector<point<T>> convexhull(vector<point<T>> v) {
    auto it = min_element(v.begin(), v.end());
    point<T> r = *it; v.erase(it);
    sort(v.begin(), v.end(), [&r](auto _a, auto _b){
        T c = cross(r, _a, _b); return c == 0 ? _a < _b : c > 0;
    });
    vector<point<T>> h({r, v[0]});
    for (int i = 1; i < v.size(); i++) {
        while (cross(h[h.size()-2], h.back(), v[i]) < 0) h.pop_back();
        h.push_back(v[i]);
    }
    return h;
}

// returns the indices of the points in the convex hull sorted in CCW order
template<typename T>
vector<int> convexhull_indices(vector<point<T>> v) {
    int m = min_element(v.begin(), v.end())-v.begin();
    vector<int> p(v.size()); iota(p.begin(), p.end(), 0);
    p.erase(p.begin()+m);
    sort(p.begin(), p.end(), [&](auto _a, auto _b){
        T c = cross(v[m], v[_a], v[_b]); return c == 0 ? v[_a] < v[_b] : c > 0;
    });
    vector<int> h({m, p[0]});
    for (int i = 1; i < p.size(); i++) {
        while (cross(v[h[h.size()-2]], v[h.back()], v[p[i]]) < 0) h.pop_back();
        h.push_back(p[i]);
    }
    return h;
}