/*
	Author: kakuai
	created: 2025.07.02 22:34:00
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 2e5 + 5; 
const int LOG = 17;

int n, q; 
vector<int> adj[maxN];
int depth[maxN], up[LOG + 1][maxN];

void dfs(int u, int par) {
	up[0][u] = par; 
	for (int i = 1; i <= LOG; ++i) up[i][u] = up[i - 1][up[i - 1][u]];

	for (int v : adj[u]) if (v != par) {
		depth[v] = depth[u] + 1; 
		dfs(v, u); 
	}
}

int lca(int& u, int& v) {
	if (u == v) return u; 

	if (depth[u] < depth[v]) swap(u, v); 

	int k = depth[u] - depth[v]; 
	for (int i = 0; i <= LOG; ++i) if ((k >> i) & 1) {
		u = up[i][u]; 
	}

	if (u == v) return u; 

	for (int i = LOG; ~i; --i) if (up[i][u] != up[i][v]) {
		u = up[i][u];  
		v = up[i][v];
	}

	return up[0][u];
}

void kakuai() {
	cin >> n >> q; 
	for (int i = 2; i <= n; ++i) {
		int u; 
		cin >> u; 
		adj[u].push_back(i); 
		adj[i].push_back(u);
	}

	dfs(1, 1);

	int u, v; 
	while (q--) {
		cin >> u >> v; 
		cout << lca(u, v) << '\n';
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b1"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}