/*
	Author: tinhnopro
	created: 27.02.2025 09:27:53
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif // LOCAL

#define TASK "rangeupdatequery"
#define int long long 

using namespace std;

using i64 = long long;

const int maxN = 2e5 + 5; 

int n, q, a[maxN], bit[maxN];

void update(int u, int val) {
	for (; u <= n + 1; u += u & -u) bit[u] += val; 
}

void updateRange(int l, int r, int val) {
	update(l, val); 
	update(r + 1, -val);
}

int query(int u) {
	int res = 0; 
	for (; u; u -= u & -u) res += bit[u]; 

	return res; 
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
		update(i, a[i] - a[i - 1]);
	}

	while (q--) {
		int type; cin >> type;

		if (type == 1) {
			int a, b, val; 
			cin >> a >> b >> val; 
			updateRange(a, b, val);
		} else {
			int k; 
			cin >> k; 
			cout << query(k) << '\n';
		}
	}
}