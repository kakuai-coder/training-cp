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

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		vector<string> a(n);
		for (auto &x : a) cin >> x;

		int len = 0, cnt = 0, ans = 0;
		for (auto &x : a) {
			cnt++;
			len += x.size();
			if (len <= m) ans = max(ans, cnt);
			else break;
		}

		cout << ans << '\n';
	}
}

