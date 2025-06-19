/*
	Author: tinhnopro
	created: 2025.06.07 22:45:42
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

int dx[] = {1, 0, -1, 0}; 
int dy[] = {0, 1, 0, -1};
int n, m; 
char a[25][25];
int x_st, y_st, x_bx, y_bx, x_en, y_en, vis[25][25], vis_p[25][25];

struct Data {
	int xp, yp, xb, yb, step, push; 
} d, d2;

struct Data2 {
	int x, y, step;
} now;

bool inMaze(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m) return false;
	if (a[x][y] == '#') return false; 
	return true; 
}

bool bfs(int st_x, int st_y, int tx, int ty) {
	for (int i = 0; i < 25; ++i) {
		for (int j = 0; j < 25; ++j) vis_p[i][j] = 0; 
	}

	vis_p[st_x][st_y] = 1; 
	vis_p[d.xb][d.yb] = 1; 

	queue<Data2> qq;
	
	qq.push({st_x, st_y, 0});

	while (!qq.empty()) {
		now = qq.front(); 
		qq.pop();

		if (now.x == tx && now.y == ty) {
			return true; 
		}

		for (int i = 0; i < 4; ++i) {
			int xx = now.x + dx[i]; 
			int yy = now.y + dy[i]; 

			if (inMaze(xx, yy) && !vis_p[xx][yy]) {
				vis_p[xx][yy] = 1; 
				qq.push({xx, yy, now.step + 1});
			}
		}
	}

	return false; 
}

bool bfs1() {
	vis[x_bx][y_bx] = 1; 
	queue<Data> q; 

	q.push({x_st, y_st, x_bx, y_bx, 0, 0});

	while (!q.empty()) {
		d = q.front(); 
		q.pop(); 

		for (int i = 0; i < 4; ++i) {
			int nx = d.xb + dx[i]; 
			int ny = d.yb + dy[i];
			int tx = d.xb - dx[i]; 
			int ty = d.yb - dy[i];

			if (inMaze(nx, ny) && inMaze(tx, ty) && !vis[nx][ny]) {
				if (bfs(d.xp, d.yp, tx, ty)) {
					vis[nx][ny] = 1; 
					d2.xb = nx; 
					d2.yb = ny; 
					d2.xp = d.xb; 
					d2.yp = d.yb;

					d2.step = d.step + now.step + 1; 
					d2.push = d.push + 1;
					if (nx == x_en && ny == y_en) return true; 
					q.push(d2);
				}
			}
		}
	}

	return false; 
}

void tinhnop() {
	cin >> n >> m;
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j];
			if (a[i][j] == 'T') {
				x_en = i; 
				y_en = j; 
			}

			if (a[i][j] == 'S') {
				x_st = i; 
				y_st = j; 
			}

			if (a[i][j] == 'B') {
				x_bx = i; 
				y_bx = j; 
			}
		}
	}

	if (bfs1()) {
		cout << d2.push << ' ' << d2.step << '\n';
	} else cout << "Impossible.";
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "pushing"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}