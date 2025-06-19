/*
	Author: tinhnopro
	created: 01.04.2025 13:06:20
*/
#include <bits/stdc++.h>

#define CHERRY "combin"

using namespace std;

using i64 = long long;

const i64 inf = (i64) 1e18 + 11; 
const int maxN = 2009;

int n, k; 
i64 m, c[maxN][maxN];

void solve() {
	cin >> n >> k >> m; 
	
	for (int i = 0; i <= n; ++i) {
		c[i][0] = 1; 
		for (int j = 1; j <= i; ++j) {
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
			if (c[i][j] > inf) c[i][j] = inf; 
		}
	}

	if (c[n][k] < m) {
		cout << -1; 
		return ;
	}

	// cout << c[n][k] << '\n';

	int last = 0;

	for (int i = 1; i <= k; ++i) {
		for (int j = last + 1; j <= n; ++j) {
			if (m > c[n - j][k - i]) {
				m -= c[n - j][k - i];
			} else {
				cout << j << ' '; 
				last = j; 
				break;
			}
		}
	}
	
	
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