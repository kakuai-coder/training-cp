/*
	Author: kakuai
	created: 2025.07.04 09:22:22
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

const int maxN = 4009; 
const int Mod = 1e9 + 7; 

int n, m;
int a[maxN], dp[maxN][maxN], dpsum[maxN][maxN], valid[maxN][maxN];
vector<int> stk; 

void kakuai() {
	cin >> n >> m; 
	for (int i = 1; i <= n; ++i) cin >> a[i];

	a[0] = Mod + 1; 
	stk.push_back(0);

	int ans = 1;

	dp[0][0] = dpsum[0][0] = 1; 

	for (int idx = 1; idx <= n; ++idx) {
		for (int i = 0; i <= m; ++i) {
			valid[idx][i] = valid[idx - 1][i];
		}

		while (a[stk.back()] < a[idx]) {
			int last = stk.back(); 
			stk.pop_back(); 

			for (int i = 0; i <= m; ++i) {
				valid[idx][i] -= dp[last][i]; 
				if (valid[idx][i] < 0) valid[idx][i] += Mod;
			}
		}

		int pre = ssize(stk) - 1; 
		while (a[stk[pre]] <= a[idx]) {
			pre--;
		}

		for (int i = a[idx]; i <= m; ++i) {
			dp[idx][i] = (dpsum[stk[pre]][i - a[idx]] - valid[stk[pre]][i - a[idx]] + Mod) % Mod;

			ans += dp[idx][i]; 
			if (ans >= Mod) ans -= Mod; 
		}

		for (int i = 0; i <= m; ++i) {
			dpsum[idx][i] = (dpsum[idx - 1][i] + dp[idx][i]) % Mod;
		}

		stk.push_back(idx); 

		for (int i = 0; i <= m; ++i) {
			valid[idx][i] += dp[idx][i]; 
			if (valid[idx][i] >= Mod) valid[idx][i] -= Mod; 
		}
	}

	cout << ans; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "sumk"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}