/*
	Author: kakuai
	created: 2025.07.03 17:27:34
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }

#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif

const int N = 4;
const int FN_SZ = N + 1;
const int MIN_V = 0;
const int MAX_V = 32767;

int val[N][N];
i64 fn[FN_SZ][FN_SZ];

void init_fn() {
	for (int i = 0; i < FN_SZ; ++i) {
		for (int j = 0; j < FN_SZ; ++j) {
			fn[i][j] = 0;
		}
	}
}

void upd(int r_idx, int c_idx, int d) {
	int r = r_idx + 1;
	int c = c_idx + 1;
	for (int i = r; i < FN_SZ; i += i & -i) {
		for (int j = c; j < FN_SZ; j += j & -j) {
			fn[i][j] += d;
		}
	}
}

i64 q_pref(int r_idx, int c_idx) {
	int r = r_idx + 1;
	int c = c_idx + 1;
	i64 res = 0;
	for (int i = r; i > 0; i -= i & -i) {
		for (int j = c; j > 0; j -= j & -j) {
			res += fn[i][j];
		}
	}
	return res;
}

i64 q_rect(int l, int b, int r, int t) {
	i64 A = q_pref(r, t);
	i64 B = (l > 0 ? q_pref(l - 1, t) : 0);
	i64 C = (b > 0 ? q_pref(r, b - 1) : 0);
	i64 D = (l > 0 && b > 0 ? q_pref(l - 1, b - 1) : 0);
	return A - B - C + D;
}

void kakuai() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			val[i][j] = 0;
		}
	}
	init_fn();

	int type;
	while (cin >> type) {
		if (type == 0) {
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					val[i][j] = 0;
				}
			}
			init_fn();
		} else if (type == 1) {
			int x, y, a;
			cin >> x >> y >> a;
			x = max(0, min(N - 1, x));
			y = max(0, min(N - 1, y));
			int old_val = val[x][y];
			i64 temp = old_val + a;
			int new_val = max(MIN_V, min(MAX_V, (int)temp));
			val[x][y] = new_val;
			upd(x, y, new_val - old_val);
		} else if (type == 2) {
			int l, b, r, t;
			cin >> l >> b >> r >> t;
			l = max(0, min(N - 1, l));
			b = max(0, min(N - 1, b));
			r = max(0, min(N - 1, r));
			t = max(0, min(N - 1, t));
			if (l > r) swap(l, r);
			if (b > t) swap(b, t);
			cout << q_rect(l, b, r, t) << '\n';
		} else if (type == 3) {
			break;
		}
	}
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "j"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	kakuai();

	cerr << "\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}
