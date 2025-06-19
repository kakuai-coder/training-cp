/*
	Author: tinhnopro
	created: 02.04.2025 16:26:13
*/
#include <bits/stdc++.h>

#define CHERRY "reverse"

using namespace std;

using i64 = long long;

const int maxN = 2e5 + 5; 

int n, m, dist[maxN], vist[maxN]; 
vector<pair<int, int> > adj[maxN];

void solve() {

	cin >> n >> m; 
	for (int i = 1; i <= m; ++i) {
		int u, v; 
		cin >> u >> v; 
		adj[u].push_back({v, 0}); 
		adj[v].push_back({u, 1});
	}

	memset(dist, 0x3f, sizeof(dist));
	deque<int> q; 
	q.push_front(1);
	dist[1] = 0;

	while (!q.empty()) {
		int u = q.front(); 
		q.pop_front();
		
		if (vist[u]) continue;

		vist[u] = 1; 

		for (auto x : adj[u]) if (dist[x.first] > dist[u] + x.second) {
			dist[x.first] = dist[u] + x.second; 
			if (x.second == 1) {
				q.push_back(x.first);
			} else q.push_front(x.first);
		}
	}

	if (!vist[n]) cout << -1; 
	else cout << dist[n];
	
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