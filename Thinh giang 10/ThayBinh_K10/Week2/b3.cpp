/*
	Author: tinhnopro
	created: 2025.04.09 23:37:51
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

const int maxN = 2e5 + 5; 
const int MOD = 1e9 + 7;

int n, m;
vector<int> adj[maxN], stk;
int low[maxN], num[maxN], timeDFS = 0;
int color[maxN], cl = 0, sz[maxN];
vector<int> g[maxN];
set<pair<int, int> > mark; 

void dfs(int u, int par) {
	low[u] = num[u] = ++timeDFS;

	stk.push_back(u);

	for (int v : adj[u]) if (v != par) {
		if (!num[v]) {
			dfs(v, u); 
			minimize(low[u], low[v]);
		} else minimize(low[u], num[v]);
	}

	if (low[u] == num[u]) {
		int v = -1;
		cl++; 
		color[u] = cl; 

		while (v != u) {
			v = stk.back(); 
			color[v] = cl; 
			low[v] = num[v] = n + 1;
			sz[cl]++; 
			stk.pop_back();
		}
	}
}

void build_graph() {
	for (int i = 1; i <= n; ++i) if (!num[i]) dfs(i, i); 
	for (int i = 1; i <= n; ++i) {
		for (int j : adj[i]) {
			int u = color[i]; 
			int v = color[j]; 
			if (u > v) swap(u, v);
			if (u != v && mark.find({u, v}) == mark.end()) {
				g[u].push_back(v);
				g[v].push_back(u); 
				mark.insert({u, v});
			}
		}
	}
}

void tinhnop() {
	cin >> n >> m; 

	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u);
	}

	build_graph(); 

	vector<int> stable; 

	for (int i = 1; i <= cl; ++i) {
		if (g[i].size() <= 1) {
			stable.push_back(i);
		}
		// cout << i << ": ";
		// for (int x : g[i]) cout << x << ' ';
		// cout << '\n';
	}

	int cnt = 1; 
	for (int x : stable) {
		// cerr << x << ' ' << sz[x] << '\n';
		cnt = (1LL * cnt * sz[x]) % MOD; 
	}

	cout << stable.size() << ' ' << cnt;
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