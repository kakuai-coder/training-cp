/*
	Author: tinhnopro
	created: 25.03.2025 14:30:51
*/
#include <bits/stdc++.h>

#define CHERRY "3"

using namespace std;

using i64 = long long;

const int MOD = 1e9 + 7; 
 
void add(int& a, int b) {
	a += b; 
	if (a >= MOD) a -= MOD; 
}

int mul(int a, int b) {
	i64 x = 1LL * a * b; 
	return x % MOD;
}

int n, t; 

namespace Sub1 {

	int a[20], res = 0;  

	bool check() {
		int lsum = a[1], rsum = 0; 
		for (int i = 2, j = n; i <= n; ++i, --j) {
			lsum += a[i];
			rsum += a[j]; 

			if (lsum <= rsum) return false; 
		}
		++res; 
		return true;
	}

	void backtrack(int idx) {
		if (idx == n + 1) {
			check(); 
			return ; 
		}

		for (int val = a[idx - 1]; val <= n; ++val) {
			a[idx] = val; 
			backtrack(idx + 1); 
		}
	}

	void Main() {
		a[0] = 1; 
		backtrack(1); 

		cout << res;
	}

	bool run() {
		// cerr << t << ' ' << n << '\n';
		if (t > 0 || n > 15) return false; 
		return Main(), true;
	}
}

namespace Sub23 {

	const int maxN = 110; 

	int dp[maxN][maxN][maxN], c[maxN]; 

	void Main() {
		for (int i = 3, j = n; i <= n; ++i, --j) {
			if (i > j) break; 
			c[i] = c[j] = i - 2; 

		}

		dp[n + 1][0][0] = 1; 

		for (int i = n; i >= 2; --i) {
			for (int sum = 0; sum < n; ++sum) {
				for (int b = 0; b <= n; ++b) {
					// cerr << i << " " << sum << " " << b << '\n';
					for (int t = 0; t * c[i] <= b && t <= sum; ++t) {
						add(dp[i][sum][b], dp[i + 1][sum - t][b - c[i] * t]);
					}

					// cout << dp[i][sum][b] << '\n';
				}
			}
		}


		int res = 0; 

		for (int sum = 0; sum <= n - 1; ++sum) {
			for (int b = 0; b <= n - sum - 1; ++b) {
				add(res, mul(dp[2][sum][b], n - sum - b));
			}
		}

		cout << res; 
	}

	bool run() {
		if (n > 100) return false; 
		return Main(), true;
	}
}

namespace Sub4 {

	const int maxN = 5e3 + 5; 
	int dp[maxN][maxN], c[maxN]; 

	void Main() {
		memset(dp, 0, sizeof(dp));
		for (int i = 2, j = n; i <= j; ++i, --j) {
			c[j] = i;
			c[i] = i - 1; 
		}

		// for (int i = 2; i <= n; ++i) cout << c[i] << ' '; 
		// cout << '\n';

		dp[n + 1][0] = 1;
		
		for (int i = n + 1; i > 2; --i) {
			for (int sum = 0; sum <= n; ++sum) {
				if (dp[i][sum] == 0) continue;
				for (int t = 0; t * c[i - 1] <= n - sum; ++t) {
					add(dp[i - 1][sum + t * c[i - 1]], dp[i][sum]);
				}
			}
		}

		int res = 0; 
		for (int sum = 0; sum <= n; ++sum) {
			add(res, mul(dp[2][sum], n - sum));
		}

		cout << res << '\n'; 
	}

	bool run() {

		return Main(), true;
	}
}

namespace Sub5 {

	const int maxN = 5e3 + 5; 
	int dp[maxN], c[maxN]; 

	void Main() {
		memset(dp, 0, sizeof(dp));
		for (int i = 2, j = n; i <= j; ++i, --j) {
			c[j] = i;
			c[i] = i - 1; 
		}

		// for (int i = 2; i <= n; ++i) cout << c[i] << ' '; 
		// cout << '\n';

		dp[0] = 1;
		
		for (int i = n; i >= 2; --i) {
			for (int j = c[i]; j <= n; ++j) {
				add(dp[j], dp[j - c[i]]);
				// cout << dp[i][j] << '\n';
			}

		}

		int res = 0; 	
		for (int sum = 0; sum <= n; ++sum) {
			add(res, mul(dp[sum], n - sum));
		}

		cout << res << '\n'; 
	}

	bool run() {

		return Main(), true;
	}
}



void Main() {
	cin >> t; 
	while (t--) {
		cin >> n;
		// if (Sub1::run()) continue;
		// if (Sub23::run()) continue;
		// if (Sub4::run()) continue;
		if (Sub5::run()) continue;
	}	
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
		Main();
	}

	cerr << "[runtime] " << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";

	return 0; 
}