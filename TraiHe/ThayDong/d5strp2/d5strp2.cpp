/*
	Author: kakuai
	created: 2025.06.26 20:41:34
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

const int maxN = 3e3 + 5; 
const i64 inf = (i64)1e18 + 11; 

int n, k; 
int cost[maxN]; 
i64 dp[maxN][maxN];
int memo_bit[maxN][maxN], memo_mask[maxN][maxN];

void kakuai() {
	cin >> n >> k; 
	for (int i = 0; i < (1 << k); ++i) {
		cin >> cost[i];
	}

	memset(dp, 0x3f, sizeof(dp)); 

	dp[0][0] = 0; 

	for (int i = 0; i < n; ++i) {
		for (int submask = 0; submask < (1 << (k - 1)); ++submask) {
			if (dp[i][submask] > inf) continue;
			for (int bit = 0; bit <= 1; ++bit) {
				int new_mask; 
				if (k == 1) {
					new_mask = 0; 
				} else {
					new_mask = ((submask << 1) | bit) & ((1 << (k - 1)) - 1);
				}

				i64 c = 0; 

				if (i + 1 >= k) {
					int full = ((submask << 1) | bit) & ((1 << k) - 1);
					c = cost[full];
				}

				if (minimize(dp[i + 1][new_mask], dp[i][submask] + c)) {
					memo_bit[i + 1][new_mask] = bit; 
					memo_mask[i + 1][new_mask] = submask; 
				}
			}
		}
	}

	i64 res = inf; 
	int best_mask = 0;

	for (int mask = 0; mask < (1 << (k - 1)); ++mask) {
		if (minimize(res, dp[n][mask])) {
			best_mask = mask; 
		}
	}

	string s(n, '0'); 

	for (int pos = n; pos >= 1; --pos) {
		int bit = memo_bit[pos][best_mask];
		s[pos - 1] = bit + '0'; 
		best_mask = memo_mask[pos][best_mask];
	}

	cout << s; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "d5strp2"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}