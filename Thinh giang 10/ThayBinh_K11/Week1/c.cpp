/*
	Author: tinhnopro
	created: 04.04.2025 23:51:12
*/
#include <bits/stdc++.h>

#define CHERRY "c"

using namespace std;

using i64 = long long;

const int maxN = 1e5 + 5; 

int w, m, n, a[maxN], b[maxN]; 

int calc(int L, int *a, int sz) {

	if (a[1] > L) return 1e9;
	int sum = a[1], cnt = 1; 

	for (int i = 2; i <= sz; ++i) {
		if (sum + a[i] + 1 <= L) {
			sum += a[i] + 1;
		} else if (a[i] <= L) {
			cnt++; 
			sum = a[i];
		} else return 1e9;
	}

	return cnt; 
}

int g(int L) {
	return max(calc(L, a, m), calc(w - L, b, n));
}

void solve() {
	
	cin >> w >> m >> n; 

	for (int i = 1; i <= m; ++i) cin >> a[i]; 

	for (int i = 1; i <= n; ++i) cin >> b[i]; 

	int lo = 0, hi = w;

	while (lo < hi) {
		int mid = (lo + hi) >> 1; 
		if (g(mid) > g(mid + 1)) lo = mid + 1; 
		else hi = mid; 
	}

	cout << g(hi);
	
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