/*
	Author: kakuai
	created: 2025.06.23 12:12:23
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 1e3 + 5; 
const int mod = 998244353; 

int n, k, h[maxN], dp[maxN][maxN];

void kakuai() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> h[i];
	}

	sort(h + 1, h + n + 1);

	int ans = 0; 
	
	for (int x = 1; x <= h[n] / (k - 1); ++x) {
		dp[0][0] = 1; 
		int pos = 1; 
		for (int i = 1; i <= n; ++i) {
			while (pos < n && h[i] - h[pos] >= x) pos++; 

			dp[i][0] = 1;
			
			for (int j = 1; j <= k; ++j) {
				dp[i][j] = dp[i - 1][j] + dp[pos - 1][j - 1];
				if (dp[i][j] >= mod) dp[i][j] -= mod; 
			}
		}

		ans += dp[n][k];
		if (ans >= mod) ans -= mod; 
	}

	cout << ans; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "a"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}