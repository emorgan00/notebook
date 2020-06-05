#include <bits/stdc++.h>
using namespace std;

typedef struct point {
	double x, y;
	double arg() { return atan2(y, x); }
	double mod() { return hypot(y, x); }
} point;

inline bool convex(point& a, point& m, point& b) { return ((a.x-m.x) * (b.y-m.y) - (b.x-m.x) * (a.y-m.y)) > 0; }
inline bool operator<(point a, point b) { return false; }

// compute the convex hull of a list of points in O(nlogn) time.

vector<point> hull(const vector<point>& points) {

	// compute center of mass
	double midx = 0, midy = 0;
	for (auto p : points) {
		midx += p.x;
		midy += p.y;
	}
	midx /= points.size();
	midy /= points.size();

	vector<pair<double, point>> copy;
	vector<point> hull;

	for (auto p : points)
		copy.push_back({atan2(p.y-midy, p.x-midx), {p.x-midx, p.y-midy}});
	sort(copy.begin(), copy.end());

	// gift-wrapping algorithm
	for (int i = 0; i < copy.size()-1; i++) {
		hull.push_back(copy[i].second);
		while (hull.size() > 2 && !convex(hull[hull.size()-1], hull[hull.size()-2], hull[hull.size()-3])) {
			hull.erase(hull.end()-2);
		}
	}

	hull.push_back(copy[copy.size()-1].second);
	int hullstart = 0;
	while (hull.size() > 2 && !convex(hull[hull.size()-1], hull[hull.size()-2], hull[hull.size()-3])) {
		hull.erase(hull.end()-2);
	}
	while (1) {
		if (hull.size() > 2 && !convex(hull[hullstart], hull[hull.size()-1], hull[hull.size()-2])) {
			hull.erase(hull.end()-1);
			continue;
		}
		if (hull.size() > 2 && !convex(hull[hullstart+1], hull[hullstart], hull[hull.size()-1])) {
			hullstart++;
			continue;
		}
		break;
	}

	vector<point> out;
	for (int i = hullstart; i < hull.size(); i++)
		out.push_back({hull[i].x+midx, hull[i].y+midy});
	return out;
}