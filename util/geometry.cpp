typedef long double ld;
template<typename T, typename U> using c_t = decltype(T()+U());

template<typename T>
struct point {

    T x, y;

    point(T _x, T _y) : x(_x), y(_y) {}
    point() : point(0, 0) {}
    template<typename U> point(point<U> o) : point(o.x, o.y) {}

    T sqdist() { return x*x+y*y; }
    ld dist() { return hypot(ld(x), ld(y)); }
    
    friend string to_string(const point a) { return "("+to_string(a.x)+", "+to_string(a.y)+")"; }
    friend istream& operator>>(istream& i, point& a) { return i >> a.x >> a.y; }
    friend ostream& operator<<(ostream& o, const point a) { return o << "(" << a.x << ", " << a.y << ")"; }

    point& operator+=(const point o) { x += o.x, y += o.y; return *this; }
    point& operator-=(const point o) { x -= o.x, y -= o.y; return *this; }
    template<typename U> point& operator*=(const U r) { x *= r, y *= r; return *this; }
    template<typename U> point& operator/=(const U r) { x /= r, y /= r; return *this; }
    template<typename U> friend point<c_t<T, U>> operator+(point a, point<U> b) { return {a.x+b.x, a.y+b.y}; }
    template<typename U> friend point<c_t<T, U>> operator-(point a,  point<U> b) { return {a.x-b.x, a.y-b.y}; }
    template<typename U> friend point<c_t<T, U>> operator*(const point a, const U r) { return {a.x*r, a.y*r}; }
    template<typename U> friend point<c_t<T, U>> operator*(const U r, const point a) { return {a.x*r, a.y*r}; }
    template<typename U> friend point<c_t<T, U>> operator/(const point a, const U r) { return {a.x/r, a.y/r}; }
    template<size_t i> T get() { return i ? y : x; }
};

template<typename T, typename U>
c_t<T, U> dot(point<T> a, point<U> b) { return a.x*b.x + a.y*b.y; }
template<typename T, typename U>
c_t<T, U> cross(point<T> a, point<U> b) { return a.x*b.y - a.y*b.x; }

// returns the projection of A to line BC
point<ld> proj(point<ld> a, point<ld> b, point<ld> c) {
    return dot(a-b, c-b)/(c-b).sqdist()*(c-b)+b;
}

// returns the point of intersection of lines AB and CD
point<ld> intersection(point<ld> a, point<ld> b, point<ld> c, point<ld> d) {
    ld s = cross(a-c, b-a)/ld(cross(d-c, b-a));
    return s*d + (1-s)*c;
}

// returns true if AB and CD intersect
bool intersects(point<ld> a, point<ld> b, point<ld> c, point<ld> d) {
    ld s = cross(a-c, b-a)/ld(cross(d-c, b-a)), t = cross(c-a, d-c)/ld(cross(b-a, d-c));
    return t >= 0 && t <= 1 && s >= 0 && s <= 1;
}

// returns double the signed area of a non-self-intersecting polygon (positive if CW, negative if CCW)
template<typename T>
T area(vector<point<T>> v) {
    T out = cross(v.back(), v[0]);
    for (int i = 0; i < v.size()-1; i++) out += cross(v[i], v[i+1]);
    return out;
}