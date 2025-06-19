/*
	Author: tinhnopro
	created: 04.01.2025 08:47:50
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
	int n, d; 
	cin >> n >> d; 
	vector<int> ans  = {1};
	if (d == 5) ans.push_back(5); 
	if (d == 7 || n >= 3) ans.push_back(7); 
	if (d % 3 == 0 || n >= 3) ans.push_back(3); 
	if (d % 9 == 0 || (d % 3 == 0 && n >= 3) || n >= 6) ans.push_back(9); 
	sort(ans.begin(), ans.end()); 
	
	for (int x : ans) cout << x << ' '; 
	cout << '\n'; 
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