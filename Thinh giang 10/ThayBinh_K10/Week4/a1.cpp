/*
	Author: tinhnopro
	created: 2025.06.14 11:55:42
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

	bool operator < (const edge_t &other) const {
		return w < other.w; 
	}
};

int n, k, m, p; 
vector<edge_t> edges;
 
void tinhnop() {
	cin >> n >> k >> m >> p; 

	for (int i = 1; i <= k; ++i) {
		int u, v, d; 
		cin >> u >> v >> d; 

		edges.push_back({u, v, d});
	}

	sort(edges.begin(), edges.end());

	
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "a1"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}