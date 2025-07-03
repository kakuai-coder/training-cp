/*
	Author: kakuai
	created: 2025.07.03 09:23:02
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

const int MaxN = 105;
const int MaxK = 10009;
const int Inf = 1e9 + 11;

struct node_t {
	int v, w, c;
	node_t(int _v, int _w, int _c) : v(_v), w(_w), c(_c) {}
	node_t() { v = w = c = 0; }
};

int n, m, k;
vector<node_t> adj[MaxN];
int dist[MaxN][MaxK];

void SPFA() {
	queue<pair<int, int>> q; // (u, c)
	bool inQueue[MaxN][MaxK] = {};

	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= k; ++j)
			dist[i][j] = Inf;

	dist[1][k] = 0;
	q.emplace(1, k);
	inQueue[1][k] = true;

	while (!q.empty()) {
		auto [u, c] = q.front(); q.pop();
		inQueue[u][c] = false;

		for (auto &e : adj[u]) {
			if (e.c > c) continue;

			int v = e.v;
			int nc = c - e.c;
			int nd = dist[u][c] + e.w;

			if (dist[v][nc] > nd) {
				dist[v][nc] = nd;
				if (!inQueue[v][nc]) {
					q.emplace(v, nc);
					inQueue[v][nc] = true;
				}
			}
		}
	}
}

void kakuai() {
	cin >> n >> m >> k;

	for (int i = 1; i <= m; ++i) {
		int u, v, w, c;
		cin >> u >> v >> w >> c;
		adj[u].emplace_back(v, w, c);
	}

	SPFA();

	int ans = Inf;
	for (int c = 0; c <= k; ++c)
		minimize(ans, dist[n][c]);

	cout << (ans == Inf ? -1 : ans);
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "shortest"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}
