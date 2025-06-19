/**
 * author: tinhnopro (tinh nop)
 * created: 2024-11-28
**/

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif // LOCAL

#include <bits/stdc++.h>

using namespace std;

template <typename T> inline int isize(const T& a) { return a.size(); }

template <typename T1, typename T2> bool maximize(T1& a, T2 b) { return a < b ? a = b, true : false; }
template <typename T1, typename T2> bool minimize(T1& a, T2 b) { return a > b ? a = b, true : false; }

int n, W;
vector<pair<int, int>> List;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
#ifdef LOCAL
	freopen("dttui2.inp", "r", stdin);
	freopen("dttui2.out", "w", stdout);
#endif // LOCAL

	cin >> n >> W;
	for (int i = 0, w, v, cnt; i < n; ++i) {
		cin >> w >> v >> cnt;

		int base = 1;
		while (base <= cnt) {
			cnt -= base;
			List.emplace_back(base * w, base * v);
			base *= 2;
		}

		if (cnt > 0) List.emplace_back(cnt * w, cnt * v);
	}

	vector<int> dp(W + 2, 0);

	for (int i = 0; i < isize(List); ++i) {
		for (int w = W; ~w; --w) if (w >= List[i].first) {
				maximize(dp[w], dp[w - List[i].first] + List[i].second);
		}
	}

	cout << dp[W];
}
