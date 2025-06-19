/*
	Author: tinhnopro
	created: 2025.04.10 09:11:17
*/
#include <bits/stdc++.h>

#define int long long 

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________


const int maxN = 3e5 + 5;
const int maxA = 1e6 + 5; 

int n, q, a[maxN], d[maxA];

struct SegmentTree {
	i64 st[4 * maxN]; 

	SegmentTree() {
		memset(st, 0, sizeof(st));
	}

	void build(int id, int l, int r) {
		if (l == r) return void(st[id] = a[l]);

		int mid = (l + r) >> 1; 

		build(id << 1, l, mid); 
		build(id << 1 | 1, mid + 1, r); 

		st[id] = st[id << 1] + st[id << 1 | 1];
	}

	void update(int id, int l, int r, int pos, int val) {
		if (l > pos || r < pos) return ; 
		if (l == r) {
			st[id] = val;
			return ; 
		}

		int mid = (l + r) >> 1;  

		update(id << 1, l, mid, pos, val); 
		update(id << 1 | 1, mid + 1, r, pos, val); 

		st[id] = st[id << 1] + st[id << 1 | 1];
	}

	i64 query(int id, int l, int r, int u, int v) {
		if (l > v || r < u) return 0LL; 
		if (u <= l && r <= v) {
			return st[id]; 
		}

		int mid = (l + r) >> 1; 
		return query(id << 1, l, mid, u, v) + query(id << 1 | 1, mid + 1, r, u, v);
	}
};

struct Disjointset {
	int lab[maxN], mx[maxN], can_join[maxN];
	
	Disjointset() {
		memset(lab, 0, sizeof(lab)); 
		memset(mx, 0, sizeof(mx));
		memset(can_join, 0, sizeof(can_join));
	}

	void init(int n) {
		for (int i = 1; i <= n; ++i) {
			lab[i] = -1;
			mx[i] = i; 
			can_join[i] = 0;
		}
	}

	int find_par(int u) {
		return lab[u] < 0 ? u : lab[u] = find_par(lab[u]);
	}

	int sz(int u) {
		return -lab[find_par(u)];
	}

	int last(int u) {
		return mx[find_par(u)] + 1; 
	}

	bool can(int u) {
		return can_join[find_par(u)];
	}

	void join(int u, int v) {
		u = find_par(u); 
		v = find_par(v);
		if (u == v) return ;

		if (lab[u] > lab[v]) swap(u, v); 

		lab[u] += lab[v]; 
		lab[v] = u; 
		maximize(mx[u], mx[v]);
	}
};

SegmentTree seg;
Disjointset dsu;

void sieve() {
	for (int i = 1; i < maxA; ++i) {
		for (int j = 1; j < maxA / i; j++) d[i * j]++;  
	}
}

void update(int l, int r) {
	int idx = dsu.last(l); 
	while (idx <= r) {
		if (d[a[idx]] == a[idx]) {
			dsu.can_join[dsu.find_par(idx)] = 1; 
			if (idx - 1 > 0 && dsu.can(idx - 1)) dsu.join(idx - 1, idx);
			if (idx + 1 <= n && dsu.can(idx + 1)) dsu.join(idx + 1, idx);
		} else {
			seg.update(1, 1, n, idx, d[a[idx]]);
			a[idx] = d[a[idx]];
		}
		idx = dsu.last(idx);
	}
}

void tinhnop() {
	cin >> n >> q; 

	sieve();

	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	
	seg.build(1, 1, n); 
	dsu.init(n);

	while (q--) {
		int op, l, r; 
		cin >> op >> l >> r;
		
		if (op == 1) {
			update(l, r);
		} else {
			cout << seg.query(1, 1, n, l, r) << '\n';
		}
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry ""
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}