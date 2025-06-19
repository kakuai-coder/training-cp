/*
	Author: tinhnopro
	created: 02.04.2025 00:09:35
*/
#include <bits/stdc++.h>

#define CHERRY "next"

using namespace std;

using i64 = long long;

const i64 inf = (i64) 1e15; 
const int maxN = 52; 

i64 x, k, c[maxN][maxN]; 

void solve() {
	for (int i = 0; i < maxN; ++i) {
		c[i][0] = 1; 
		for (int j = 1; j <= i; ++j) {
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
			if (c[i][j] > inf) c[i][j] = inf + 1; 
		}
	}

	int t; cin >> t; 
	while (t--) {
		cin >> x >> k; 

		int c_bit = __builtin_popcountll(x);

		i64 n = 0, n_bit = c_bit; 
		for (int i = 0; i < maxN; ++i) {
			if ((x >> (maxN - i - 1)) & 1) {
				n += c[maxN - i - 1][n_bit];
				n_bit--;	
			}
		}
		n++;

		if (n + k > c[maxN - 1][c_bit]) {
			cout << -1 << '\n';
			continue;
		}

		// cout << n << ' ';

		n += k; 
		i64 res = 0; 
		for (int i = 0; i < maxN; ++i) {
			i64 x = c[maxN - i - 1][c_bit];
			if (n > x) {
				n -= x; 
				c_bit--; 
				res = res | (1LL << (maxN - i - 1));
			}
		}

		if (res > inf) {
			cout << -1 << '\n';
		} else cout << res << '\n';
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