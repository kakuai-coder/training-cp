/*
	Author: kakuai
	created: 2025.07.09 12:20:55
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

const int maxN = 1005;
int n, m;
char a[maxN][maxN];
bool visited[maxN][maxN];

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

queue<pair<int, int>> q1, q2;
int cnt = 0;

void bfs() {
	while (!q1.empty()) {
		int x = q1.front().first;
		int y = q1.front().second;
		q1.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];

			if (nx < 1 || ny < 1 || nx > n || ny > m) continue;
			if (a[nx][ny] == '*') continue;
			if (visited[nx][ny]) continue;

			visited[nx][ny] = true;
			if (a[nx][ny] == a[x][y]) {
				q1.push({nx, ny});
			} else {
				q2.push({nx, ny});
			}
		}
	}
}

void kakuai() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}

	q1.push({1, 1});
	visited[1][1] = true;

	while (!q1.empty()) {
		cnt++;
		bfs();
		swap(q1, q2);
	}

	cout << cnt << '\n';
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}
