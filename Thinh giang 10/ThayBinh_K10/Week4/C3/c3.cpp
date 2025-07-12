/*
	Author: kakuai
	created: 2025.07.04 00:02:05
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

const int maxN = 2e5 + 5; 
const int Log = 17; 

struct node_t {
	int v, c1, c2; 

	node_t(int _v, int _c1, int _c2) : v(_v), c1(_c1), c2(_c2) {}
	node_t() {
		v = c1 = c2 = 0;
	}
};	

int n;
vector<node_t> adj[maxN];
int depth[maxN], up[Log + 1][maxN], diff[maxN];

void dfs(int u, int par) {
	up[0][u] = par; 
	for (int i = 1; i <= Log; ++i) up[i][u] = up[i - 1][up[i - 1][u]];

	for (auto& x : adj[u]) {
		int v = x.v;
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
	for (auto& x : adj[u]) {
		int v = x.v; 
		if (v == par) continue;

		dfs2(v, u); 
		diff[u] += diff[v];
	}
}

int ans = 0; 

void dfs_total(int u, int par) {
	for (auto& x : adj[u]) {
		int v = x.v; 
		int c1 = x.c1; 
		int c2 = x.c2; 
		if (v == par) continue;

		ans += min(c2, c1 * diff[v]);

		dfs_total(v, u); 
	}
}


void kakuai() {
	cin >> n; 

	for (int i = 1; i < n; ++i) {
		int u, v, c1, c2; cin >> u >> v >> c1 >> c2; 
		adj[u].emplace_back(v, c1, c2); 
		adj[v].emplace_back(u, c1, c2);
	}

	dfs(1, 0); 

	for (int u = 1; u < n; ++u) {
		int v = u + 1; 

		diff[u]++;
		diff[v]++;
		diff[lca(u, v)] -= 2; 
	}

	dfs2(1, 0);

	dfs_total(1, 0);

	cout << ans; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "c3"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}