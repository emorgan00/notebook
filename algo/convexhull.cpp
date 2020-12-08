// returns the convex hull sorted in CCW order, requires math/geometry
// see https://cp-algorithms.com/geometry/grahams-scan-convex-hull.html
// (basically copied from there, this version works with integers)

template<typename T>
vector<point<T>> convexhull(vector<point<T>> v) {
    auto it = min_element(v.begin(), v.end());
    point<T> r = *it; v.erase(it);
    sort(v.begin(), v.end(), [&r](auto a, auto b){
        T c = cross(r, a, b); return c == 0 ? a < b : c > 0;
    });
    vector<point<T>> h({r, v[0]});
    for (int i = 1; i < v.size(); i++) {
        while (cross(h[h.size()-2], h.back(), v[i]) < 0) h.pop_back();
        h.push_back(v[i]);
    }
    return h;
}