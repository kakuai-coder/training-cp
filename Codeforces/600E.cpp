/**
 * author: tinhnopro (tinh nop)
 * created: 2024-12-09
**/
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 0
#endif // LOCAL

#include <bits/stdc++.h>

#define int long long

using namespace std;

const int maxN = 1e5 + 5;

int n, c[maxN];
vector<int> adj[maxN];
map<int, int> cnt[maxN], sum[maxN];
int answer[maxN];

void dfs(int u, int parent) {
	cnt[u][c[u]] = 1;
	sum[u][1] = c[u];

	for (int v : adj[u]) if (v ^ parent) {
		dfs(v, u);

		if (cnt[u].size() < cnt[v].size()) {
			swap(cnt[u], cnt[v]);
			swap(sum[u], sum[v]);
		}

		for (auto x : cnt[v]) {
			int val = x.first;
			int tot = x.second;

			sum[u][cnt[u][val]] -= val;			cnt[u][val] += tot;
			sum[u][cnt[u][val]] += val;

		}
		debug(u, sum[u], cnt[u]);

		sum[v].clear();
		cnt[v].clear();
	}


	answer[u] = sum[u].rbegin()->second;
}


int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (fopen("600E.inp", "r")) {
		freopen("600E.inp", "r", stdin);
		freopen("600E.out", "w", stdout);
	}

	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> c[i];
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}

	dfs(1, 1);

	for (int i = 1; i <= n; ++i) cout << answer[i] << ' ';
}

