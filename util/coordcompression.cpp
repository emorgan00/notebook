#include <bits/stdc++.h>
using namespace std;

// Transform the contents of A into elements of [0..N],
// while preserving the ordering/equality relationship among indices into A.
// Runs in O(nlogn).

template<typename T>
vector<int> compress(vector<T>& A) {

	vector<pair<T, int>> ordering(A.size());
	vector<int> out(A.size());
	for (int i = 0; i < A.size(); i++)
		ordering[i] = {A[i], i};

	sort(ordering.begin(), ordering.end());

	int offset = 0;
	for (int i = 0; i < A.size(); i++) {
		if (i > 0 && ordering[i].first == ordering[i-1].first) offset++;
		out[ordering[i].second] = i-offset;
	}
	return out;
}

// Same thing, but you can supply a custom comparator to use for A,
// as well as a function to test if two elements are equivalent

template<typename T, typename X, typename Y>
vector<int> compress(vector<T>& A, X comp, Y equiv) {

    vector<pair<T, int>> ordering(A.size());
    vector<int> out(A.size());
    for (int i = 0; i < A.size(); i++)
        ordering[i] = {A[i], i};

    sort(ordering.begin(), ordering.end(), [&](pair<T, int>& x, pair<T, int>& y){return comp(x.first, y.first);});

    int offset = 0;
    for (int i = 0; i < A.size(); i++) {
        if (i > 0 && equiv(ordering[i].first, ordering[i-1].first)) offset++;
        out[ordering[i].second] = i-offset;
    }
    return out;
}