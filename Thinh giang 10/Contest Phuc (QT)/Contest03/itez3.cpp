// tinhnopro 
#include <bits/stdc++.h>
using namespace std; 

#define hanh "itez3"

using i64 = long long;

const int maxN = 2e5 + 5; 

int n, q; 
i64 a[maxN], st[4 * maxN]; 
pair<i64, int> lazy[4 * maxN]; 

void build(int id, int l, int r) {
	if (l == r) {
		st[id] = a[l]; 
		return ; 
	}

	int mid = (l + r) >> 1; 
	
	build(id << 1, l, mid); 
	build(id << 1 | 1, mid + 1, r); 

	st[id] = st[id << 1] + st[id << 1 | 1]; 
}

void down(int id, int l, int r, int mid) {
	if (!lazy[id].second) return ; 
	
	if (lazy[id].second == 2) {
		lazy[id << 1].second = 2; 
		lazy[id << 1 | 1].second = 2; 
		lazy[id << 1].first = lazy[id << 1 | 1].first = lazy[id].first;
		st[id << 1] = 1LL * (mid - l + 1) * lazy[id].first;
		st[id << 1 | 1] = 1LL * (r - mid) * lazy[id].first;
	} else {
		lazy[id << 1].second = (lazy[id << 1].second == 0 ? 1 : lazy[id << 1].second); 
		lazy[id << 1 | 1].second = (lazy[id << 1 | 1].second == 0 ? 1 : lazy[id << 1 | 1].second); 
		
		lazy[id << 1].first += lazy[id].first;
		lazy[id << 1 | 1].first += lazy[id].first;

		st[id << 1] += 1LL * (mid - l + 1) * lazy[id].first;
		st[id << 1 | 1] += 1LL * (r - mid) * lazy[id].first;
	}

	lazy[id] = {0LL, 0}; 
}

void update(int id, int l, int r, int u, int v, int val, int type) {
	if (l > v || r < u) return ; 
	if (u <= l && r <= v) {
		if (type == 1) {
			st[id] += 1LL * (r - l + 1) * val; 
			lazy[id].second = (lazy[id].second == 0 ? 1 : lazy[id].second); 
			lazy[id].first += val; 
		} else {
			st[id] = 1LL * (r - l + 1) * val; 
			lazy[id].first = val; 
			lazy[id].second = 2; 
		}
		return ; 
	}

	int mid = (l + r) >> 1; 
	down(id, l, r, mid);

	update(id << 1, l, mid, u, v, val, type); 
	update(id << 1 | 1, mid + 1, r, u, v, val, type); 

	st[id] = st[id << 1] + st[id << 1 | 1];
}

i64 query(int id, int l, int r, int u, int v) {
	if (l > v || r < u) return 0; 
	if (u <= l && r <= v) return st[id]; 

	int mid = (l + r) >> 1; 
	down(id, l, r, mid); 

	return query(id << 1, l, mid, u, v) + query(id << 1 | 1, mid + 1, r, u, v);
}

void Main() {
	cin >> n >> q; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	build(1, 1, n); 

	while (q--) {
		int type, a, b; 
		cin >> type >> a >> b; 

		if (type == 3) {
			cout << query(1, 1, n, a, b) << '\n';
		} else {
			int x; cin >> x; 
			update(1, 1, n, a, b, x, type);
		}
	}
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); 
	
	if (fopen(hanh".inp", "r")) {
		freopen(hanh".inp", "r", stdin); 
		freopen(hanh".out", "w", stdout);
	}

	int t = 1; 
	// cin >> t; 
	for (int i = 1; i <= t; ++i) {
		Main();
	}

	cerr << "\n[runtime]" << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";
	return 0; 
}