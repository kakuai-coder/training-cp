/*
	Author: tinhnopro
	created: 2025.04.16 23:46:19
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

int n, m; 

vector<edge_t> edges;
i64 dist[205][205];

void tinhnop() {
	cin >> n >> m; 
	memset(dist, 0x3f, sizeof(dist));
	for (int i = 1; i <= m; ++i) {
		int u, v, w; 
		cin >> u >> v >> w;
		dist[u][v] = w;
		dist[v][u] = w;
		edges.push_back({u, v, w});
	}

	for (int i = 1; i <= n; ++i) {
		for (int u = 1; u <= n; ++u) {
			for (int v = 1; v <= n; ++v) {
				if (dist[u][v] > dist[u][i] + dist[i][v]) {
					dist[u][v] = dist[u][i] + dist[i][v];
				}
			}
		}
	}

	i64 tot = 0;

	for (edge_t &e : edges) {
		int u = e.u; 
		int v = e.v; 
		int w = e.w; 

		if (w > dist[u][v]) continue;
		
		bool ok = false; 

		for (int i = 1; i <= n; ++i) {
			if (dist[u][i] + dist[i][v] == dist[u][v]) {
				ok = true; 
				break; 
			}
		}

		if (ok) continue;

		// cout << u << ' ' << v << '\n';

		tot += w; 
	}

	cout << tot; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b2"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}