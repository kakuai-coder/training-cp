/*
	Author: kakuai
	created: 2025.06.20 21:27:22
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

const int maxN = 2e5 + 5, inf = 1e9 + 11; 

int k, n, q, a[6][maxN], prob[1 << 6][maxN], rev[1 << 6];

struct SegmentTree {
	int st[4 * maxN][2]; 

	SegmentTree() {
		memset(st[1], 0, sizeof(st[1])); 
		memset(st[0], 0, sizeof(st[0]));
	}

	void update(int id, int l, int r, int pos, int val) {
		if (l > pos || pos > r) return ; 
		if (l == r) {
			st[id][0] = st[id][1] = val;
			return ; 
		}

		int mid = (l + r) >> 1; 
		update(id << 1, l, mid, pos, val);
		update(id << 1 | 1, mid + 1, r, pos, val); 

		st[id][0] = max(st[id << 1][0], st[id << 1 | 1][0]);
		st[id][1] = min(st[id << 1][1], st[id << 1 | 1][1]); 
	}

	int get_max(int id, int l, int r, int u, int v) {
		if (l > v || r < u) return -inf; 
		if (u <= l && r <= v) {
			return st[id][0];
		}

		int mid = (l + r) >> 1;
		return max(get_max(id << 1, l, mid, u, v), get_max(id << 1 | 1, mid + 1, r, u, v));
	}

	int get_min(int id, int l, int r, int u, int v) {
		if (l > v || r < u) return inf; 
		if (u <= l && r <= v) {
			return st[id][1];
		}

		int mid = (l + r) >> 1;
		return min(get_min(id << 1, l, mid, u, v), get_min(id << 1 | 1, mid + 1, r, u, v));
	}
};

SegmentTree st[1 << 6];

void kakuai() {
	cin >> n >> k; 
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < k; ++j) {
			cin >> a[j][i]; 
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int mask = 0; mask < (1 << k); ++mask) {
			for (int j = 0; j < k; ++j) {
				if ((mask >> j) & 1) {
					prob[mask][i] += a[j][i];
				} else prob[mask][i] -= a[j][i];
 			}
		}
	}

	for (int mask = 0; mask < (1 << k); ++mask) {
		rev[mask] = ((1 << k) - 1) ^ mask;

		// cerr << mask << ' ' << rev[mask] << '\n';
 	}

	for (int i = 1; i <= n; ++i) {
		for (int mask = 0; mask < (1 << k); ++mask) {
			st[mask].update(1, 1, n, i, prob[mask][i]);
		}
	}

	cin >> q; 
	while (q--) {
		int type; 
		cin >> type; 

		if (type == 1) {
			int idx; cin >> idx; 
			for (int i = 0; i < k; ++i) cin >> a[i][idx];
			for (int mask = 0; mask < (1 << k); ++mask) {
				prob[mask][idx] = 0; 
				for (int j = 0; j < k; ++j) {
					if ((mask >> j) & 1) {
						prob[mask][idx] += a[j][idx];
					} else prob[mask][idx] -= a[j][idx];
				}
				st[mask].update(1, 1, n, idx, prob[mask][idx]);
			}
		} else {
			int l, r; 
			cin >> l >> r; 

			int res = -inf;

			for (int mask = 0; mask < (1 << k); ++mask) {
				maximize(res, st[mask].get_max(1, 1, n, l, r) - st[mask].get_min(1, 1, n, l, r));
			}

			cout << res << '\n'; 
		}
	}

}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}