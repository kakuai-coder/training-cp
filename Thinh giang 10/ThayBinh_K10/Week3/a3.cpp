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

const int maxN = 1e5 + 5; 
const int mod = 1e9 + 7; 
const i64 inf = (i64) 1e15 + 5; 

int n, m; 
vector<pair<int, int> > adj[maxN]; 
i64 dist[maxN], cnt[maxN], max_len[maxN], min_len[maxN];


void Dijsktra(int s) {
	priority_queue<pair<i64, int>, vector<pair<i64, int> > , greater<pair<i64, int> > > pq;
	for (int i = 1; i <= n; ++i) dist[i] = inf; 
	dist[s] = 0; 
	cnt[s] = 1; 
	pq.emplace(0, s); 

	while (!pq.empty()) {
		i64 d_u = pq.top().first;
		int u = pq.top().second; 
		pq.pop(); 

		if (d_u > dist[u]) continue;

		for (auto x : adj[u]) {
			int v = x.first;
			int w = x.second;

			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w; 
				max_len[v] = max_len[u] + 1; 
				min_len[v] = min_len[u] + 1; 
				cnt[v] = cnt[u];

				pq.emplace(dist[v], v);
			} else if (dist[v] == dist[u] + w) {
				maximize(max_len[v], max_len[u] + 1);
				minimize(min_len[v], min_len[u] + 1); 
				cnt[v] += cnt[u]; 
				if (cnt[v] > mod) cnt[v] -= mod;
			}
		}
	}
}

void tinhnop() {
	cin >> n >> m; 
	for (int i = 1; i <= m; ++i) {
		int u, v, c; 
		cin >> u >> v >> c; 
		adj[u].emplace_back(v, c); 
	}	

	Dijsktra(1); 

	cout << dist[n] << ' ' << cnt[n] << ' ' << min_len[n] << ' ' << max_len[n] << '\n'; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "a3"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}