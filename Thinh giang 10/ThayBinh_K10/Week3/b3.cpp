/*
	Author: tinhnopro
	created: 2025.04.16 20:05:59
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

struct edge_t {
	int u, v, w;

	edge_t(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};

const int maxN = 2e5 + 5; 
const i64 inf = (i64) 1e18 + 5;

int n, m;
vector<edge_t> edges;
vector<int> g[maxN];

i64 dist[maxN];
int vist[maxN];

bool dfs(int u) {
	if (u == n) return true;
	
	vist[u] = 1; 
	int w = 0; 

	for (int v : g[u]) if (!vist[v]) {
		w |= dfs(v);
	}

	return w; 
}

void tinhnop() {
	cin >> n >> m; 
	for (int i = 1; i <= m; ++i) {
		int u, v, w; 
		cin >> u >> v >> w;
		edges.push_back({u, v, -w});
		g[u].push_back(v); 
	}

	for (int i = 2; i <= n; ++i) dist[i] = inf; 

	for (int i = 1; i < n; ++i) {
		for (edge_t &x : edges) {
			int u = x.u;
			int v = x.v; 
			int w = x.w; 

			if (dist[u] != inf && dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
			}
		}
	}

	bool isCyclic = false; 

	for (edge_t &x : edges) {
		if (dist[x.u] != inf && dist[x.v] > dist[x.u] + x.w) {
			isCyclic |= dfs(x.v); 
			for (int i = 1; i <= n; ++i) vist[i] = 0; 
		}
	}

	if (isCyclic) cout << -1; 
	else cout << -dist[n]; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b3"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}