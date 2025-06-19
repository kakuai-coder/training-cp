/*
	Author: tinhnopro
	created: 2025.04.15 08:30:05
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

const int maxN = 1011; 
const i64 inf = (i64) 1e16 + 1; 

int a, b, n;
pair<i64, i64> adj[maxN][maxN];
i64 dist[maxN], cnt_id[maxN], vist[maxN]; 

void Dijsktra() {
	priority_queue<pair<i64, int>, vector<pair<i64, int> > , greater<pair<i64, int> > > pq;
	for (int i = 1; i <= 1000; ++i) dist[i] = cnt_id[i] = inf; 
	dist[a] = 0; 
	cnt_id[a] = 0; 
	pq.emplace(0, a); 
	
	while (!pq.empty()) {
		i64 d_u = pq.top().first;
		int u = pq.top().second; 
		pq.pop(); 
		if (vist[u]) continue;
		vist[u] = 1; 
		if (d_u > dist[u]) continue;

		for (int v = 1; v <= 1000; ++v) {
			if (v == u) continue;
			if (dist[v] > dist[u] + adj[u][v].first) {
				dist[v] = dist[u] + adj[u][v].first; 
				cnt_id[v] = cnt_id[u] + adj[u][v].second; 
				pq.emplace(dist[v], v);
			} else if (dist[v] == dist[u] + adj[u][v].first) {
				if (minimize(cnt_id[v], cnt_id[u] + adj[u][v].second)) pq.emplace(dist[v], v);
			}
		}
	}
}
 
void tinhnop() {
	cin >> a >> b >> n; 

	for (int i = 1; i <= 1000; ++i) {
		for (int j = 1; j <= 1000; ++j) adj[i][j] = {inf, inf};
	}

	for (int i = 1; i <= n; ++i) {
		int w, k; 
		cin >> w >> k;
		vector<int> v;  
		for (int j = 1; j <= k; ++j) {
			int x; cin >> x; 
			v.push_back(x);
		}

		for (int j = 0; j < k - 1; ++j) {
			for (int j2 = j + 1; j2 < k; ++j2) {
				if (minimize(adj[v[j]][v[j2]].first, 1LL * w)) {
					adj[v[j]][v[j2]].second = j2 - j; 
				}
			}
		}
	}

	Dijsktra(); 

	if (dist[b] == inf) {
		cout << -1 << ' ' << -1; 
		return ; 
	}

	cout << dist[b] << ' ' << cnt_id[b];
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "citybus"
	if (fopen(cherry".in", "r")) {
		freopen(cherry".in", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}