/*
	Author: tinhnopro
	created: 31.03.2025 23:05:59
*/
#include <bits/stdc++.h>

#define CHERRY "lexbracket"

using namespace std;

using i64 = long long;

const long long INF = 9223372036854775807;
int n;
i64 dp[3009][3009]; 
i64 k;

long long mul(long long a, long long b) {
	if (a == 0 || b == 0) return 0;
	if (a > INF / b) return INF;
	return a * b;
}

long long add(long long a, long long b) {
	if (a > INF - b) return INF;
	return a + b;
}

i64 calc(int i, int j) {
	if (i > n) return j == 0; 
	
	i64 &cur = dp[i][j];
	if (~cur) return cur; 

	cur = 0; 
	cur = add(cur, calc(i + 1, j + 1)); 
	if (j > 0) cur = add(cur, calc(i + 1, j - 1));

	return cur; 
}

void kth() { 

	int diff = 0;
	for (int i = 1; i <= n; ++i) {
		if (k <= calc(i + 1, diff + 1)) {
			cout << '(';
			++diff;
		} else {
			cout << ')';
			k -= calc(i + 1, diff + 1);
			--diff;
		}
	}
}	

void solve() {
	cin >> n >> k;

	memset(dp, -1, sizeof(dp));
	// cout << calc(1, 0); 

	kth();

	
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