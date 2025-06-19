/*
	Author: tinhnopro
	created: 2025.06.18 01:44:58
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

const int mod = 1e9 + 7; 	
const int maxN = 5e5 + 5; 

struct edge_t {
	int u, v, w; 
	edge_t(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
	

	bool operator < (const edge_t &other) const {
		return w < other.w; 
	}
};

int n, m;
vector<pair<int, int> > adj[maxN]; 

vector<edge_t> edges;

int vist[maxN];

int dfs(int u, int w, int d = 0) {
	int cur = 0;
	
	bool ok = false; 

	for (auto &x : adj[u]) {
		int v = x.first; 
		int wnxt = x.second; 

		if (wnxt != w + 1) continue;
		
		cur += dfs(v, wnxt, d + 1);
		ok = true; 
	}

	if (!ok) {
		int x = (1LL * d * (d + 1) / 2) % mod; 
		cout << u << ' ' << x << '\n';																					
		return x;   
	} 
	
	return cur; 
}

void tinhnop() {
	cin >> n >> m; 
	for (int i = 1; i <= m; ++i) {
		int u, v, w; 
		cin >> u >> v >> w; 
		adj[u].push_back({v, w}); 
		adj[v].push_back({u, w});
		edges.push_back({u, v, w});
	}

	sort(edges.begin(), edges.end());

	int res = 0; 

	for (auto &x : edges) {
		if (!vist[x.u]) {
			res += dfs(x.v, x.w, 1);
			if (res >= mod) res -= mod; 
		}
 	}

	cout << res; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "f"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}