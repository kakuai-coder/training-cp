/*
	Author: tinhnopro
	created: 04.04.2025 07:25:43
*/
#include <bits/stdc++.h>

#define CHERRY "circus"

using namespace std;

using i64 = long long;

const int maxN = 55; 

int n, m, cs, ct, xst, yst, xen, yen; 
int dist[maxN][maxN][6][6];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};

char a[maxN][maxN]; 

struct Data {
	int x, y, c, h; 

	Data() {
		x = y = c = h = 0; 
	}

	Data(int _x, int _y, int _z, int _h) : x(_x), y(_y), c(_z), h(_h) {}
};

void bfs() {
	memset(dist, 0x3f, sizeof(dist)); 
	queue<Data> q;

	q.emplace(xst, yst, cs, 0);
	dist[xst][yst][cs][0] = 0;

	while (!q.empty()) {
		Data v = q.front(); 
		q.pop();

		if (v.x == xen && v.y == yen && v.c == ct) {
			cout << dist[v.x][v.y][v.c][v.h] << '\n'; 
			return ; 
		}

		int x, y, c, h; 
		x = v.x; y = v.y; c = v.c; h = v.h; 

		// Case 1 
		int nx = x + dx[h]; 
		int ny = y + dy[h]; 
		int nc = c - 1; 
		if (nc == 0) nc = 5;
		
		if (1 > nx || nx > n || 1 > ny || ny > m || a[nx][ny] == '#') {

		} else {
			if (dist[nx][ny][nc][h] > dist[x][y][c][h] + 1) {
				dist[nx][ny][nc][h] = dist[x][y][c][h] + 1; 
				q.emplace(nx, ny, nc, h);
			}
		}

		// Case 2 
		if (h < 2) {
			for (int i = 2; i <= 3; ++i) {
				if (dist[x][y][c][i] > dist[x][y][c][h] + 1) {
					dist[x][y][c][i] = dist[x][y][c][h] + 1;					
					q.emplace(x, y, c, i);
				}
			}
		} else {
			for (int i = 0; i <= 1; ++i) {
				if (dist[x][y][c][i] > dist[x][y][c][h] + 1) {
					dist[x][y][c][i] = dist[x][y][c][h] + 1;					
					q.emplace(x, y, c, i);
				}
			}
		}
	}

	cout << -1;
}

void solve() {
	cin >> n >> m >> cs >> ct;
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j]; 
			if (a[i][j] == 'S') {
				xst = i; 
				yst = j; 
			} else if (a[i][j] == 'T') {
				xen = i; 
				yen = j; 
			}
		}
	}

	bfs();
	
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