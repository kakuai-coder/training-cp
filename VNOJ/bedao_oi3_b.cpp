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

#define TASK "mexquery"

using namespace std;

template <typename T>
int isize(const T& a) { return a.size(); }

template <typename T1, typename T2>
bool maximize(T1& a, T2 b) { return a < b ? a = b, 1 : 0; }

template <typename T1, typename T2>
bool minimize(T1& a, T2 b) { return a > b ? a = b, 1 : 0; }

const int maxN = 3e5 + 11;

int n, q, a[maxN];

struct SegmentTree {
	int st[4 * maxN], lazy[4 * maxN];

	SegmentTree() {
		memset(st, 0, sizeof(st));
		memset(lazy, -1, sizeof(lazy));
	}

	void down(int id, int l, int r, int mid) {
		if (lazy[id] == -1) return ;

		lazy[id << 1] = lazy[id];
		lazy[id << 1 | 1] = lazy[id];

		st[id << 1] = lazy[id] * (mid - l + 1);
		st[id << 1 | 1] = lazy[id] * (r - mid);

		lazy[id] = -1;
	}

	void update(int id, int l, int r, int u, int v, int val) {
		if (l > v || r < u) return ;
		if (u <= l && r <= v) {
			st[id] = val * (r - l + 1);
			lazy[id] = val;
			return ;
		}

		int mid = (l + r) >> 1;
		down(id, l, r, mid);

		update(id << 1, l, mid, u, v, val);
		update(id << 1 | 1, mid + 1, r, u, v, val);

		st[id] = st[id << 1] + st[id << 1 | 1];
	}

	int query(int id, int l, int r, int u, int v) {
		if (l > v || r < u) return 0;
		if (u <= l && r <= v) return st[id];

		int mid = (l + r) >> 1;
		down(id, l, r, mid);

		return query(id << 1, l, mid, u, v) + query(id << 1 | 1, mid + 1, r, u, v);
	}
} seg[33];

int cnt[33];

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (ifstream(TASK ".inp")) {
		freopen(TASK ".inp", "r", stdin);
		freopen(TASK ".out", "w", stdout);
	}

	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	for (int i = 1; i <= n; ++i) seg[a[i]].update(1, 1, n, i, i, 1);

	cin >> q;

	int type, l, r, x;
	while (q--) {
		cin >> type >> l >> r;
		if (type == 1) {
			cin >> x;

			for (int i = 0; i <= 30; ++i) {
				cnt[i] = seg[i].query(1, 1, n, l, r);
				seg[i].update(1, 1, n, l, r, 0);
			}

			if (x == 1) {
				for (int i = 0; i <= 30; ++i) {
					seg[i].update(1, 1, n, l, l + cnt[i] - 1, 1);
					l += cnt[i];
				}
			} else {
				for (int i = 30; ~i; --i) {
					seg[i].update(1, 1, n, l, l + cnt[i] - 1, 1);
					l += cnt[i];
				}
			}
		} else {
			for (int i = 0; i <= 31; ++i) if (seg[i].query(1, 1, n, l, r) == 0) {
				cout << i << '\n';
				break;
			}
		}
	}
}
