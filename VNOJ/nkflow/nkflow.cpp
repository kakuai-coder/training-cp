/*
	Author: tinhnopro
	created: 2025.04.29 14:42:17
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

const int maxN = 1011;
const int inf = 1e9 + 11; 

int n, m, s, t; 

struct Network {
	int s, t, f[maxN][maxN], cap[maxN][maxN], d[maxN], head[maxN]; 
	vector<int> adj[maxN];

	void addEdge(const int &u, const int &v, const int &c) {
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
		cap[u][v] = c; 	
		f[u][v] = f[v][u] = 0; 
	}

	void bfs() {
		for (int i = 1; i <= n; ++i) d[i] = inf; 
		queue<int> q; 
		
		while (!q.empty()) {
			int u = q.front(); 
			q.pop(); 

			for (int v : adj[u]) {
				if (cap[u][v] == f[u][v]) continue;
				if (d[v] > d[u] + 1) {
					d[v] = d[u] + 1; 
					q.push(v);
				}
			}
		}
	}

	int dfs(int u, int delta) {
		if (delta == 0) return delta; 
		if (u == t) return delta;
		
		for (; head[u] < ssize(adj[u]); ++head[u]) {
			int v = adj[u][head[u]];

			if (f[u][v] == cap[u][v]) continue;
			if (d[v] != d[u] + 1) continue;

			int ndelta = dfs(v, min(cap[u][v] - f[u][v], delta));

			if (ndelta == 0) continue;

			f[u][v] += ndelta; 
			f[v][u] -= ndelta; 

		}
	}
};

void tinhnop() {
	cin >> n >> m >> s >> t;

	for (int i = 1; i <= m; ++i) {
		int u, v, c; 
		cin >> u >> v >> c; 

	}


}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "nkflow"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}