/*
	Author: tinhnopro
	created: 21.12.2024 09:57:57
*/
#include <bits/stdc++.h>

#ifdef LOCAL
// #include "debug.h"
#else
#define debug(...) 42
#endif // LOCAL

#define TASK "segtree_itmix"

using namespace std;

using i64 = long long;

const int maxN = 1e5 + 5; 
const int mod = 1e9 + 7; 

void mul(int &a, int b) {
	i64 s = 1LL * a * b; 
	a = s % mod; 
}

void add(int &a, int b) {
	a += b; 
	if (a >= mod) a -= mod; 
}

int n, q; 
int a[maxN];

struct Node {
	int val, mul, add; 

	Node() : val(0), mul(1), add(0) {}
	Node(int _val, int _mul, int _add) : val(_val), mul(_mul), add(_add) {}

	Node operator + (const Node& other) const {
		Node res = Node(); 
		res.val = val + other.val;
		res.val %= mod;  
		return res; 
	}
};

Node st[4 * maxN]; 

void build(int id, int l, int r) {
	if (l == r) {
		st[id].val = a[l]; 
		st[id].mul = 1; 
		st[id].add = 0; 
		return ;
	}

	int mid = (l + r) >> 1; 
	
	build(id << 1, l, mid); 
	build(id << 1 | 1, mid + 1, r); 

	st[id] = st[id << 1] + st[id << 1 | 1]; 
}

void down(const int& id, const int& l, const int& r, const int& mid) {
	if (st[id].add == 0 && st[id].mul == 1) return ; 
	
	// lazy add
	mul(st[id << 1].add, st[id].mul); 
	add(st[id << 1].add, st[id].add);

	mul(st[id << 1 | 1].add, st[id].mul); 
	add(st[id << 1 | 1].add, st[id].add);

	// lazy mul 
	mul(st[id << 1].mul, st[id].mul); 
	mul(st[id << 1 | 1].mul, st[id].mul);

	// segtree mul 
	mul(st[id << 1].val, st[id].mul); 
	mul(st[id << 1 | 1].val, st[id].mul); 

	// segtree add
	add(st[id << 1].val, 1LL * (mid - l + 1) * st[id].add % mod);
	add(st[id << 1 | 1].val, 1LL * (r - mid) * st[id].add % mod);

	st[id].mul = 1; 
	st[id].add = 0; 
}

void update(int id, int l, int r, int u, int v, int mu, int ad) {
	if (l > v || r < u) return ; 
	if (u <= l && r <= v) {
		mul(st[id].val, mu); 
		add(st[id].val, 1LL * (r - l + 1) * ad % mod);
		mul(st[id].mul, mu);
		mul(st[id].add, mu);
		add(st[id].add, ad);

		return ;
	}

	int mid = (l + r) >> 1; 
	down(id, l, r, mid); 

	update(id << 1, l, mid, u, v, mu, ad); 
	update(id << 1 | 1, mid + 1, r, u, v, mu, ad);

	st[id] = st[id << 1] + st[id << 1 | 1];
}

int query(int id, int l, int r, int u, int v) {
	if (l > v || r < u) return 0; 
	if (u <= l && r <= v) return st[id].val; 

	int mid = (l + r) >> 1; 
	down(id, l, r, mid);

	return (query(id << 1, l, mid, u, v) + query(id << 1 | 1, mid + 1, r, u, v)) % mod;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (fopen(TASK".inp", "r")) {
		freopen(TASK".inp", "r", stdin);
		freopen(TASK".out", "w", stdout);
	}
	
	cin >> n >> q; 

	for (int i = 1; i <= n; ++i) 
		cin >> a[i];
	
	build(1, 1, n); 

	while (q--) {
		int type, l, r, x; 
		cin >> type >> l >> r; 
		if (type == 4) {
			cout << query(1, 1, n, l, r) << '\n';
			continue;
		}
		cin >> x; 
		if (type == 1) update(1, 1, n, l, r, 1, x); 
		if (type == 2) update(1, 1, n, l, r, x, 0); 
		if (type == 3) update(1, 1, n, l, r, 0, x); 	

		// for (int i = 1; i <= n; ++i) cout << query(1, 1, n, i, i) << ' '; 
		// cout << '\n';
	}
}