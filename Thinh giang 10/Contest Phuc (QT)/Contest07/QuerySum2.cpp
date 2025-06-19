/*
	Author: tinhnopro
	created: 27.02.2025 09:19:26
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif // LOCAL

#define TASK "QuerySum2"

using namespace std;

using i64 = long long;

const int maxN = 1e5 + 5;

int n, q, a[maxN];
i64 bit[maxN];

void upd(int u, int val) {
	for (; u <= n; u += u & -u) bit[u] += val;
}

i64 query(int u) {
	i64 res = 0; 

	for (; u; u -= u & -u) res += bit[u]; 

	return res;
}

i64 queryRange(int l, int r) {
	return query(r) - query(l - 1); 
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
		upd(i, a[i]);
	}

	while (q--) {
		int type, u, v; 
		cin >> type >> u >> v;

		if (type == 1) {
			upd(u, v); 
		} else {
			cout << queryRange(u, v) << '\n';
		}
	}
}