#include <bits/stdc++.h>
using namespace std;

// check if x in A
template<typename T>
bool bs_contains(const vector<T>& A, T x) {

	int a = 0, b = A.size()-1;
	while (a <= b) {
		int m = (a+b)/2;
		if (x > A[m])
			a = m+1;
		else if (x < A[m])
			b = m-1;
		else return true;
	}
	return false;
}

// earliest position where x could go if inserted in A
template<typename T>
int bs_index(const vector<T>& A, T x) {

	int a = 0, b = A.size()-1;
	while (a <= b) {
		int m = (a+b)/2;
		if (x > A[m])
			a = m+1;
		else
			b = m-1;
	}
	return a;
}