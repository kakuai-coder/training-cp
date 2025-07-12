/*
	Author: kakuai
	created: 2025.07.03 13:14:07
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

const int maxN = 1e6 + 5; 
const int Log = 20;

int n, q; 
vector<pair<int, int> > adj[maxN];
int depth[maxN], up[Log + 1][maxN], h[maxN];

void dfs(int u, int par) {
	up[0][u] = par; 
	for (int i = 1; i <= Log; ++i) up[i][u] = up[i - 1][up[i - 1][u]];
	
	for (auto &x : adj[u]) {
		int v = x.first; 
		int c = x.second;

		if (v == par) continue;

		h[v] = h[u] + c; 
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

void kakuai() {
	cin >> n; 
	for (int i = 2; i <= n; ++i) {
		int p, c; 
		cin >> p >> c; 
		adj[p].emplace_back(i, c);
	}

	cin >> q;

	dfs(1, 0);

	while (q--) {
		int u, v, c; 
		cin >> u >> v >> c; 
		int dist = h[u] + h[v] - 2 * h[lca(u, v)];

		cout << min(h[u], h[v] + c) + min(dist, c) << '\n';
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b6"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}