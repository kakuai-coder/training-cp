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

using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> a(n);
	int64_t sum_odd = 0, sum_even = 0, cnt = 0;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		if (i & 1) {
			sum_odd += a[i];
			cnt++;
		} else sum_even += a[i];
	}

	if (sum_odd % cnt != 0 || sum_even % (n - cnt) != 0) {
		cout << "NO\n";
		return ;
	}

	if (sum_odd / cnt == sum_even / (n - cnt)) {
		cout << "YES\n";
	} else cout << "NO\n";
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	while (t--) {
		solve();
	}
}

