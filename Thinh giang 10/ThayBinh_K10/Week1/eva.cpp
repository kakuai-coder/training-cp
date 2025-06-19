/*
	Author: tinhnopro
	created: 02.04.2025 14:07:01
*/
#include <bits/stdc++.h>

#define CHERRY "eva"

using namespace std;

using i64 = long long;

const int maxN = 1e5 + 5; 

int n, k, m, dist[maxN]; 
vector<int> adj[maxN]; 

void solve() {
	cin >> n >> k;
	queue<int> q; 
	memset(dist, -1, sizeof(dist)); 
	for (int i = 1, x; i <= k; ++i) {
		cin >> x; 
		q.push(x); 
		dist[x] = 0; 
	}

	cin >> m; 

	for (int i = 1; i <= m; ++i) {
		int u, v; 
		cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u); 
	}

	while (!q.empty()) {
		int u = q.front(); 
		q.pop(); 

		for (int v : adj[u]) if (dist[v] == -1) {
			dist[v] = dist[u] + 1; 
			q.push(v); 
		}
	}

	for (int i = 1; i <= n; ++i) cout << dist[i] << ' ';

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