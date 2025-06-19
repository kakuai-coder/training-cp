/*
	Author: tinhnopro
	created: 2025.04.15 09:47:38
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

const int maxN = 5e4 + 5; 
const i64 inf = (i64) 1e16 + 5; 

int n, m; 
vector<pair<int, int> > g1[maxN], g2[maxN], g3[maxN];
int cnt[maxN], cost[maxN][2];
i64 dist1[maxN], dist2[maxN], dist3[maxN];
pair<int, int> edges[maxN];

void Dijsktra(int s, i64 *dist, vector<pair<int, int> > *adj) {
	for (int i = 1; i <= n; ++i) dist[i] = inf; 
	dist[s] = 0; 
	priority_queue<pair<i64, int>, vector<pair<i64, int> >, greater<pair<i64, int> > > pq;
	pq.emplace(0, s); 

	while (!pq.empty()) {
		int u = pq.top().second; 
		i64 d_u = pq.top().first; 
		pq.pop();
		if (d_u > dist[u]) continue;
		for (auto x : adj[u]) {
			int v = x.first; 
			int w = x.second;

			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w; 
				pq.emplace(dist[v], v);
			}
		}
	}
}

void tinhnop() {
	cin >> n >> m; 
	for (int i = 1; i <= m; ++i) {
		int u, v, w1, w2; 
		cin >> u >> v >> w1 >> w2; 
		cost[i][0] = w1; 
		cost[i][1] = w2; 
		edges[i] = {u, v}; 
		g1[v].push_back({u, w1});
		g2[v].push_back({u, w2});
	}

	Dijsktra(n, dist1, g1); 
	Dijsktra(n, dist2, g2);

	for (int i = 1; i <= m; ++i) {
		int k = 0; 
		int u, v;
		tie(u, v) = edges[i];
		k += dist1[u] < dist1[v] + cost[i][0];
		k += dist2[u] < dist2[v] + cost[i][1];


		// cout << u << ' ' << v << ' ' << k << '\n';
		g3[u].push_back({v, k});
	}

	Dijsktra(1, dist3, g3);

	cout << dist3[n]; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "a4"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}