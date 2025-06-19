/*
	Author: tinhnopro
	created: 2025.04.07 22:37:32
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

const int maxN = 505, maxV = 1e6; 

char c[maxN][maxN];
int m, n, xst, yst, xen, yen, dist[maxV]; 

int convert_vertex(int i, int j, int k) {
	return (i - 1) * n * 2 + (j - 1) * 2 + k;
}

void reconvert(int &i, int &j, int &k, int num) {
	i = num / (n * 2) + 1;
	int d = num % (n * 2);
	if (d & 1) {
		k = 1; d--;
	} else k = 0; 
	j = d / 2 + 1; 
}

bool isSafe(int i, int j, int k) {
	if (k == 1) {
		if (i == m) return false; 
		return c[i + 1][j] == '#';
	} else {
		if (i == 1) return false; 
		return c[i - 1][j] == '#';
	}
}

void bfs() {
	memset(dist, 0x3f, sizeof(dist));
	deque<int> q; 
	q.push_front(convert_vertex(xst, yst, 1));
	dist[convert_vertex(xst, yst, 1)] = 0;

	while (!q.empty()) {
		int x = q.front();
		q.pop_front(); 
		int i, j, k;
		reconvert(i, j, k, x); 

		// cout << x << ' ' << i << ' ' << j << ' ' << k << '\n';
		
		if (i == xen && j == yen) {
			cout << dist[x];
			return ; 
		}

		if (isSafe(i, j, k)) {
			for (int d : {1, -1}) {
				int ny = j + d; 
				if (1 > ny || ny > n) continue;
				if (c[i][ny] == '#') continue;
				
				int v = convert_vertex(i, ny, k);
				if (dist[v] > dist[x]) {
					dist[v] = dist[x]; 
					q.push_front(v);
				}
			}

			int v = convert_vertex(i, j, 1 ^ k);
			if (dist[v] > dist[x] + 1) {
				dist[v] = dist[x] + 1; 
				q.push_back(v);
			}
		} else {
			if (k == 0) {
				if (i == 1) continue;
				int v = convert_vertex(i - 1, j, k);
				if (dist[v] > dist[x]) {
					dist[v] = dist[x]; 
					q.push_front(v);
				}
			} else {
				if (i == m) continue;
				int v = convert_vertex(i + 1, j, k); 
				if (dist[v] > dist[x]) {
					dist[v] = dist[x]; 
					q.push_front(v);
				}
			}
		}
	}

	cout << -1; 
}

void tinhnop() {
	cin >> m >> n; 
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> c[i][j];
			if (c[i][j] == 'C') {
				xst = i; 
				yst = j; 
			} 
			if (c[i][j] == 'D') {
				xen = i; 
				yen = j; 
			} 
		}
	}

	bfs();
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "gravity"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}