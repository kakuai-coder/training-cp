/*
	Author: tinhnopro
	created: 2025.04.13 21:40:23
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 10
#endif // LOCAL

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, T b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 2e5 + 5; 
const i64 inf = (i64) 1e18;

int n, k; 
vector<pair<int, int> > adj[maxN];
i64 f[maxN], g[maxN];

i64 X; 
int c = 0; 

void dfs(int u, int par, i64 d) {
    f[u] = 0; 
    g[u] = inf; 

    for (auto &x : adj[u]) {
        int v = x.first; 
        int w = x.second; 
        if (v == par) continue;
        
        dfs(v, u, w); 

        maximize(f[u], f[v] + w); 
        minimize(g[u], g[v] + w);
    }

    if (f[u] + g[u] <= X) {
        f[u] = -inf; 
    } else if (f[u] + d > X) {
        ++c; 
        g[u] = 0; 
        f[u] = -inf;
    }
}

int cnt(i64 L) {
	X = L; 
	c = 0; 
	dfs(1, 0, inf); 
	
	// cout << c << ": ";
	// for (int i = 1; i <= n; ++i) {
	// 	cout << i << ' ' << g[i] << ' ' << f[i] << '\n';
	// }

	return c; 
}

void tinhnop() {
	cin >> n >> k; 

	for (int i = 1; i < n; ++i) {
		int u, v, w; 
		cin >> u >> v >> w; 
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}

	// cnt(29);


	i64 l = -1, r = (i64) 1e16; 
	while (r - l > 1) {
		i64 mid = (l + r) >> 1LL; 
		if (cnt(mid) <= k) {
			r = mid; 
		} else l = mid; 
	}
 
	cout << r << '\n';
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "c"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}