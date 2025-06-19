/*
	Author: tinhnopro
	created: 04.01.2025 08:34:18
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif // LOCAL

#define TASK ""

using namespace std;

using i64 = long long;

void solve() {
	i64 n; 
	cin >> n; 
	
	i64 ans = 1; 

	while (n > 3) {
		ans *= 2; 
		n /= 4; 
	}

	cout << ans << '\n';
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (fopen(TASK".inp", "r")) {
		freopen(TASK".inp", "r", stdin);
		freopen(TASK".out", "w", stdout);
	}

	int t; 
	cin >> t; 
	while (t--) {
		solve(); 
	}
}