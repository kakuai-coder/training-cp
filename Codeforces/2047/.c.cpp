/**
 * author: tinhnopro (tinh nop)
 * created: 2024-12-05
**/
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 0
#endif // LOCAL

#include <bits/stdc++.h>

#define TASK ""

using namespace std;

const int maxN = 1e5 + 11;

int n, a[maxN][2];

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i][0];
	for (int i = 1; i <= n; ++i) cin >> a[i][1];

	int64_t sum = 0;
	for (int i = 1; i <= n; ++i) sum += max(a[i][0], a[i][1]);
	int64_t ans = -1e18;
	for (int i = 1; i <= n; ++i) ans = max(ans, sum + min(a[i][0], a[i][1]));

	cout << ans << '\n';
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(false);
	if (fopen(TASK ".inp", "r")) {
		freopen(TASK ".inp", "r", stdin);
		freopen(TASK ".out", "w", stdout);
	}

	int t; cin >> t;
	while (t--) {
		solve();
	}
}

