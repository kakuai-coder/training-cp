/*
	Author: tinhnopro
	created: 31.03.2025 18:42:01
*/
#include <bits/stdc++.h>

#define CHERRY "lexperm"

using namespace std;

using i64 = long long;

int n, k, s[20], used[20], s2[20];
i64 fact[20]; 

void solve() {
	int x;
	n = 1; 
	while (cin >> x) {
		s[n] = x; 
		n++; 
	}

	n--; n--; 
	k = s[n + 1];

	fact[1] = 1; 
	fact[0] = 1;


	for (int i = 2; i <= n; ++i) fact[i] = 1LL * fact[i - 1]  * i;  

	memset(used, 0, sizeof(used));
	
	i64 res = 0; 

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < s[i]; ++j) if (!used[j]) {
			res += fact[n - i]; 
		}
		used[s[i]] = 1;
	}

	cout << res + 1 << '\n';
	
	memset(used, 0, sizeof(used));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) if (!used[j]) {
			if (k <= fact[n - i]) {
				cout << j << ' ';
				used[j] = 1; 
				break; 
			} else {
				k -= fact[n - i]; 
			}
		}
	}

	// for (int i = 1; i <= n; ++i) cout << s2[i];
	
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