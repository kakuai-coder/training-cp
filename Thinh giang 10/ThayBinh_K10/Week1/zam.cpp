/*
	Author: tinhnopro
	created: 02.04.2025 14:35:22
*/
#include <bits/stdc++.h>

#define CHERRY "zam"

using namespace std;

using i64 = long long;

const int maxN = 105; 

int n, m, st, en, s; 
int cost[maxN], dist[maxN * 1009], trace[maxN * 1009];
vector<int> adj[maxN];

int to_vertex(int u, int c) {
	return (u - 1) * (s + 1) + c % (s + 1); 
}

pair<int, int> to_num(int p) {
	int u = p / (s + 1) + 1; 
	int c = p % (s + 1); 
	return {u, c};
}

void bfs() {
	queue<int> q; 
	memset(dist, -1, sizeof(dist));

	int u = to_vertex(st, s - cost[st]);
	q.push(u); 
	dist[u] = 1;

	while (!q.empty()) {
		int p = q.front();
		q.pop();
		pair<int, int> x = to_num(p); 
		// cout << p << ' ' <<  x.first << ' ' << x.second << '\n';

		
		for (int v : adj[x.first]) if (x.second >= cost[v]) {
			int d = x.second - cost[v]; 
			int p1 = to_vertex(v, d); 
			if (dist[p1] == -1) {
				dist[p1] = dist[p] + 1;
				trace[p1] = p;
				q.push(p1);
			}
		}
	}
}

void solve() {
	cin >> n >> m >> st >> en >> s; 

	for (int i = 1; i <= n; ++i) {
		cin >> cost[i]; 
	}

	for (int i = 1, u, v; i <= m; ++i) {
		cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u); 
	}

	if (s < cost[st]) {
		cout << -1; 
		return ;
	}

	bfs(); 

	if (dist[to_vertex(en, 0)] == -1) {
		cout << -1; 
		return ;
	}

	int v = to_vertex(en, 0), u = to_vertex(st, s - cost[st]); 

	vector<int> path; 
	path.push_back(v);

	while (v != u) {
		v = trace[v];
		path.push_back(v);
		if (v == 0) return ;
		// cerr << v << '\n';
	}

	reverse(path.begin(), path.end()); 

	cout << path.size() << ' '; 
	for (int x : path) {
		pair<int, int> d = to_num(x); 
		cout << d.first << ' ';
	}

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