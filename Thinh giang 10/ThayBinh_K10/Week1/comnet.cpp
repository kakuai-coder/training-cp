/*
	Author: tinhnopro
	created: 02.04.2025 14:15:50
*/
#include <bits/stdc++.h>

#define CHERRY "comnet"
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif // LOCAL

using namespace std;

using i64 = long long;

const int maxN = 5009; 

int n, m; 

struct DSU {
	int lab[maxN];

	DSU() {
		memset(lab, -1, sizeof(lab));
	}

	int find_par(int u) {
		return lab[u] < 0 ? u : lab[u] = find_par(lab[u]);
	}

	void join(int a, int b) {
		a = find_par(a); 
		b = find_par(b); 

		// cout << a << ' ' << b << '\n';

		if (a == b) return ; 

		if (lab[a] > lab[b]) swap(a, b); 

		lab[a] += lab[b]; 
		lab[b] = a;
	}
} dsu;



void solve() {
	cin >> n >> m; 
	for (int i = 1; i <= m; ++i) {
		int u, v; 
		cin >> u >> v; 
		dsu.join(u, v);
	}

	vector<int> root; 
	for (int i = 1; i <= n; ++i) if (dsu.lab[i] < 0) root.push_back(i);

	// for (int i = 1; i <= n; ++i) cout << dsu.lab[i] << ' ';
	// cout << '\n';

	// cout << dsu.find_par(1);

	vector<pair<int, int> > edges; 

	for (size_t i = 1; i < root.size(); ++i) {
		edges.emplace_back(root[0], root[i]);
	}

	cout << edges.size() << '\n'; 

	for (size_t i = 0; i < edges.size(); ++i) {
		cout << edges[i].first << ' ' << edges[i].second << '\n';
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