#include <bits/stdc++.h>
using namespace std;

typedef struct point {
    double x, y;
    double arg() { return atan2(y, x); }
    double mod() { return hypot(y, x); }
} point;

typedef struct segment {
    point a, b;
} segment;

// short functions

inline double dot(point a, point b) { return a.x*b.x + a.y*b.y; }
inline double cross(point a, point b) { return a.x*b.y - a.y*b.x; }
inline double dist(point a, point b) { return hypot(a.x-b.x, a.y-b.y); }

inline bool anglecmp(point a, point b) { return atan2(a.y, a.x) < atan2(b.y, b.x); }
inline bool distancecmp(point a, point b) { return hypot(a.y, a.x) < hypot(b.y, b.x); }

inline point intersection(point a, point b, point c, point d) {
    float t = ((a.x-c.x) * (c.y-d.y) - (a.y-c.y) * (c.x-d.x)) / ((a.x-b.x) * (c.y-d.y) - (a.y-b.y) * (c.x-d.x));
    return {a.x + t*(b.x-a.x), a.y + t*(b.y-a.y)};
}
inline point intersection(segment& a, segment& b) { return intersection(a.a, a.b, b.a, b.b); }

inline bool intersects(point a, point b, point c, point d) {
    float t = ((a.x-c.x) * (c.y-d.y) - (a.y-c.y) * (c.x-d.x)) / ((a.x-b.x) * (c.y-d.y) - (a.y-b.y) * (c.x-d.x));
    float u = -1 * ((a.x-b.x) * (a.y-c.y) - (a.y-b.y) * (a.x-c.x)) / ((a.x-b.x) * (c.y-d.y) - (a.y-b.y) * (c.x-d.x));
    return t >= 0 && t <= 1 && u >= 0 && u <= 1;
}
inline bool intersects(segment& a, segment& b) { return intersects(a.a, a.b, b.a, b.b); }

// longer, more specialized functions

double area(vector<point> v) { // v.size() must be at least 3.
    double out = cross(v[v.size()-1], v[0]);
    for (int i = 0; i < v.size()-1; i++)
        out += cross(v[i], v[i+1]);
    return abs(out);
}

// returns true if point a is contained in the polygon
bool contains(vector<segment> v, point a) {
    int count = 0;
    point infinity_point = {0, 1e100};
    for (segment s : v) {
        segment ray = {a, infinity_point};
        if (intersects(s, ray));
            count++; 
    }
    return count%2 == 1;
}