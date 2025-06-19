/*
	Author: tinhnopro
	created: 31.03.2025 14:32:37
*/
#include <bits/stdc++.h>

#define CHERRY "Connect"

using namespace std;

using i64 = long long;

const int maxN = 1e5 + 5; 

int n, m; 

vector<int> adj[maxN]; 
int dist[maxN];

int bfs(int u, bool ok) {
	queue<int> q; 
	vector<int> nodes; 

	q.push(u); 

	dist[u] = 0; 
	int node = -1;

	while (!q.empty()) {
		int u = q.front();
		nodes.push_back(u); 
		q.pop(); 

		if (node == -1 || dist[node] < dist[u]) {
			node = u; 
		}

		for (int v : adj[u]) if (dist[v] == -1) {
			dist[v] = dist[u] + 1; 
			q.push(v); 	
		}
	}

	if (!ok) {
		for (int x : nodes) dist[x] = -1;
	}

	return node; 
}

void solve() {
	cin >> n >> m; 

	for (int i = 1, u, v; i <= m; ++i) {
		cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u);
	}

	int res = 0; 

	// cout << n << ' ' << m << '\n';

	memset(dist, -1, sizeof(dist));

	for (int i = 1; i <= n; ++i) if (dist[i] == -1) {
		int x = bfs(i, false); 
		// cout << x << ' ';
		x = bfs(x, true); 

		res += dist[x] + 1; 
	}

	// cout << '\n';

	cout << res; 

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
		// cerr << "Case #" << i << '\n';
		solve();
	}

	cerr << "[runtime] " << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";

	return 0; 
}