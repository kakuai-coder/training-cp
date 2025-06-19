/*
	Author: tinhnopro
	created: 04.04.2025 15:33:15
*/
#include <bits/stdc++.h>

#define CHERRY "b"

using namespace std;

using i64 = long long;

const int maxK = 20; 
const int maxN = 1001; 
const i64 inf = (i64) 1e15;

int n, m, k, s[maxK];
i64 dist[25][maxN], dp[25][(1 << maxK)];
vector<pair<int, i64> > adj[maxN]; 


void bfs(int x) {
	for (int i = 1; i <= n; ++i) dist[x][i] = inf;  
	priority_queue<pair<i64, int>, vector<pair<i64, int> >, greater<pair<i64, int> > > pq; 
	
	dist[x][s[x]] = 0; 
	pq.emplace(0LL, s[x]);

	while (!pq.empty()) {
		int u; 
		i64 d_u; 

		tie(d_u, u) = pq.top(); 
		pq.pop(); 

		if (d_u > dist[x][u]) continue;

		for (auto d : adj[u]) {
			int v = d.first; 
			i64 w = d.second; 

			if (dist[x][v] > dist[x][u] + w) {
				dist[x][v] = dist[x][u] + w;
				pq.emplace(dist[x][v], v);
			}
		}
	}
}

i64 calc(int i, int mask) {
	if (__builtin_popcount(mask) == k + 1) {
		return dist[i][1];
	}

	if (~dp[i][mask]) return dp[i][mask]; 

	i64 cur = inf; 

	for (int j = 1; j <= k; ++j) {
		if (!((mask >> j) & 1)) cur = min(cur, calc(j, mask | (1 << j)) + dist[i][s[j]]);
	}

	return dp[i][mask] = cur; 
}

void solve() {
	cin >> n >> m >> k;
	
	for (int i = 1; i <= k; ++i) cin >> s[i]; 

	for (int i = 1; i <= m; ++i) {
		int u, v, w; 
		cin >> u >> v >> w; 
		adj[u].push_back({v, w});
	}

	s[0] = 1; 
	for (int i = 0; i <= k; ++i) bfs(i);

	memset(dp, -1, sizeof(dp)); 

	i64 ans = calc(0, 1); 

	if (ans < inf) {
		cout << ans; 
	} else cout << -1;

	return void(cout << '\n');
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	if (fopen(CHERRY".inp", "r")) {
		freopen(CHERRY".inp", "r", stdin);
		freopen(CHERRY".out", "w", stdout);
	}

	int t = 1; 
	// cin >> t;

	for (int i = 1; i <= t; ++i) {
		cerr << "Case #" << i << '\n';
		solve();
	}

	cerr << "[runtime] " << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";

	return 0; 
}