/**
 * author: tinhnopro (tinh nop)
 * created: 2024-12-05
**/
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 0
#endif // LOCAL

#include <bits/stdc++.h>

using namespace std;

const int maxN = 2e5 + 5;

int n;
vector<int> adj[maxN];

int ans, dp[maxN];

using ii = pair<int, int>;

#define fi first
#define se second

int b[4];

ii get_max(ii x, int c) {
	b[1] = x.fi;
	b[2] = x.se;
	b[3] = c;
	sort(b + 1, b + 4);
	return {b[3], b[2]};
}

void dfs(int u, int parent) {
	dp[u] = adj[u].size() - 1;
	if (u == 1) dp[u]++;

	ii d = {-1e9, -1e9};

	for (int v : adj[u]) if (v ^ parent) {
		dfs(v, u);
		d = get_max(d, dp[v]);
 	}

 	dp[u] += max(0, d.first - 1);

 	if (u == 1)
		ans = max(ans, dp[u]);
	else
		ans = max(ans, dp[u] + 1);

 	if (d.se > -1e9) {
		if (u == 1) {
			ans = max(ans, dp[u] + d.se - 1);
		} else  ans = max(ans, dp[u] + d.se);
 	}
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) adj[i].clear();
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	ans = 1;

	dfs(1, 0);

	cout << ans << '\n';
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	while (t--) {
		solve();
	}
}

