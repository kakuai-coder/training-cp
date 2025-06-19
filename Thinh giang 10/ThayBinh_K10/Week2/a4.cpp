/*
	Author: tinhnopro
	created: 2025.04.09 07:42:54
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

const int maxN = 1e6 + 5; 
const int LOG = 25;

int n, m; 
vector<int> adj[maxN]; 
int st[LOG + 1][maxN], depth[maxN]; 
i64 mark[maxN]; 

void dfs_build(int u, int par) {
	for (int v : adj[u]) {
		if (v == par) continue;
		
		depth[v] = depth[u] + 1; 
		st[0][v] = u; 

		for (int i = 1; i <= LOG; ++i) {
			st[i][v] = st[i - 1][st[i - 1][v]];
		}
		
		dfs_build(v, u); 
	}
}

int lca(int u, int v) {
	if (u == v) return u; 

	if (depth[u] < depth[v]) swap(u, v);

	for (int i = LOG; i >= 0; --i) if (depth[st[i][u]] >= depth[v]) {
		u = st[i][u]; 
	}

	if (u == v) return u; 

	for (int i = LOG; i >= 0; --i) if (st[i][u] != st[i][v]) {
		u = st[i][u]; 
		v = st[i][v]; 
	}

	return st[0][u];
}

void dfs2(int u, int par) {
	for (int v : adj[u]) if (v != par) {
		dfs2(v, u); 
		mark[u] += mark[v];
	}
}

void tinhnop() {

	cin >> n; 

	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u);
	}
	
	st[0][1] = 0; 
	dfs_build(1, 0);

	cin >> m; 

	for (int i = 1, u, v, l; i <= m; ++i) {
		cin >> u >> v; 
		l = lca(u, v); 
		// cout << l << '\n';
		mark[st[0][l]]--;
		mark[l]--; 
		mark[u]++; 
		mark[v]++;
	}

	dfs2(1, 0);

	int cnt = 0; 

	for (int i = 1; i <= n; ++i) {
		if (!mark[i]) cnt++;
		// cout << mark[i] << ' ';
	}

	cout << cnt;
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}