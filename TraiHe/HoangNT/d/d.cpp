/*
	Author: tinhnopro
	created: 2025.06.17 17:44:15
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

const int maxN = 2e6 + 5;

int n, q; 
int a[505], dp[maxN], bit[maxN];
vector<array<int, 4>> quest[maxN]; 
int res[maxN][2];

void update(int id, int val) {
	if (!id) return ; 
	for (; id <= n; id += id & -id) bit[id] += val; 
}

int Get(int id) {
	int res = 0; 
	for (; id; id -= id & -id) res += bit[id];
	return res; 
}

void tinhnop() {
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) cin >> a[i]; 

	for (int i = 1; i <= q; ++i) {
		int l, r, x, y; 
		cin >> l >> r >> x >> y;
		quest[r].push_back({x - 1, l, 0, i});
		quest[r].push_back({y, l, 1, i});
	}

	int sum = 0; 
	dp[0] = 1e9 + 11; 
	
	for (int i = 1; i <= n; ++i) {
		sum += a[i]; 
		sort(quest[i].begin(), quest[i].end());
		memset(bit, 0, sizeof(bit));

		for (int j = sum - a[i]; j >= 0; --j) {
			maximize(dp[j + a[i]], min(i, dp[j]));
		}

		int idx = 1; 
		for (auto &r : quest[i]) {
			int l = r[1];
			int x = r[0];
			int id1 = r[2]; 
			int id2 = r[3];

			while (idx <= min(x, sum)) {
				update(n - dp[idx] + 1, 1);
				idx++; 
			}

			res[id2][id1] = Get(n - l + 1);
		}
	}

	for (int i = 1; i <= q; ++i) cout << res[i][1] - res[i][0] << '\n';
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "d"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}