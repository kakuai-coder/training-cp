/*
	Author: tinhnopro
	created: 2025.06.17 00:31:21
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 10
#endif // LOCAL

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

int m, n; 
char a[2009][2009];
int dp[2009][2009][2][2];

int sol(int i, int j, bool r, bool c){
    int v = (a[i][j] - '0') ^ r ^ c;
    if (!v)
        return 1e9 + 11;
    if (i == m && j == n)
        return 0;
    if (~dp[i][j][r][c])
        return dp[i][j][r][c];

    int cur = 1e9 + 11;

    if (i + 1 <= m){
      for (int t2 = 0; t2 < 2; ++t2)
        minimize(cur, sol(i + 1, j, t2, c) + t2);
    }

    if (j + 1 <= n){
      for (int t2 = 0; t2 < 2; ++t2)
        minimize(cur, sol(i, j + 1, r, t2) + t2);
    }

    return dp[i][j][r][c] = cur;
}

void tinhnop() {
	cin >> m >> n; 
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> a[i][j];
		}
	}

	memset(dp, -1, sizeof(dp));

	int ans = 1e9 + 11; 

	for (int r = 0; r < 2; ++r) {
		for (int c = 0; c < 2; ++c) {
    	int v = (a[1][1] - '0') ^ r ^ c;
			if (!v) continue;
			minimize(ans, sol(1, 1, r, c) + r + c);
		}
	}

	cout << ans; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "d5gpath"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}