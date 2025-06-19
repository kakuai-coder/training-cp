/*
	Author: tinhnopro
	created: 2025.04.16 22:44:06
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

int m, n; 

set<pair<int, int> > mark;
vector<int> adj[150];
int deg[150], vist[150];
int cnt = 0; 

void dfs(int u) {
	vist[u] = 1;
	if (deg[u] & 1) cnt++;  
	for (int v : adj[u]) if (!vist[v]) {
		dfs(v);
	}
}

void tinhnop() {
	cin >> m >> n;
	for (int i = 1; i <= n; ++i) {
		int u, v; 
		cin >> u >> v; 
		if (u > v) swap(u, v);
		mark.insert({u, v});
	}

	for (int i = 0; i <= m; ++i) {
		for (int j = i; j <= m; ++j) {
			if (!mark.count({i, j})) {
				adj[i].push_back(j); 
				adj[j].push_back(i);
				deg[i]++; 
				deg[j]++;
			}
		}
	}

	int res = 0; 

	for (int i = 0; i <= m; ++i) if (!vist[i]) {
		cnt = 0;
		dfs(i);

		if (adj[i].size() == 0) continue;

		if (cnt == 0) res++; 
		else res += cnt / 2; 
	}

	cout << res; 
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
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}