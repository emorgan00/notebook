#include <bits/stdc++.h>
using namespace std;

// both unite and query take effectively constant time
struct unionfind {

	int length;
	vector<int> parent;

	unionfind(int s) {
		length = s;
		parent.assign(s, 0);
		std::iota(parent.begin(), parent.end(), 0);
	}

	int rep(int x) {
		while (x != parent[x]) {
			parent[x] = parent[parent[x]];
			x = parent[x];
		}
		return x;
	}

	void unite(int a, int b) {
		a = rep(a);
		b = rep(b);
		if (a == b)
			return;
		parent[b] = a;
	}

	// returns true if a and b are in the same set.
	inline bool query(int a, int b) {
		return rep(a) == rep(b);
	}
};