/*
	Author: tinhnopro
	created: 2025.06.18 14:38:29
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

struct edge_t {
	int u, v, w; 

	edge_t(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

	bool operator <(const edge_t &other) const {
		if (w == other.w) return u < other.u; 
		return w < other.w; 	
	}
};

const int maxN = 1e5 + 5; 

vector<edge_t> edges; 

int n, m; 

int dp[maxN], pre[maxN];

void tinhnop() {
	cin >> n >> m; 
	for (int i = 1; i <= m; ++i) {
		int u, v, w; 
		cin >> u >> v >> w; 
		edges.push_back({u, v, w});
	}

	sort(edges.begin(), edges.end());

	for (int i = 2; i <= n; ++i) {
		dp[i] = pre[i] = -1e9 - 11;
	}

	for (int i = 0, fi, last; i < ssize(edges); ++i) {
		fi = i; 
		last = i; 
	
		while (i + 1 < ssize(edges) && edges[i + 1].w == edges[i].w) {
			i++; 
			last = i;
		}

		
		for (int j = fi; j <= last; ++j) {
			int u = edges[j].u; 
			int v = edges[j].v; 
			maximize(dp[u], pre[v] + 1);
			maximize(dp[v], pre[u] + 1); 
		}

		for (int j = fi; j <= last; ++j) {
			int u = edges[j].u; 
			int v = edges[j].v; 
			pre[u] = dp[u]; 
			pre[v] = dp[v];
		}
	}

	for (int i = 1; i <= n; ++i) cout << max(dp[i], 0) << ' ';
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "g"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}