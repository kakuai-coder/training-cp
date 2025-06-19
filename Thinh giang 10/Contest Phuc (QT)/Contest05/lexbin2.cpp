/*
	Author: tinhnopro
	created: 31.03.2025 17:40:31
*/
#include <bits/stdc++.h>

#define CHERRY "lexbin2"

using namespace std;

using i64 = long long;

int n; 
i64 k, dp[100][2]; 
char s[100], s2[100];

void solve() {
	cin >> n; 
	for (int i = 1; i <= n; ++i) cin >> s[i]; 
	cin >> k; 

	dp[1][0] = dp[1][1] = 1; 

	for (int i = 2; i <= n; ++i) {
		dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
		dp[i][1] = dp[i - 1][0];
	}

	i64 res = 0; 

	for (int i = 1; i <= n; ++i) {
		if (s[i] == '1') {
			res += dp[n - i + 1][0];
		}
	}

	cout << res + 1 << '\n'; 

	for (int i = 1; i <= n; ++i) {
		s2[i] = '0'; 
	}

	for (int i = 1; i <= n; ++i) {
		if (k > dp[n - i + 1][0]) {
			s2[i] = '1'; 
			k -= dp[n - i + 1][0]; 
		} 
	}

	for (int i = 1; i <= n; ++i) cout << s2[i];

	return void(cout << '\n');
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	if (fopen(CHERRY".inp", "r")) {
		freopen(CHERRY".inp", "r", stdin);
		freopen(CHERRY".out", "w", stdout);
	}

	int t = 1; 
	// cin >> t;

	for (int i = 1; i <= t; ++i) {
		cerr << "Case #" << i << '\n';
		solve();
	}

	cerr << "[runtime] " << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";

	return 0; 
}