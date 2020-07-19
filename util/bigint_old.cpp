#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

// definition

#define bigint_size 100 // change this if bigint isn't storing enough
#define bigint_max 1e18

typedef struct bigint {
	int datasize;
	ull data[bigint_size];
	bigint(unsigned int x) {
		datasize = 1;
		data[0] = (ull)x;
	}
} bigint;

// to string

string to_string(bigint& a) {
	string out = "";
	for (int i = 0; i < a.datasize; i++) {
		while (out.size()%18 != 0)
			out = "0"+out;
		out = to_string(a.data[i])+out;
	}
	return out;
}

ostream& operator<<(ostream& out, bigint& a) {
	out << to_string(a);
	return out;
}

// comparison operators

inline bool operator==(bigint& a, bigint& b) {
	if (a.datasize != b.datasize)
		return false;
	for (int i = 0; i < a.datasize; i++)
		if (a.data[i] != b.data[i])
			return false;
	return true;
}

inline bool operator>(bigint& a, bigint& b) {
	if (a.datasize != b.datasize)
		return a.datasize > b.datasize;
	for (int i = a.datasize-1; i >= 0; i--)
		if (a.data[i] != b.data[i])
			return a.data[i] > b.data[i];
	return false;
}

inline bool operator<(bigint& a, bigint& b) {
	return b>a;
}

// addition

inline void operator+=(bigint& a, bigint& b) {
	int carry = 0;
	ull temp;
	for (int i = 0; i < b.datasize || carry; i++) {
		assert(i < 100);
		if (a.datasize == i) {
			a.data[a.datasize] = 0;
			a.datasize++;
		}
		if (i < b.datasize) {
			if (a.data[i] >= bigint_max-b.data[i]-carry) {
				temp = (a.data[i]-bigint_max+b.data[i]+carry);
				carry = 1;
			} else {
				temp = (a.data[i]+b.data[i]+carry);
				carry = 0;
			}
		} else {
			if (a.data[i] >= bigint_max-carry) {
				temp = (a.data[i]-bigint_max+carry);
				carry = 1;
			} else {
				temp = (a.data[i]+carry);
				carry = 0;
			}
		}
		a.data[i] = temp;
	}
}

inline void operator+=(bigint& a, ull b) {
	int carry = 0;
	ull temp;
	for (int i = 0; i < 1 || carry; i++) {
		assert(i < 100);
		if (a.datasize == i) {
			a.data[a.datasize] = 0;
			a.datasize++;
		}
		if (i < 1) {
			if (a.data[i] >= bigint_max-b-carry) {
				temp = (a.data[i]-bigint_max+b+carry);
				carry = 1;
			} else {
				temp = (a.data[i]+b+carry);
				carry = 0;
			}
		} else {
			if (a.data[i] >= bigint_max-carry) {
				temp = (a.data[i]-bigint_max+carry);
				carry = 1;
			} else {
				temp = (a.data[i]+carry);
				carry = 0;
			}
		}
		a.data[i] = temp;
	}
}

inline void operator++(bigint& a) {
	a += 1;
}

inline void operator++(bigint& a, int dummy) {
	a += 1;
}