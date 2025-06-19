/*
	Author: tinhnopro
	created: 01.04.2025 14:01:06
*/
#include <bits/stdc++.h>

#define CHERRY "digtsum"

using namespace std;

using i64 = long long;

int n, a[20];
i64 dp[20][9 * 20];

i64 calc(int i, int sum, bool tight) {
	if (i < 0) {
		return sum; 
	}
 
	if (!tight && ~dp[i][sum]) return dp[i][sum]; 
	
	int max_digt = tight ? a[i] : 9;

	i64 cur = 0; 

	for (int j = 0; j <= max_digt; ++j) {
		bool new_tight = tight && (j == max_digt);
		cur += calc(i - 1, sum + j, new_tight); 
	}

	if (!tight) return dp[i][sum] = cur; 
	return cur; 
}

i64 solve(i64 x) {
	n = 0; 
	while (x) {
		a[n++] = x % 10; 
		x /= 10; 
	}

	// for (int i = 0; i < n; ++i) cout << a[i] << '\n';


	return calc(n - 1, 0, 1); 
}


void solve() {
	i64 l, r; 
	cin >> l >> r; 

	memset(dp, -1, sizeof(dp));

	cout << solve(r) - solve(l - 1); 
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