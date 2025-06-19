/*
	Author: tinhnopro
	created: 2025.04.09 07:13:33
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

const int maxN = 3e5 + 5; 

int n, m; 
vector<int> adj[maxN];
vector<int> biconnected, stk;
int low[maxN], num[maxN]; 


void build_dfs(int u, int par) {
	static int timeDFS = 0; 
	low[u] = num[u] = ++timeDFS; 

	stk.push_back(u); 

	for (int v : adj[u]) if (v != par) {
		if (!num[v]) {
			build_dfs(v, u);
			minimize(low[u], low[v]);

			if (low[v] >= num[u]) {
				int cnt = 0, d = -1; 
				do {
					d = stk.back(); 
					stk.pop_back();
					cnt++;
				} while (d != v);
				biconnected.push_back(cnt);
			}
		} else minimize(low[u], num[v]);
	}
}

void tinhnop() {
	cin >> n >> m; 

	if (m == 0) {
		cout << 1; 
		return ; 
	}

	for (int i = 1, u, v; i <= m; ++i) {
		cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u);
	}

	for (int i = 1; i <= n; ++i) if (!num[i]) build_dfs(i, i); 

	// for (int x : biconnected) cout << x << '\n';
	
	cout << 1 + *max_element(biconnected.begin(), biconnected.end());
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry ""
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}