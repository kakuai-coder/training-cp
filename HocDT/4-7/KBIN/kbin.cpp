/*
	Author: kakuai
	created: 2025.07.04 09:00:37
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

int n;
i64 dp[1009][5];
i64 k;

i64 solve(int i, int last) {
	if (i == n + 1) return 1;
	if (~dp[i][last]) return dp[i][last];

	i64 cur = 0;

	if (!last) {
		cur += solve(i + 1, 1);
	} 
	minimize(cur, k + 1);
	
	cur += solve(i + 1, 0);
	
	minimize(cur, k + 1);

	return dp[i][last] = cur;
}

void trace(int i, int last) {
	if (i == n + 1) return ;
	if (!last && solve(i + 1, 0) < k) {
		k -= solve(i + 1, 0);
		cout << 1; 
		trace(i + 1, 1);
	} else {
		cout << 0;
		trace(i + 1, 0);
	}
}

void kakuai() {
	cin >> n >> k; 
	memset(dp, -1, sizeof(dp));
	if (solve(1, 0) < k) {
		cout << "-1";
		return ;
	}

	trace(1, 0);
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "KBIN"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}