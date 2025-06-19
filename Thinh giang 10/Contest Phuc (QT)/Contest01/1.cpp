/*
	Author: tinhnopro
	created: 12.01.2025 20:22:48
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif // LOCAL

#define TASK ""

using namespace std;

using i64 = long long;

i64 n, m, l, r; 

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (fopen(TASK".inp", "r")) {
		freopen(TASK".inp", "r", stdin);
		freopen(TASK".out", "w", stdout);
	}

	cin >> n >> m >> l >> r; 

	/*
		a % b [l, r]
		b [l + 1, n]
		
	*/

	i64 res = 0; 

	for (i64 b = l + 1; b <= n; ++b) {
		res += (m / b) * (min(r, b - 1) - l + 1); 
		res += max(0LL, min(r, m % b) - l + 1);
	}

	if (l == 0)
		res -= n - l; 

	cout << res; 
}
