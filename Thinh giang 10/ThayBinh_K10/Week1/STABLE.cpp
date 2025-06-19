/*
	Author: tinhnopro
	created: 03.04.2025 00:07:09
*/
#include <bits/stdc++.h>

#define CHERRY "STABLE"

using namespace std;

using i64 = long long;

const int maxN = 1e4 + 5; 

int n, m, s, dist[maxN], cnt[maxN]; 
vector<int> adj[maxN]; 
set< pair<int, int> > Set; 

void bfs() {
	queue<int> q; 

	memset(dist, 0x3f, sizeof(dist));

	q.push(s); 
	dist[s] = 0;
	cnt[s] = 1; 

	while (!q.empty()) {
		int u = q.front(); 
		q.pop(); 

		// cout << u << ' ' << cnt[u] << ' ' << dist[u] << '\n';

		for (int v : adj[u]) {
			if (dist[v] > dist[u] + 1) {
				// cout << v << ' ' << u << ' ' << cnt[v] << ' ' << cnt[u] << '\n';
				dist[v] = dist[u] + 1;
				cnt[v] = cnt[u]; 
				// cout << ' ' << v << ' ' << u << ' ' << cnt[v] << ' ' << cnt[u] << '\n';
				q.push(v); 
			} else if (dist[v] == dist[u] + 1) {
				cnt[v] = 2; 
			}

			// dist[v] = min(dist[v], dist[u] + 1)
			// cnt[v] += cnt[u]
		}
	}
}

void solve() {
	cin >> n >> m >> s; 
	for (int i = 1, u, v; i <= m; ++i) {
		cin >> u >> v;
		if (Set.find({u, v}) == Set.end())
		adj[u].push_back(v); 
		
		Set.insert({u, v});
	}

	bfs();

	int ans = 0; 

	for (int i = 1; i <= n; ++i) if (cnt[i] >= 2) {
		ans++; 
		// cout << i << ' ' << dist[i] << '\n';
	}


	cout << ans; 

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