/*
	Author: tinhnopro
	created: 27.03.2025 09:12:55
*/
#include <bits/stdc++.h>

#define CHERRY "Bowling"

using namespace std;

using i64 = long long;

const int maxN = 2e5 + 7; 
const i64 INF = (i64) 1e18 + 5; 

int n, r; 
i64 a[maxN], dp[maxN]; 

void solve() {
	cin >> n >> r; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
	}

	for (int i = 1; i <= n; ++i) {
		a[i] += a[i - 1];
	}

	if (r == n) {
		cout << a[n]; 
		return ;
	}

	memset(dp, -0x3f, sizeof(dp)); 

	i64 last = 0; 

	for (int i = 0; i <= r; ++i) {
		dp[i] = 0;
	}

	i64 res = -INF; 

	for (int i = r + 1; i < n; ++i) {
		dp[i] = a[i] + last;
		res = max(res, dp[i]);
		dp[i] = max(dp[i], dp[i - 1]);  

		if (i - 2 * r > 0) {
			last = max(last, dp[i - 2 * r] - a[i - 2 * r]);
		}
	}

	for (int j = n - r; j; --j) {
		dp[n] = max(dp[n], dp[j - 1] + a[n] - a[j - 1]);
	}
	res = max(res, dp[n]);
	dp[n] = max(dp[n], dp[n - 1]);

	cout << res; 
	
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