/*
	Author: kakuai
	created: 2025.07.03 23:18:47
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
#define int long long 

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 1e5 + 5; 
const int Log = 16; 

int n, m, q;
vector<int> adj[maxN];
int depth[maxN], up[Log + 1][maxN], sum[maxN], sumtoRoot[maxN];

void dfs(int u, int par) {
	up[0][u] = par; 
	for (int i = 1; i <= Log; ++i) up[i][u] = up[i - 1][up[i - 1][u]];

	for (int v : adj[u]) {
		if (v == par) continue;

		depth[v] = depth[u] + 1; 
		
		dfs(v, u);
	}
}

int lca(int u, int v) {
	if (u == v) return u; 

	if (depth[u] < depth[v]) swap(u, v);
	
	int k = depth[u] - depth[v];

	for (int i = Log; ~i; --i) if ((k >> i) & 1) {
		u = up[i][u];
	}

	if (u == v) return u; 

	for (int i = Log; ~i; --i) if (up[i][u] != up[i][v]) {
		u = up[i][u]; 
		v = up[i][v];
	}

	return up[0][u];
}

void dfs2(int u, int par) {
	for (int v : adj[u]) if (v != par) {
		dfs2(v, u); 
		sum[u] += sum[v];
	}
}

void dfs_total(int u, int par) {
	sumtoRoot[u] = sumtoRoot[par] + sum[u];
	for (int v : adj[u]) if (v != par) {
		dfs_total(v, u); 
	}
}

void kakuai() {
	cin >> n >> m >> q; 

	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u);
	}

	dfs(1, 0); 

	for (int i = 1; i <= m; ++i) {
		int u, v, c; 
		cin >> u >> v >> c; 
		sum[u] += c; 
		sum[v] += c; 
		int d = lca(u, v); 
		sum[d] -= c;
		sum[up[0][d]] -= c;  
	}

	dfs2(1, 0);

	dfs_total(1, 0);

	while (q--) {
		int u, v; cin >> u >> v; 
		cout << sumtoRoot[u] + sumtoRoot[v] - 2 * sumtoRoot[lca(u, v)] + sum[lca(u, v)] << '\n';
	}

}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "c2"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}