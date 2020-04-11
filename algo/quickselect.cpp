#include <bits/stdc++.h>
using namespace std;

// get the k-th smallest element of A in expected O(n) time.
// Note: this will shuffle the contents of A by partially sorting it.
template<typename T>
T quickselect(vector<T>& A, int k) {
	int lower = 0, upper = A.size()-1;

	while (1) {
		int p = A[lower], q = A[upper], r = A[(lower+upper)>>1];
		int pivot = max(min(p, q), min(max(p, q), r));

		// dutch-flag partitioning
		int a = lower, b = upper, m = lower;
		while (m <= b) {
			if (A[m] < pivot) {
				swap(A[a], A[m]);
				a++; m++;
			} else if (A[m] == pivot)
				m++;
			else {
				swap(A[m], A[b]);
				b--;
			}
		}

		if (k >= a && k <= b)
			return A[k];
		else if (k < a)
			upper = a-1;
		else
			lower = b+1;
	}
	// never reached
	assert(false);
}