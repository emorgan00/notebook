// Range associative-function query data structure.
// O(nlogn) to set up, O(1) to query.
// Accepts an arbitrary associative function.

template<typename T, T F(T, T)>
struct dst {

	int length;
	vector<vector<T>> subs;

	void _fill_subs(int a, int b, int h) {
		int m = (a+b) >> 1;
		if (m < length) {
			T r = subs[h][m] = subs[0][m];
			for (int i = m-1; i >= a; i--)
				subs[h][i] = F(subs[0][i], subs[h][i+1]);
		}
		if (m+1 < length) {
			T r = subs[h][m+1] = subs[0][m+1];
			for (int i = m+2; i <= min(b, length-1); i++)
				subs[h][i] = F(subs[h][i-1], subs[0][i]);
		}
		if (h > 1) {
			_fill_subs(a, m, h-1);
			_fill_subs(m+1, b, h-1);
		}
	}

	dst(vector<T>& data) {
		length = data.size();
		int exp = 32-__builtin_clz(length-1);
		subs.assign(exp, vector<T>(length));
		for (int i = 0; i < length; i++)
			subs[0][i] = data[i];
		_fill_subs(0, (1<<exp)-1, exp-1);
	}

	// function over the range [a..b]
	inline T query(int a, int b) {
		if (a == b) return subs[0][a];
		int s = 31-__builtin_clz(b-a);
		int as = (a >> s) + 1, bs = b >> s;
		int h = __builtin_ctz(max(as & -as, bs & -bs)) + s;
		return F(subs[h][a], subs[h][b]);
	}
};