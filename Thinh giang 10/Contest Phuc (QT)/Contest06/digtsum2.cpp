/*
	Author: tinhnopro
	created: 01.04.2025 15:00:29
*/
#include <bits/stdc++.h>

#define CHERRY "digtsum2"

using namespace std;

using i64 = long long;

const int mod = 1e9 + 7; 
const int maxN = 1e4 + 5; 

string k; 
int d, dp[maxN][105]; 

void selfAdd(int &a, int b) {
	a += b; 
	if (a >= mod) a -= mod; 
}

int calc(const string &s, int i, int sum, bool tight) {
	if (i < 0) {
		return sum == 0; 
	}

	if (!tight && ~dp[i][sum]) return dp[i][sum]; 

	int di = s[i] - '0'; 

	int max_digt = tight ? di : 9; 

	// cerr << max_digt << '\n';

	int cur = 0; 

	for (int j = 0; j <= max_digt; ++j) {
		
		bool new_tight = tight && (j == max_digt); 
		selfAdd(cur, calc(s, i - 1, (sum + j) % d, new_tight));
	}

	if (!tight) return dp[i][sum] = cur; 
	return cur; 
}

void solve() {

	cin >> k >> d;

	reverse(k.begin(), k.end());
	memset(dp, -1, sizeof(dp));
	
	cout << (calc(k, k.size() - 1, 0, 1) - 1 + mod) % mod;
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