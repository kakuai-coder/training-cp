/*
	Author: tinhnopro
	created: 2025.04.15 07:29:00
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

const int maxN = 2e5 + 5; 
const int mod = 1e9 + 7; 
const i64 inf = (i64) 1e15 + 5; 

struct Node {
	i64 w; 
	bool buy; 
	int u; 

	Node(int _u, i64 _w, bool _buy) : u(_u), w(_w), buy(_buy) {}

	bool operator <(const Node &other) const {
		return w > other.w;
	}
};

int n, m, k; 
vector<pair<int, int> > adj[maxN]; 
int a, b, cost[maxN];
i64 dist[maxN][2];

void Dijsktra(int s) {
	priority_queue<Node> pq;
	for (int i = 1; i <= n; ++i) dist[i][0] = dist[i][1] = inf; 
	dist[s][0] = 0; 
	pq.emplace(s, 0, 0);
	
	while (!pq.empty()) {
		Node x = pq.top(); 
		pq.pop();
		if (x.w > dist[x.u][x.buy]) continue;

		if (cost[x.u] && x.buy == 0 && dist[x.u][1] > dist[x.u][0] + cost[x.u]) {
			dist[x.u][1] = dist[x.u][0] + cost[x.u]; 
			pq.emplace(x.u, dist[x.u][1], 1);
		}

		for (auto d : adj[x.u]) {
			int v = d.first; 
			int w = d.second; 

			if (x.buy == 1) {
				if (dist[v][1] > dist[x.u][1] + w) {
					dist[v][1] = dist[x.u][1] + w; 
					pq.emplace(v, dist[v][1], 1);
				} 
			} else {
				if (dist[v][0] > dist[x.u][0] + w) {
					dist[v][0] = dist[x.u][0] + w; 
					pq.emplace(v, dist[v][0], 0);
				}
			}
		}
	}
}

void tinhnop() {
	cin >> n >> m >> k >> a >> b;
	for (int i = 1; i <= k; ++i) {
		int u, c;
		cin >> u >> c; 
		cost[u] = c; 
	} 

	for (int i = 1; i <= m; ++i) {
		int u, v, c; 
		cin >> u >> v >> c; 
		adj[u].emplace_back(v, c); 
		adj[v].emplace_back(u, c); 
	}	
	
	Dijsktra(a); 
	cout << dist[b][1]; 
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