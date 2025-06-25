/*
	Author: kakuai
	created: 2025.06.20 08:31:58
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 1e5 + 5; 
const int LOG = 20; 

int n, q; 
i64 a[maxN], sum[maxN], mx[maxN][LOG + 1], mi[maxN][LOG + 1], X, Y; 

void build_rmq() {
	for (int i = 1; i <= n; ++i) {
		mx[i][0] = mi[i][0] = sum[i];
	}

	for (int j = 1; j <= LOG; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
			mi[i][j] = min(mi[i][j - 1], mi[i + (1 << (j - 1))][j - 1]);
		}
	}
}

i64 get_max(int l, int r) {
	if (l > r) return 1e16;
	int lg = __lg(r - l + 1);
	return max(mx[l][lg], mx[r - (1 << lg) + 1][lg]);
}

i64 get_min(int l, int r) {
	if (l > r) return -1e16;
	int lg = __lg(r - l + 1);
	return min(mi[l][lg], mi[r - (1 << lg) + 1][lg]);
}

int nxt_X(int l, int k) {
	i64 d = X + sum[l - 1] - k; 

	int lo = l, hi = n + 1; 

	while (hi - lo > 1) {
		int mid = (lo + hi) / 2; 
		if (get_max(l, mid) < d) {
			lo = mid; 
		} else hi = mid; 
	}

	return lo; 
}

int nxt_Y(int l, int k) {
	i64 d = Y + sum[l - 1] - k; 

	int lo = l - 1, hi = n + 1; 

	while (hi - lo > 1) {
		int mid = (lo + hi) / 2; 
		if (get_max(l, mid) <= d) {
			lo = mid; 
		} else hi = mid; 
	}

	return hi; 
}


void kakuai() {
	cin >> n >> X >> Y; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
		sum[i] = sum[i - 1] + a[i]; 
	}

	cin >> q; 
	while (q--) {
		int l, r, k; cin >> l >> r >> k;

		int idx = l;
		i64 s = k;

		while (idx <= r) {
			s += a[idx]; 
			if (s < X) s = X; 
			if (s > Y) s = Y; 
			idx++;
		}

		cout << s << '\n'; 
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "a"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".ans", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}