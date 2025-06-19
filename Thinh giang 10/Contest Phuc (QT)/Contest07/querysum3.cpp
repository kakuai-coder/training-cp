/*
	Author: tinhnopro
	created: 27.02.2025 09:53:53
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif // LOCAL

#define TASK "querysum3"

using namespace std;

using i64 = long long;
#define int long long

const int maxN = 1e5 + 5; 

int n, q; 
int a[maxN];
i64 seg[4 * maxN], lazy[4 * maxN]; 

#define Left(id) ((id) << 1)
#define Right(id) ((id) << 1 | 1)

void build(int id, int l, int r) {
	if (l == r) {
		seg[id] = a[l]; 
		lazy[id] = 0; 
		return ; 
	}

	int mid = (l + r) >> 1; 

	build(Left(id), l, mid); 
	build(Right(id), mid + 1, r); 

	seg[id] = seg[Left(id)] + seg[Right(id)];
}

void down(int id, int l, int r) {
	if (!lazy[id]) return ; 

	int mid = (l + r) >> 1; 

	seg[Left(id)] += 1LL * lazy[id] * (mid - l + 1); 
	seg[Right(id)] += 1LL * lazy[id] * (r - mid);

	lazy[Left(id)] += lazy[id]; 
	lazy[Right(id)] += lazy[id]; 

	lazy[id] = 0; 
}

void update(int id, int l, int r, int u, int v, int val) {
	if (l > v || r < u) return ; 
	if (u <= l && r <= v) {
		seg[id] += 1LL * val * (r - l + 1);
		lazy[id] += val; 

		return ; 
	}

	int mid = (l + r) >> 1; 

	down(id, l, r);
	update(Left(id), l, mid, u, v, val); 
	update(Right(id), mid + 1, r, u, v, val); 

	seg[id] = seg[Left(id)] + seg[Right(id)];
}

int query(int id, int l, int r, int u, int v) {
	if (l > v || r < u) return 0; 
	if (u <= l && r <= v) {
		return seg[id]; 
	}

	down(id, l, r); 

	int mid = (l + r) >> 1; 

	return query(Left(id), l, mid, u, v) + query(Right(id), mid + 1, r, u, v);
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (fopen(TASK".inp", "r")) {
		freopen(TASK".inp", "r", stdin);
		freopen(TASK".out", "w", stdout);
	}

	cin >> n >> q; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
	}

	build(1, 1, n);

	while (q--) {
		int type, x, y; 
		cin >> type >> x >> y;
		
		if (type == 1) {
			int val; cin >> val; 
			update(1, 1, n, x, y, val);
		} else {
			cout << query(1, 1, n, x, y) << '\n';
		}
	}
}