/*
	Author: tinhnopro
	created: 2025.04.09 22:24:00
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 10
#endif // LOCAL

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 1e4 + 5; 

int n, m, k; 
vector<int> adj[maxN];
int low[maxN], num[maxN], incyc[maxN], distx[maxN], disty[maxN];
pair<int, int> pos[14]; 

int timeDFS = 0;

void dfs(int u, int par) {
	low[u] = num[u] = ++timeDFS; 

	for (int v : adj[u]) if (v != par) {
		if (!num[v]) {
			dfs(v, u); 
			minimize(low[u], low[v]);

			if (low[v] <= num[u]) {
				incyc[u] = true; 
			}

		} else minimize(low[u], num[v]);
 	}
}

void bfs(int s, int *dist) {
	for (int i = 1; i <= n; ++i) dist[i] = 1e9;
	queue<int> q; 

	q.push(s);
	dist[s] = 0; 

	while (!q.empty()) {
		int u = q.front(); 
		q.pop(); 

		for (auto v : adj[u]) {
			if (dist[v] > dist[u] + 1) {
				dist[v] = dist[u] + 1; 
				q.push(v);
			}
		}
	}
}

void tinhnop() {
	cin >> n >> m >> k; 

	for (int i = 1; i <= k; ++i) {
		cin >> pos[i].first >> pos[i].second; 
	}

	for (int i = 1; i <= m; ++i) {
		int u, v; 
		cin >> u >> v;
		adj[u].push_back(v); 
		adj[v].push_back(u);
	}

	for (int i = 1; i <= n; ++i) if (!num[i]) dfs(i, i);

	for (int i = 1; i <= k; ++i) {
		bfs(pos[i].first, distx);
		bfs(pos[i].second, disty);

		bool can = false; 

		for (int u = 1; u <= n; ++u) if (incyc[u]) {
			if (distx[u] > disty[u]) {
				can = true; 
				break;
			}
		}

		cout << !can << '\n';
	}
}	

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b4"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}