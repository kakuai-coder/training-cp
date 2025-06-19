/*
	Author: tinhnopro
	created: 2025.06.18 21:08:18
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

const int maxN = 6009;

int n, m;
vector<int> adj[maxN];
vector<pair<int, int>> edges; 
int vist[maxN]; 
i64 d[maxN], cnt[maxN];

i64 ans = (i64) 1e18 + 11, tot = 0; 

void bfs(int u, int v) {
	queue<int> q;
	memset(vist, 0, sizeof(vist)); 
	memset(d, 0x3f, sizeof(d)); 
	memset(cnt, 0, sizeof(cnt));
	q.push(u);

	cnt[u] = 1; 
	d[u] = 1; 

	while (!q.empty()) {
		int x = q.front(); 
		q.pop();
		vist[x] = 1; 

		for (int w : adj[x]) if (!vist[w]) {
			if ((u == x && w == v) || (v == x && w == u)) continue;
			if (d[w] > d[x] + 1) {
				d[w] = d[x] + 1; 
				cnt[w] = cnt[x]; 
				q.push(w);
			} else if (d[w] == d[x] + 1) {
				cnt[w] += cnt[x];
			}
		}
	}

	if (ans > d[v]) {
		ans = d[v];
		tot = cnt[v];
	} else if (ans == d[v]) {
		tot += cnt[v];
	}
}

void tinhnop() {
	cin >> n >> m; 
	for (int i = 1; i <= m; ++i) {
		int u, v; 
		cin >> u >> v;
		adj[u].push_back(v); 
		adj[v].push_back(u);
		edges.push_back({u, v});
	}

	for (auto &e : edges) {
		int u = e.first; 
		int v = e.second; 

		bfs(v, u);
	}

	// cout << tot << ' ' << ans << '\n';

	cout << tot / ans; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "j"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}