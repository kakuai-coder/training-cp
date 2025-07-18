/*
	Author: tinhnopro
	created: 2025.04.16 20:05:59
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
};

const int maxN = 2e5 + 5; 
const i64 inf = (i64) 1e18 + 5;

int n, m;
vector<edge_t> edges;

i64 dist[maxN];
int trace[maxN];

void tinhnop() {
	cin >> n >> m; 
	for (int i = 1; i <= m; ++i) {
		int u, v, w; 
		cin >> u >> v >> w;
		edges.push_back({u, v, w});
	}


	for (int i = 2; i <= n; ++i) dist[i] = inf; 
	int st; 

	for (int i = 1; i <= n; ++i) {
		st = -1; 
		for (edge_t &x : edges) {
			int u = x.u;
			int v = x.v; 
			int w = x.w; 

			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				trace[v] = u; 
				st = v;
			}
		}
	}

	if (st == -1) return void(cout << "NO");

	int u = st; 
	for (int i = 0; i < n; ++i) u = trace[u]; 

	vector<int> cycle; 

	cycle.push_back(u);
	int cur = trace[u];
	while (cur != u) {
		cycle.push_back(cur);
		cur = trace[cur]; 
	}
	cycle.push_back(u);

	reverse(cycle.begin(), cycle.end()); 

	cout << "YES\n"; 

	for (int x : cycle) cout << x << ' ';
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b4"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}