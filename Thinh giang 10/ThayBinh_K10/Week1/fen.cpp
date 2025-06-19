	/*
		Author: tinhnopro
		created: 02.04.2025 16:40:16
	*/
	#include <bits/stdc++.h>

	#define CHERRY "fen"

	using namespace std;

	using i64 = long long;

	int n, m, a[55][55], dist[55][55];

	int dx[5] = {1, 0, -1, 0, 0}; 
	int dy[5] ={0, 1, 0, -1, 0};

	void bfs(int i, int j) {
		memset(dist, 0x3f, sizeof(dist));
		queue<pair<int, int> > q; 
		q.emplace(i, j); 

		dist[i][j] = 0;

		while (!q.empty()) {
			int x, y; 
			tie(x, y) = q.front(); 
			q.pop(); 

			int c = (dist[x][y] + 1) % 4;

			if (x == 1 && y == m) return ;


			for (int i = 0; i < 5; ++i) {
				int xx = x + dx[i]; 
				int yy = y + dy[i]; 

				if (xx == 0 || xx > n || yy == 0 || yy > m) continue;

				if (a[xx][yy] == c) continue;

				if (xx == x && yy == y) {
					dist[xx][yy] = dist[x][y] + 1; 
					q.emplace(xx, yy);
					continue;
				}

				if (dist[xx][yy] > dist[x][y] + 1) {
					dist[xx][yy] = dist[x][y] + 1;
					q.emplace(xx, yy);
				}
			}
		}
	}

	void solve() {
		cin >> n >> m; 

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				cin >> a[i][j]; 
			}
		}

		bfs(n, 1);

		cout << dist[1][m];

		return void(cout << '\n');
	}

	int main() {
		ios::sync_with_stdio(false);
		cin.tie(nullptr);

		if (fopen(CHERRY".inp", "r")) {
			freopen(CHERRY".inp", "r", stdin);
			freopen(CHERRY".out", "w", stdout);
		}

		int t = 1; 
		// cin >> t;

		for (int i = 1; i <= t; ++i) {
			cerr << "Case #" << i << '\n';
			solve();
		}

		cerr << "[runtime] " << 1.0 * clock() / CLOCKS_PER_SEC << "[ms]";

		return 0; 
	}