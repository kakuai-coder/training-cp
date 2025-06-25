/*
	Author: kakuai
	created: 2025.06.21 08:06:44
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

int n, q, nxtL[maxN], nxtR[maxN];

struct DisjointSet {
	int mx[maxN], mi[maxN],lab[maxN];

	DisjointSet() {
		memset(lab, 0, sizeof(lab)); 
		memset(mx, 0, sizeof(mx)); 
		memset(mi, 0, sizeof(mi));
	}

	void init(int i) {
		lab[i] = -1; 
		mx[i] = i; 
		mi[i] = i; 
	}

	int find_par(int u) {
		if (lab[u] == 0) init(u);
		return lab[u] < 0 ? u : lab[u] = find_par(lab[u]);
	}

	void merge(int u, int v) {
		u = find_par(u); 
		v = find_par(v); 

		if (u == v) return ; 

		if (lab[u] > lab[v]) swap(u, v); 
		lab[u] += lab[v]; 
		lab[v] = u; 

		maximize(mx[u], mx[v]);
		minimize(mi[u], mi[v]);
	}

	int jumpR(int x) {
		return mx[find_par(x)];
	}

	int jumpL(int x) {
		return mi[find_par(x)];
	}
} dsu;

struct SegmentTreeL {
	int st[4 * maxN];

	SegmentTreeL() {
		memset(st, 0x3f, sizeof(st));
	}

	void update(int id, int l, int r, int pos, int val) {
		if (l > pos || pos > r) return ; 
		if (l == r) {
			minimize(st[id], val);
			return ; 
		}

		int mid = (l + r) >> 1; 

		update(id << 1, l, mid, pos, val); 
		update(id << 1 | 1, mid + 1, r, pos, val); 

		st[id] = min(st[id << 1], st[id << 1 | 1]);
	}

	int query(int id, int l, int r, int u, int v) {
		if (l > v || r < u) return inf;
		if (u <= l && r <= v) return st[id]; 

		int mid = (l + r) >> 1; 

		return min(query(id << 1, l, mid, u, v), query(id << 1 | 1, mid + 1, r, u, v));
	}
} stL;

struct SegmentTreeR {
	int st[4 * maxN];

	SegmentTreeR() {
		memset(st, -0x3f, sizeof(st));
	}

	void update(int id, int l, int r, int pos, int val) {
		if (l > pos || pos > r) return ; 
		if (l == r) {
			maximize(st[id], val);
			return ; 
		}

		int mid = (l + r) >> 1; 

		update(id << 1, l, mid, pos, val); 
		update(id << 1 | 1, mid + 1, r, pos, val); 

		st[id] = max(st[id << 1], st[id << 1 | 1]);
	}

	int query(int id, int l, int r, int u, int v) {
		if (l > v || r < u) return -inf;
		if (u <= l && r <= v) return st[id]; 

		int mid = (l + r) >> 1; 

		return max(query(id << 1, l, mid, u, v), query(id << 1 | 1, mid + 1, r, u, v));
	}
} stR;

void kakuai() {
	cin >> n >> q; 

	for (int i = 1; i <= n; ++i) {
		nxtL[i] = 1e9; 
		nxtR[i] = -1e9;
	}

	while (q--) {
		int t; cin >> t; 
		if (t == 0) {
			int l, r, x; 
			cin >> l >> r >> x; 
			if(x == 0) {
				for (int i = dsu.jumpR(l); i < r; i = dsu.jumpR(i)) {
					dsu.merge(i, i + 1);
				}
			} else {
				minimize(nxtL[l], r);
				maximize(nxtR[r], l);

				stL.update(1, 1, n, l, nxtL[l]);
				stR.update(1, 1, n, r, nxtR[r]);
			}
		} else {
			int x; cin >> x;  

			if (dsu.lab[x] != 0) {
				cout << "NO\n"; 
				continue;
			}

			int l = x, r = x; 
			
			if (dsu.lab[x - 1] != 0) {
				l = dsu.jumpL(x - 1);
			}

			if (dsu.lab[x + 1] != 0) {
				r = dsu.jumpR(x + 1);
			}

			if (dsu.lab[x - 1] != 0) {
				int idx = stL.query(1, 1, n, l, x);

				if (idx <= r) {
					cout << "YES\n"; 
					continue;
				}
			}

			if (dsu.lab[x + 1] != 0) {
				int idx = stR.query(1, 1, n, x, r);
				if (idx >= l) {
					cout << "YES\n";
					continue;
				} 
			}


			cout << "N/A\n";
		}
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "a"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}