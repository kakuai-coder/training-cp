/*
	Author: kakuai
	created: 2025.07.04 22:18:35
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

int n, m;
vector<int> adj[maxN]; 
int diff[maxN], sumtoRoot[maxN]; 
map<pair<int, int>, int > mark;  
int up[Log + 1][maxN], depth[maxN];
vector<pair<int, int> > edges; 

void dfs_build(int u, int par) {
	up[0][u] = par; 

	for (int i = 1; i <= Log; ++i) up[i][u] = up[i - 1][up[i - 1][u]];

	for (int v : adj[u]) if (v != par) {
		depth[v] = depth[u] + 1; 
		dfs_build(v, u); 
	}
}


void dfs(int u, int par, int d) {
	sumtoRoot[u] = d; 

	for (int v : adj[u]) if (v != par) {
		dfs(v, u, d + diff[v]);
	}
} 

pair<int, pair<int, int> >  lca(int u, int v) {
	if (u == v) {
		return {u, {-1, -1}};
	}

	int k = depth[u] - depth[v] - 1; 

	if (k >= 0) {
		for (int i = 0; i <= Log; ++i) if ((k >> i) & 1) {
			u = up[i][u];
		}
	}

	if (k >= 0 && up[0][u] == v) {
		return {v, {u, -1}};
	}

	if (k >= 0) u = up[0][u]; 

	for (int i = Log; ~i; --i) if (up[i][u] != up[i][v]) {
		u = up[i][u]; 
		v = up[i][v];
	}

	return {up[0][u], {u, v}};
}

void kakuai() {
	cin >> n >> m; 
	for (int i = 1; i < n; ++i) {
		int u, v; 
		cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u);
	}

	int k = m - (n - 1);

	dfs_build(1, 1); 

	int res = 0; 

	for (int i = 1; i <= k; ++i) {
		int u, v; 
		cin >> u >> v; 

		if (depth[u] < depth[v]) swap(u, v);

		edges.emplace_back(u, v);

		auto x = lca(u, v); 

		int par = x.first; 
		int c, d; 
		tie(c, d) = x.second;

		// cerr << par << ' ' << c << ' ' << d << '\n';

		if (c != -1) {
			diff[c]++; 
			res -= diff[c];
		}

		if (d != -1) {
			diff[d]++; 
			res -= diff[d]; 
		}
		
		if (c != -1 && d != -1) {
			res -= mark[{max(c, d), min(c, d)}];
			mark[{max(c, d), min(c, d)}]++;
		}
	}

	dfs(1, 0, 0); 

	// cout << res << ' '; 

	for (auto &x : edges) {
		int u = x.first; 
		int v = x.second; 

		auto d = lca(u, v); 
		int l = d.first; 

		res += sumtoRoot[u] + sumtoRoot[v] - 2 * sumtoRoot[l];
	}

	cout << res; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "e"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}