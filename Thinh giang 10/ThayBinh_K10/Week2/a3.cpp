/*
	Author: tinhnopro
	created: 2025.04.10 00:27:18
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

const int maxN = 1e5 + 5; 

template <typename T> 
struct DisjointSet {
	T par[maxN];
	int mx[maxN];

	void init(int n){
		for (int i = 1; i <= n; i ++){
			par[i] = -1;
			mx[i] = i;
		}
	}

	int f(int i){
		if (par[i] < 0)
			return i;
		return par[i] = f(par[i]);
	}

	int sz(int i){
		return -par[f(i)];
	}

	void Merge(int x, int y){
		x = f(x);
		y = f(y);
		if (x == y)
			return;
		if (par[x] > par[y])
			swap(x, y);
		par[x] += par[y];
		par[y] = x;
		maximize(mx[x], mx[y]);
	}
};

int n, m; 
vector<int> adj[maxN], bridge_tree[maxN];
int low[maxN], num[maxN]; 
DisjointSet<int> dsu;

void dfs(int u, int par) {
	static int timeDFS = 0;
	low[u] = num[u] = ++timeDFS;

	for (int v : adj[u]) if (v != par) {
		if (!num[v]) {
			dfs(v, u);
			minimize(low[u], low[v]);
			
			if (low[v] > num[u]) {
				bridge_tree[u].push_back(v);
				bridge_tree[v].push_back(u);
				dsu.Merge(u, v);
			}
		} else minimize(low[u], num[v]);
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

	dsu.init(n);

	for (int i = 1; i <= n; ++i) if (!num[i]) dfs(i, i);

	i64 res = 0; 

	for (int i = 1; i <= n; ++i) {
		res += dsu.sz(i) - 1 - bridge_tree[i].size();
	}

	cout << res / 2; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "a3"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}