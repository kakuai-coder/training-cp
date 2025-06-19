/*
	Author: tinhnopro
	created: 2025.06.15 19:24:19
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 10
#endif // LOCAL

#define int long long 

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 2009;

int n, m, c[maxN][maxN], dist[maxN][maxN]; 
int deg[maxN], vist[maxN], dp[1 << 21];

int cntEdge = 0;

void dfs(int u) {
	vist[u] = 1;
	if (c[u][u]) cntEdge++;
	for (int v = 1; v <= n; ++v) if (c[u][v] && !vist[v]) {
		cntEdge++;
		dfs(v);
	}
}

void tinhnop() {

	memset(dist, 0x3f, sizeof(dist));
	int sumW = 0;
	cin >> n >> m; 

	for (int i = 1; i <= n; ++i) dist[i][i] = 0; 

	for (int i = 1; i <= m; ++i) {
		int u, v, cost;
		cin >> u >> v >> cost;

		c[u][v] = c[v][u] = 1;

		minimize(dist[u][v], cost);
		minimize(dist[v][u], cost); 

		deg[u]++;
		deg[v]++;
		sumW += cost;
	}	

	for (int i = 1; i <= n; ++i) {
		for (int u = 1; u <= n; ++u) {
			for (int v = 1; v <= n; ++v) if (dist[u][v] > dist[u][i] + dist[i][v]) {
				dist[u][v] = dist[u][i] + dist[i][v];
			}
		}
	}

	for (int i = 2; i <= n; ++i) {
		if (dist[1][i] > 1e9 + 11 && deg[i] > 0) {
			cout << -1;
			return ;
		}
	}

	vector<int> odd; 

	for (int i = 1; i <= m; ++i) if (deg[i] & 1) {
		odd.push_back(i);
	}

	int k = ssize(odd);

	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0; 

	for (int mask = 1; mask < (1 << k); ++mask) {
		int i = __builtin_ctz(mask);
		int mask2 = mask ^ (1 << i);

		for (int j = i + 1; j < k; ++j) {
			if (mask2 & (1 << j)) {
              int m2 = mask2 ^ (1<<j);
              int cost = dist[ odd[i] ][ odd[j] ];
              dp[mask] = min(dp[mask], dp[m2] + cost);
			}
		}
	}

	cout << sumW + dp[(1 << k) - 1];
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "pacman"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}