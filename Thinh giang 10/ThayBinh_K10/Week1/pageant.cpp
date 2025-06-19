/*
	Author: tinhnopro
	created: 02.04.2025 23:10:02
*/
#include <bits/stdc++.h>

#define CHERRY "pageant"

using namespace std;

using i64 = long long;

const int maxN = 55; 
const int inf = 1e9;

int n, m, c[maxN][maxN]; 
int min_group[3];
char a[maxN][maxN];
int dx[] = {0, 1, 0, -1}; 
int dy[] = {1, 0, -1, 0};
vector<pair<int, int> > group[3];

int cnt = 0;

void dfs(int x, int y) {
	c[x][y] = cnt; 
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i]; 
		int ny = y + dy[i];

		if (1 > nx || nx > n) continue;
		if (1 > ny || ny > m) continue;

		if (a[nx][ny] == '.') continue;

		a[nx][ny] = '.';

		dfs(nx, ny);
	}
}

int dist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

void solve() {
	cin >> n >> m; 

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j];
		}
	}

	memset(c, -1, sizeof(c));

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (a[i][j] == 'X') {
				dfs(i, j);
				cnt++; 
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			// cout << c[i][j] << ' ';
			if (c[i][j] != -1) {
				group[c[i][j]].push_back({i, j});
			}
		}
		// cout << '\n';
	}
	int res = 1e9;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (c[i][j] == -1) {
				int d = 0; 
				for (int gr = 0; gr < 3; ++gr) {
					int t = 1e9;

					for (auto v : group[gr]) t = min(t, dist(v.first, v.second, i, j) - 1);

					d += t; 
				}
				res = min(res, d + 1);
			}
		}
	}

	for (int gr = 0; gr < 3; ++gr) {
		min_group[gr] = inf;
		for (auto v : group[gr]) {
			for (auto v2 : group[(gr + 1) % 3]) {
				min_group[gr] = min(min_group[gr], dist(v.first, v.second, v2.first, v2.second) - 1);		
			}
		}
	}


	for (int gr = 0; gr < 3; ++gr) {
		res = min(res, min_group[gr] + min_group[(gr + 1) % 3]);
	}

	cout << res;

	
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