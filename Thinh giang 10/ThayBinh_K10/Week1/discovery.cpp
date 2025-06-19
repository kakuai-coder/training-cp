/*
	Author: tinhnopro
	created: 2025.04.08 10:52:58
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

const int maxN = 1e6 + 5; 

char d[] = {'E', 'N', 'S', 'W'};
int dx[] = {1, 0, 0, -1};
int dy[] = {0, 1, -1, 0};

map<pair<int, int> , int> mark;
int adj[maxN][4], dist[maxN];
pair<int, int> trace[maxN]; 

void bfs(int sr) {
	memset(dist, 0x3f, sizeof(dist)); 
	queue<int> q; 
	q.push(sr);
	dist[sr] = 0; 

	while (!q.empty()) {
		int u = q.front(); 
		q.pop(); 

		for (int i = 0; i < 4; ++i) {
			if (adj[u][i] != 0) {
				int v = adj[u][i]; 
				if (dist[v] > dist[u] + 1) {
					dist[v] = dist[u] + 1;
					trace[v] = {u, i}; 
					q.push(v); 
				}
			}
		}
	}

	// cerr << dist[1] << '\n';

	int u = 1; 
	string path; 
	while (u != sr) {
		path.push_back(d[trace[u].second]);
		u = trace[u].first;
	}

	reverse(path.begin(), path.end());

	cout << path;
}

void tinhnop() {
	string s; cin >> s; 

	int x = 0, y = 0; 

	mark[{x, y}] = 1; 
	int u = 1, n = 1; 

	for (char c : s) {
		int i;
		for (i = 0; i < 4; ++i) if (d[i] == c) {
			x += dx[i]; 
			y += dy[i];
			break; 
		}
		int v; 
		if (mark.find({x, y}) == mark.end()) {
			n++;
			mark[{x, y}] = n; 
			v = n;
		} else v = mark[{x, y}];
		
		adj[u][i] = v; 
		if (i == 0) adj[v][3] = u; 
		if (i == 3) adj[v][0] = u; 
		if (i == 1) adj[v][2] = u; 
		if (i == 2) adj[v][1] = u;

		u = v; 
	}

	// for (int i = 1; i <= n; ++i) {
		// for (int j = 0; j < 4; ++j) cout << adj[i][j] << ' ';
		// cout << '\n';
	// }
	// cerr << "ok";

	bfs(u);	
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "discovery"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}