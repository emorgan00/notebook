struct convexhull {

    typedef long double T;
    using point = array<T, 3>;

    static T cw(const point& a, const point& b, const point& c) {
        return a[1]*(b[2]-c[2])+b[1]*(c[2]-a[2])+c[1]*(a[2]-b[2]);
    }

    T cx = 0, cy = 0;
    point pt(T x, T y) { return {atan2(y-cy, x-cx), x, y}; }

    vector<pair<T, T>> tmp;
    multiset<point> hull;
    using it = decltype(hull.end());
    it inc(it& a) { return a == --hull.end() ? a = hull.begin() : ++a; }
    it dec(it& a) { return a == hull.begin() ? a = --hull.end() : --a; }

    // erase everything from the hull.
    void clear() { tmp.clear(), hull.clear(); }

    // returns true if the point (x, y) is contained within the
    // interior of the convex hull in O(logn) time.
    bool contains(T x, T y) {
        if (hull.empty()) return 0;
        point p = pt(x, y);
        it b = hull.lower_bound(p); dec(b); it a = b; inc(a);
        return cw(*a, p, *b) > 0;
    }

    // insert the point (x, y) into the hull in O(logn) time.
    void insert(T x, T y) {
        if (hull.empty()) {
            tmp.push_back({x, y});
            if (tmp.size() == 3) {
                for (auto& [px, py] : tmp) cx += px/3, cy += py/3;
                for (auto& [px, py] : tmp) hull.insert(pt(px, py));
            }
        } else if (!contains(x, y)) {
            it a = hull.insert(pt(x, y)), b = a, c = inc(b); inc(c);
            while (cw(*a, *b, *c) <= 0) hull.erase(b), b = c, inc(c);
            b = a, c = dec(b), dec(c);
            while (cw(*a, *b, *c) >= 0) hull.erase(b), b = c, dec(c);
        }
    }
};