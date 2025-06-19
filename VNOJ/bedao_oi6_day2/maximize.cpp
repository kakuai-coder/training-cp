/**
 * author: tinhnopro (tinh nop)
 * created: 2024-12-03
**/
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 0
#endif // LOCAL

#include <bits/stdc++.h>

#define TASK "maximize"

using namespace std;

template <typename T> int isize(const T& a) { return a.size(); }

bool maximize(int64_t& a, int64_t b) {
	return a < b ? a = b, true : false;
}

bool minimize(int64_t& a, int64_t b) {
	return a > b ? a = b, true : false;
}

const int maxN = 1e5 + 5;
const int64_t inf = (int64_t) 1e18 + 5;

int n, k;
int64_t dp[maxN], a[maxN];

struct SegmentTree {
	int64_t st[4 * maxN], lazy[4 * maxN];
	void init() {
		memset(st, 0, sizeof(st));
		memset(lazy, 0, sizeof(lazy));
	}

	void build(int id, int l, int r) {
		lazy[id] = 0;
		if (l == r) return void(st[id] = dp[l]);

		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);

		st[id] = max(st[id << 1], st[id << 1 | 1]);
	}

	void down(const int& id) {
		if (!lazy[id]) return ;

		lazy[id << 1] += lazy[id];
		lazy[id << 1 | 1] += lazy[id];

		st[id << 1] += lazy[id];
		st[id << 1 | 1] += lazy[id];

		lazy[id] = 0;
	}

	void update(int id, int l, int r, int u, int v, int64_t val) {
		if (l > v || r < u) return ;
		if (u <= l && r <= v) {
			st[id] += val;
			lazy[id] += val;
			return ;
		}

		down(id);

		int mid = (l + r) >> 1;
		update(id << 1, l, mid, u, v, val);
		update(id << 1 | 1, mid + 1, r, u, v, val);

		st[id] = max(st[id << 1], st[id << 1 | 1]);
	}

	int64_t Get(int id, int l, int r, int u, int v) {
		if (l > v || r < u) return -inf;
		if (u <= l && r <= v) return st[id];

		down(id);

		int mid = (l + r) >> 1;

		return max(Get(id << 1, l, mid, u, v),
							Get(id << 1 | 1, mid + 1, r, u, v));
	}
} seg;

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (ifstream(TASK ".inp")) {
		freopen(TASK ".inp", "r", stdin);
		freopen(TASK ".out", "w", stdout);
	}

	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		dp[i] = -inf;
	}
	dp[0] = 0;

	deque<int64_t> stmax, stmin;

	while (k--) {
		stmax.clear();
		stmin.clear();
		seg.build(1, 0, n);

		stmax.push_back(0);
		stmin.push_back(0);

		for (int i = 1; i <= n; ++i) {
			while (isize(stmax) > 1 && a[stmax.back()] <= a[i]) {
				int j = stmax.back();
				stmax.pop_back();
				int j2 = stmax.back();
				seg.update(1, 0, n, j2, j - 1, -a[j]);
			}

			while (isize(stmin) > 1 && a[stmin.back()] >= a[i]) {
				int j = stmin.back();
				stmin.pop_back();
				int j2 = stmin.back();
				seg.update(1, 0, n, j2, j - 1, -a[j]);
			}

			seg.update(1, 0, n, stmax.back(), i - 1, a[i]);
			seg.update(1, 0, n, stmin.back(), i - 1, a[i]);

			stmin.push_back(i);
			stmax.push_back(i);

			dp[i] = seg.Get(1, 0, n, 0, i - 1);
//			cout << dp[i] << ' ';
		}
	}

	cout << dp[n];
}
