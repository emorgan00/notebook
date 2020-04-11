#include <bits/stdc++.h>
using namespace std;

// Note: this is not finished/working

// Accepts a list of segments in the form {{{a, b}, {c, d}}, ...}.
// Returns a list of intersections between pairs of segments.
// Runs in O(nlogn).

#define x first
#define y second

template<typename T>
struct event {
	pair<T, T> p;
	int type, index;
};

struct sweep_item {
	int order, index;
};

struct cmp_x {
	template<typename T>
	bool operator()(const event<T>& a, const event<T>& b) {
		return a.p.x > b.p.x;
	}
};

struct cmp_y {
	template<typename T>
	bool operator()(const event<T>& a, const event<T>& b) {
		return a.p.y > b.p.y;
	}
};

template<typename T>
inline bool intersects(T a, T b, T c, T d) {
	float t = ((a.x-c.x) * (c.y-d.y) - (a.y-c.y) * (c.x-d.x)) / ((a.x-b.x) * (c.y-d.y) - (a.y-b.y) * (c.x-d.x));
	float u = -1 * ((a.x-b.x) * (a.y-c.y) - (a.y-b.y) * (a.x-c.x)) / ((a.x-b.x) * (c.y-d.y) - (a.y-b.y) * (c.x-d.x));
	return t >= 0 && t <= 1 && u >= 0 && u <= 1;
}

template<typename T>
inline T intersection(T a, T b, T c, T d) {
	float t = ((a.x-c.x) * (c.y-d.y) - (a.y-c.y) * (c.x-d.x)) / ((a.x-b.x) * (c.y-d.y) - (a.y-b.y) * (c.x-d.x));
	return {a.x + t*(b.x-a.x), a.y + t*(b.y-a.y)};
}

template<typename T>
vector<pair<T, T>> intersections(vector<pair<pair<T, T>, pair<T, T>>>& segments) {

	priority_queue<struct event<T>, vector<event<T>>, cmp_x> events;
	set<struct event<T>, cmp_y> sweep;
	vector<pair<T, T>> out;

	for (int i = 0; i < segments.size(); i++) {
		auto s = segments[i];
		if (s.first.x > s.second.x)
			swap(s.first, s.second);
		events.push({s.first, 0, i});
		events.push({s.second, 1, i});
	}

	// Bentley-Ottman algorithm
	while (!events.empty()) {
		auto e = events.top();
		events.pop();

		if (e.type == 0) {

			sweep.insert(e);
			auto s = segments[e.index];
			auto a_it = sweep.lower_bound(e);
			auto b_it = sweep.upper_bound(e);

			if (a_it != sweep.begin()) {
				auto a = segments[a_it->index];
				if (intersects(a.first, a.second, s.first, s.second)) {
					events.push({intersection(a.first, a.second, s.first, s.second), 2, a_it->index});
				}
			}

			if (b_it != sweep.end()) {
				auto b = segments[b_it->index];
				if (intersects(b.first, b.second, s.first, s.second)) {
					events.push({intersection(b.first, b.second, s.first, s.second), 2, e.index});
				}
			}

		} else if (e.type == 1) {

			event<T> start = {segments[e.index].first, 0, e.index};
			auto a_it = sweep.lower_bound(start);
			auto b_it = sweep.upper_bound(start);
			sweep.erase(start);

			if (a_it == sweep.begin() || b_it == sweep.end())
				continue;
			auto a = segments[a_it->index];
			auto b = segments[b_it->index];

			if (intersects(a.first, a.second, b.first, b.second)) {
				events.push({intersection(a.first, a.second, b.first, b.second), 2, a_it->index});
			}

		} else {

			out.push_back(e.p);
			auto a_it = sweep.find(e);
			auto b_it = sweep.upper_bound(e);
			swap(a_it->p.y, b_it->p.y);
		}
	}
	return out;
}

int main() {
	vector<pair<pair<int, int>, pair<int, int>>> segments = {{{1, 1}, {2, 2}}, {{2, 1}, {1, 2}}};
	cout << intersections(segments).size() << endl;
}