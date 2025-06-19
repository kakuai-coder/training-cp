/*
	Author: tinhnopro
	created: 2025.04.15 15:43:28
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

const int maxN = 1011;
const int maxV = 1e6 + 5; 

int m, n, h[maxN][maxN], lastH[maxN][maxN];
vector<pair<int, int > > pos[maxV]; 

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0}; 

void bfs(int x, int y, int val) {
	queue<pair<int, int> > q; 
	lastH[x][y] = val; 
	q.emplace(x, y); 

	while (!q.empty()) {
		int X, Y; 
		tie(X, Y) = q.front(); 
		q.pop(); 

		for (int i = 0; i < 4; ++i) {
			int nx = X + dx[i]; 
			int ny = Y + dy[i];

			if (!lastH[nx][ny] && h[nx][ny] <= val) {
				lastH[nx][ny] = val; 
				q.emplace(nx, ny); 
			}
		}
	}
}

bool isBroder(int x, int y) {
	for (int i = 0; i < 4; ++i) {
		if (lastH[x + dx[i]][y + dy[i]]) return true;
	}
	return false; 
}

void tinhnop() {
	cin >> m >> n; 

	int mxH = 0; 

	memset(lastH, -1, sizeof(lastH));

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> h[i][j]; 
			pos[h[i][j]].push_back({i, j});
			maximize(mxH, h[i][j]);
			lastH[i][j] = 0;
		}
	}

	for (int i = 1; i <= mxH; ++i) {
		for (auto d : pos[i]) {
			int x, y;
			tie(x, y) = d; 
			if (!lastH[x][y] && isBroder(x, y)) {
				bfs(x, y, h[x][y]); 
			}
		}
	}

	i64 ans = 0; 

	for (int i = 2; i < m; ++i) {
		for (int j = 2; j < n; ++j) {
			ans += max(0, lastH[i][j] - h[i][j]); 
		}
	}

	cout << ans; 
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "a6"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	tinhnop();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}