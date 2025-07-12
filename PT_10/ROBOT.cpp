/*
	Author: kakuai
	created: 2025.07.12 09:51:59
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#define int long long

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 5009; 

int n, m;
int a[maxN], dp[maxN][maxN];
pair<int, int> d[maxN];

void kakuai() {
	cin >> n >> m; 

	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	for (int i = 1; i <= m; ++i) {
		cin >> d[i].first >> d[i].second;
	}

	sort(a + 1, a + n + 1); 
	sort(d + 1, d + m + 1); 

	memset(dp, 0x3f, sizeof(dp));

	dp[0][0] = 0; 

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			dp[i][j] = dp[i][j - 1];
			int res = 0; 
			for (int x = 1; x <= min(i, d[j].second); ++x) {
				res += abs(a[i - x + 1] - d[j].first);
				dp[i][j] = min(dp[i][j], dp[i - x][j - 1] + res);
			}
		}
	}

	cout << dp[n][m];

}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "ROBOT"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}