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


int32_t main() {
	cin.tie(0)->sync_with_stdio(false);
	if (fopen(TASK ".inp", "r")) {
		freopen(TASK ".inp", "r", stdin);
		freopen(TASK ".out", "w", stdout);
	}

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> a(n);
		for (auto &x : a) cin >> x;
		int sum = 0, cnt = 0;
		for (auto &x : a) {
			sum += x;
			int sqrt_sum = sqrt(sum);
			if (sqrt_sum * sqrt_sum == sum && sqrt_sum & 1) cnt++;
		}

		cout << cnt << '\n';
	}
}

