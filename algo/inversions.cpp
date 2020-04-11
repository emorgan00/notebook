#include <bits/stdc++.h>
using namespace std;

// Returns the number of pairs (i, j) such that i < j and A[i] > A[j].
// Runs in O(nlogn). Will not mutate the array.

template<typename T>
int sub_inversions(vector<T>& A, vector<T>& store, int lower, int upper) {

	if (lower == upper) return 0;
	int mid = (lower+upper)/2;
	int out = sub_inversions(store, A, lower, mid) + sub_inversions(store, A, mid+1, upper);

	// merge sort
	int j = mid+1, k = lower;
	for (int i = lower; i <= mid; i++) {
		while (j <= upper && A[j] < A[i])
			store[k++] = A[j++];
		store[k++] = A[i];
		out += j-mid-1;
	}
	while (j <= upper)
		store[k++] = A[j++];

	return out;
}

template<typename T>
int inversions(vector<T>& A) {
	vector<T> copy(A), store(A);
	return sub_inversions(copy, store, 0, A.size()-1);
}