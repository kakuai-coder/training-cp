// tinhnopro 
#include <bits/stdc++.h>
using namespace std; 

#define hanh "QuerySum"

using i64 = long long;

const int maxN = 1e5 + 5; 
const int mod = 1e9 + 7; 

int n, q, a[maxN], lazy[4 * maxN];
pair<int, int> st[4 * maxN];

int add(int a, int b) {
	a += b;
	if (a >= mod) a -= mod; 
	return a; 
}

int sub(int a, int b) {
	a -= b; 
	if (a < 0) a += mod; 
	return a; 
}

int mul(int a, int b) {
	i64 x = 1LL * a * b; 
	return x % mod; 
}

int sum(int n) {
	i64 x = 1LL * n * (n + 1) / 2; 
	return x % mod;
}

int sum(int l, int r) {
	return sub(sum(r), sum(l - 1));
}

int fixmod(int x) {
	if (x < 0) x += mod; 
	return x;
}

void down(int id, int l, int r, int mid) {
	if (!lazy[id]) return ; 

	lazy[id << 1] = add(lazy[id << 1], lazy[id]); 
	lazy[id << 1 | 1] = add(lazy[id << 1 | 1], lazy[id]);

	st[id << 1].first = add(st[id << 1].first, mul(mid - l + 1, lazy[id]));
	st[id << 1 | 1].first = add(st[id << 1 | 1].first, mul(r - mid, lazy[id]));

	st[id << 1].second = add(st[id << 1].second, mul(sum(l, mid), lazy[id]));
	st[id << 1 | 1].second = add(st[id << 1 | 1].second, mul(sum(mid + 1, r), lazy[id]));
	

	lazy[id] = 0;
}

void update(int id, int l, int r, int u, int v, int val) {
	if (l > v || r < u) return ; 
	if (u <= l && r <= v) {
		st[id].first = add(st[id].first, val);
		st[id].second = add(st[id].second, mul(sum(l, r), val));
		lazy[id] = add(lazy[id], val);
		return ;  
	}

	int mid = (l + r) >> 1; 
	down(id, l, r, mid);

	update(id << 1, l, mid, u, v, val); 
	update(id << 1 | 1, mid + 1, r, u, v, val); 

	st[id].first = add(st[id << 1].first, st[id << 1 | 1].first);
	st[id].second = add(st[id << 1].second, st[id << 1 | 1].second);
}

int query1(int id, int l, int r, int u, int v) {
	if (l > v || r < u) return 0; 
	if (u <= l && r <= v) {
		return st[id].first;
	}

	int mid = (l + r) >> 1; 
	down(id, l, r, mid);

	return add(query1(id << 1, l, mid, u, v), query1(id << 1 | 1, mid + 1, r, u, v));
}

int query2(int id, int l, int r, int u, int v) {
	if (l > v || r < u) return 0; 
	if (u <= l && r <= v) {
		return st[id].second; 
	}

	int mid = (l + r) >> 1; 
	down(id, l, r, mid);

	return add(query2(id << 1, l, mid, u, v), query2(id << 1 | 1, mid + 1, r, u, v));
}

void Main() {
	cin >> n; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
		a[i] = fixmod(a[i]);
	}

	cin >> q; 

	while (q--) {
		int type, l, r; 
		cin >> type >> l >> r; 

		if (type == 1) {
			int val; cin >> val; 
			for (int i = l; i <= r; ++i) a[i] = add(a[i], val);

			for (int i = 1; i <= n; ++i) cout << a[i] << ' '; 
			cout << '\n';
		} else {
			int res = 0; 
			for (int i = l; i <= r; ++i) {
				res = add(res, a[i]);
			}

			cout << res << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); 
	
	if (fopen(hanh".inp", "r")) {
		freopen(hanh".inp", "r", stdin); 
		freopen(hanh".ans", "w", stdout);
	}

	int t = 1; 
	// cin >> t; 
	for (int i = 1; i <= t; ++i) {
		Main();
	}

	cerr << "\n[runtime]" << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";
	return 0; 
}