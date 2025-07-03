/*
	Author: kakuai
	created: 2025.07.01 21:01:18
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

const int maxN = 3e5 + 5; 

int n, m, q; 
vector<int> adj[maxN];
int lab[maxN], maxDist[maxN], far, maxdepth;

int findPar(int u) {
	return lab[u] < 0 ? u : lab[u] = findPar(lab[u]);
}

int getCenter(int x) {
	return (x + 1) / 2; 
}

void join(int u, int v) {
	u = findPar(u); 
	v = findPar(v); 

	if (u == v) return ; 
	
	if (lab[u] > lab[v]) swap(u, v); 

	lab[u] += lab[v]; 
	lab[v] = u; 
}

void joinSet(int u, int v) {
	u = findPar(u); 
	v = findPar(v); 

	if (u == v) return ; 
	
	if (lab[u] > lab[v]) swap(u, v); 

	lab[u] += lab[v]; 
	lab[v] = u; 

	maximize(maxDist[u], max(maxDist[v], getCenter(maxDist[u]) + getCenter(maxDist[v]) + 1));
}

void dfs(int u, int par, int depth) {

	if (maximize(maxdepth, depth)) far = u;

	for (int v : adj[u]) if (v != par) {
		dfs(v, u, depth + 1);
	}
}

void kakuai() {
	cin >> n >> m >> q; 

	for (int i = 1; i <= n; ++i) {
		lab[i] = -1; 
		maxDist[i] = 0; 
	}

	for (int i = 1; i <= m; ++i) {
		int u, v; 
		cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u);
		join(u, v);
	}

	for (int i = 1; i <= n; ++i) if (lab[i] < 0) {

		far = 0, maxdepth = 0; 

		dfs(i, 0, 0);

		maxdepth = 0; 
		dfs(far, 0, 0);

		maxDist[i] = maxdepth;
	}

	while (q--) {
		int op; 
		cin >> op; 

		if (op == 1) {
			int x; cin >> x; 
			int u = findPar(x); 
			cout << maxDist[u] << '\n';
		} else {
			int x, y; 
			cin >> x >> y; 
			joinSet(x, y);
		}
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "a2"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}