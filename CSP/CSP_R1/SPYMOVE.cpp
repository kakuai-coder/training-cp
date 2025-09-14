/*
	Author: kakuai
	created: 2025.07.05 09:59:22
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

const int maxN = 1e5 + 5; 

int n, m, k, a[maxN], b[maxN]; 
vector<int> adj[maxN];
int dist[maxN][1 << 6], vist[maxN][1 << 6];

void bfs() {
	queue<pair<int, int> > q; 
	memset(dist, 0x3f, sizeof(dist));
	memset(vist, 0, sizeof(vist));
	
	int mask = (b[1] == 0 ? 0 : (1 << b[1]));

	dist[1][mask] = 0;

	q.emplace(1, mask);
	
	while (!q.empty()) {
		int u = q.front().first; 
		int mask = q.front().second; 

		q.pop();

		// cerr << u << ' ' << mask << '\n';

		vist[u][mask] = 1; 

		for (int v : adj[u]) {

			if (a[v] != 0 && !((mask >> a[v]) & 1)) continue; 

			int new_bit = (b[v] == 0 ? 0 : (1 << b[v]));

			if (!vist[v][mask | new_bit] && dist[v][mask | new_bit] > dist[u][mask] + 1) {
				dist[v][mask | new_bit] = dist[u][mask] + 1; 
				q.emplace(v, mask | new_bit);
			}
		}
	}
} 

void kakuai() {
	cin >> n >> m >> k; 

	for (int i = 1; i <= n; ++i) {
		cin >> a[i];

		if (a[i] == -1) a[i] = 0; 
	}

	for (int i = 1; i <= n; ++i) {
		cin >> b[i];

		if (b[i] == -1) b[i] = 0;
	}

	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v; 
		adj[u].push_back(v);
		adj[v].push_back(u); 
	}

	bfs();

	k++;

	for (int i = 1; i <= n; ++i) {
		if (a[i] == 0) {
			int ans = 1e9 + 11; 
			for (int mask = 0; mask < (1 << k); ++mask) minimize(ans, dist[i][mask]);
			
			cout << (ans >= 1e9 + 11 ? -1 : ans) << ' ';
		} else {
			int ans = 1e9 + 11; 

			for (int mask = 0; mask < (1 << k); ++mask) if ((mask >> a[i]) & 1) 
				minimize(ans, dist[i][mask]);

			cout << (ans >= 1e9 + 11 ? -1 : ans) << ' ';
		}
	}
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "spymove"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();
	
	return 0;
}