/*
	Author: kakuai
	created: 2025.06.23 21:29:50
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 1e5 + 11; 
const int inf = 1e9 + 11; 

int n, m, k; 
int cnt[maxN], idx[maxN];
vector<pair<int, int>> adj[maxN], vec;
int dist[20][maxN];
pair<int, int> edges[maxN];
priority_queue<pair<int, int> > pq; 
int dp[maxN];

void Dijsktra(int id) {
	for (int i = 1; i <= n; ++i) {
		dist[id][i] = inf; 
	}

	int s = edges[idx[id]].second;

	dist[id][s] = 0; 

	pq.push({0, s});

	while (pq.size()) {
		int u = pq.top().second;
		int d_u = pq.top().first; 
		pq.pop(); 

		if (d_u > dist[id][u]) continue;

		for (auto &x : adj[u]) {
			int v = x.first; 
			int w = x.second; 

			if (dist[id][v] > dist[id][u] + w) {
				dist[id][v] = dist[id][u] + w; 
				pq.push({-dist[id][v], v});
			}
		}
	}
}

void kakuai() {
	cin >> n >> m >> k; 
	for (int i = 1; i <= k; ++i) cin >> idx[i];

	for (int i = 1; i <= m; ++i) {
		int u, v, c; 
		cin >> u >> v >> c; 
		cnt[u]++; 
		cnt[v]--; 
		adj[u].push_back({v, c}); 
		edges[i] = {u, v};
	}

	for (int i = 1; i <= k; ++i) {
		int id = idx[i];
		vec.push_back({edges[id].second, edges[id].first});
	}

	for (int i = 1; i <= k; ++i) Dijsktra(i);

	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0; 
	for (int msk = 0; msk < (1 << k); ++msk) {
		int id = __builtin_popcount(msk); 
		for (int i = 0; i < k; ++i) if (!((msk >> i) & 1)) {
			minimize(dp[msk | (1 << i)], dp[msk] + dist[id + 1][vec[i].second]);   
		}
	}

	int full = (1 << k) - 1; 

	if (dp[full] >= inf) {
		cout << -1;
	} else cout << dp[full];
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
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}