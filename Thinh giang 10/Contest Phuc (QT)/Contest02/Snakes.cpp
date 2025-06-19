/*
	Author: tinhnopro
	created: 26.03.2025 02:00:19
*/
#include <bits/stdc++.h>

#define CHERRY "Snakes"

using namespace std;

using i64 = long long;

const int maxN = 505;

int n, k, dp[maxN][maxN], a[maxN];

void solve() {
	cin >> n >> k; 

	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
	}

	memset(dp, 0x3f, sizeof(dp)); 
	dp[0][0] = 0; 

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= k + 1; ++j) {
			int sum = 0; 
			int cnt = 0; 
			int mx = 0;
			for (int t = i; t >= 1; --t) {
				sum += a[t];
				mx = max(mx, a[t]);
				cnt++; 
				dp[i][j] = min(dp[i][j], dp[t - 1][j - 1] + mx * cnt - sum);
			}
		}
	}

	int ans = 1e9; 

	for (int i = 1; i <= k + 1; ++i) {
		ans = min(ans, dp[n][i]);
	}

	cout << ans; 

	return void(cout << '\n');
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (fopen(CHERRY".inp", "r")) {
		freopen(CHERRY".inp", "r", stdin);
		freopen(CHERRY".out", "w", stdout);
	}

	unsigned testcases = 1; 
	// cin >> testcases;

	for (unsigned test = 1; test <= testcases; ++test) {
		cerr << "Case #" << test << '\n';
		solve();
	}

	cerr << "[runtime] " << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";

	return 0; 
}