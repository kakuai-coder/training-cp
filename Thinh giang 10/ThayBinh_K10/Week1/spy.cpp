/*
	Author: tinhnopro
	created: 02.04.2025 22:38:45
*/
#include <bits/stdc++.h>

#define CHERRY "spy"

using namespace std;

using i64 = long long;
#define int long long 

int n, m, i1, j1, i2, j2;

bool c[205][205];

int d[205][205][5];

const int oo = 1e16;

struct DATA{
	int x, y, h;
};

int dx[] = {0, 1, 0, -1, 0};
int dy[] = {0, 0, 1, 0, -1};

void bfs(){
	memset(d, 0x3f, sizeof(d));

	queue < DATA > q;
	q.push({i1, j1, 0});

	d[i1][j1][0] = 0;

	while (q.size()){
		DATA v = q.front(); 
		q.pop();

		int x = v.x;
		int y = v.y;
		int h = v.h;

		for (int i = 1; i <= 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 > nx || nx > n || 0 > ny || ny > m)
				continue;
			if (c[nx][ny])
				continue;
			if (i == h)
				continue;
			if (d[nx][ny][i] > 1 + d[x][y][h]){
					d[nx][ny][i] = 1 + d[x][y][h];
					q.push({nx, ny, i});
			}
		}
	}
}

void solve() {
	cin >> n >> m >> j1 >> i1 >> j2 >> i2;

	int x, y;

	while (cin >> x >> y){
		c[y][x] = 1;
	}

	bfs();

	int ans = oo;

	for (int i = 1; i <= 4; i ++)
		if (ans >= d[i2][j2][i])
			ans = d[i2][j2][i];
		
	if (ans == oo)
		cout << "NO";
	else
		cout << ans;

	return void(cout << '\n');
}

int32_t main() {
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