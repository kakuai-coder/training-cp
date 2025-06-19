/*
	Author: tinhnopro
	created: 31.03.2025 21:16:12
*/
#include <bits/stdc++.h>

#define CHERRY "lexcatalan"

using namespace std;

using i64 = long long;


int n, k, c[50], c2[50];
i64 dp[50][50], cnt = 0;

i64 calc(int i, int j) {
	if (j < 0) return 0; 
	
	i64 &cur = dp[i][j]; 

	if (~cur) return cur; 

	if (i == 1 && j != 0) return cur = 0;
	if (i == n) return cur = (j == 0); 

	cur = 0; 

	cur += calc(i + 1, j + 1); 
	if (j > 0) cur += calc(i + 1, j - 1); 
	
	return cur; 
}

void order_to_config() {
	c2[1] = 0; c2[2] = 1; 
	for (int i = 3; i <= n; ++i) {
		if (c2[i - 1] == 0) {
			c2[i] = 1; 
			continue;
		}

		if (k > calc(i, c2[i - 1] - 1)) {
			k -= calc(i, c2[i - 1] - 1);
			c2[i] = c2[i - 1] + 1; 
		} else {
			c2[i] = c2[i - 1] - 1; 
		}
	}

	for (int i = 1; i <= n; ++i) cout << c2[i] << ' ';
}

void config_to_order() {

	for (int i = 2; i <= n; ++i) {
		for (int j = 0; j < c[i]; ++j) {
			if (abs(c[i - 1] - j) == 1) cnt += calc(i, j);
		}
	}

	cout << cnt + 1 << '\n';
}



void solve() {
	cin >> n; 
	n = 2 * n + 1; 
	for (int i = 1; i <= n; ++i) cin >> c[i]; 
	cin >> k; 

	memset(dp, -1, sizeof(dp));
	calc(1, 0);
	
	config_to_order(); 
	order_to_config(); 


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