// computes the indices of all points which
// are members of the convex hull in O(nlogn) time.

template<typename T>
struct pt {
    T x, y;
};

template<typename T>
bool cw(pt<T> a, pt<T> b, pt<T> c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

template<typename T>
bool ccw(pt<T> a, pt<T> b, pt<T> c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

// see https://cp-algorithms.com/geometry/grahams-scan-convex-hull.html
// (this is basically copied from there)

template<typename T>
vector<int> convexhull(vector<pt<T>>& p) {
    vector<int> ord(p.size()); iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j){return p[i] < p[j];});
    pt<T> a = p[ord[0]], b = p[ord.back()];
    vector<int> u = {ord[0]}, l = {ord[0]};
    for (int j = 1; j < p.size(); j++) {
        int i = ord[j];
        if (j == p.size()-1 || cw(a, p[i], b)) {
            while (u.size() >= 2 && !cw(p[u[u.size()-2]], p[u[u.size()-1]], p[i]))
                u.pop_back();
            u.push_back(i);
        }
        if (j == p.size()-1 || ccw(a, p[i], b)) {
            while(l.size() >= 2 && !ccw(p[l[l.size()-2]], p[l[l.size()-1]], p[i]))
                l.pop_back();
            l.push_back(i);
        }
    }
    for (int i = l.size()-2; i > 0; i--)
        u.push_back(l[i]);
    return u;
}