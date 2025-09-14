// kakuai ^><^ || cherry  
#include <bits/stdc++.h>
#define task "b"

#define id(i, j) (((i) - 1) * m + (j) - 1)

using namespace std;

const int MAX = 2009, INF = 1e9 + 11;

int n, m; 
vector<vector<char> > a; 
int dist[MAX][MAX][2];
vector<pair<int, int> > move_p = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
vector<pair<int, int> > move_k = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};


void solve(void) { 
	cin >> n >> m; 
	
	a.resize(n + 2, vector<char>(m + 2));

	vector<pair<int, char> > pieces;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j];

			if (a[i][j] == 'T') {
				pieces.push_back({id(i, j), a[i][j]});
			} else if (a[i][j] == 'M') {
				pieces.push_back({id(i, j), a[i][j]});
			}
		}
	}

	int P = (int)pieces.size();

	for (int i = 0; i < P; ++i) {
		int s = pieces[i].first;
		char t = pieces[i].second; 
		
		queue<pair<int, int> > dq; 

		for (int j = 0; j < m * n; ++j) dist[i][j][0] = dist[i][j][1] = INF; 

		dist[i][s][0] = 0;
		dq.push({s, 0});

		const vector<pair<int, int> > &mov = (t == 'M' ? move_k : move_p); 

		while (!dq.empty()) {
			int u = dq.front().first; 
			int p = dq.front().second;
			dq.pop();

			int x = u / m + 1;
			int y = u % m + 1;


			for (auto &mv : mov) {
				int nx = x + mv.first;
				int ny = y + mv.second; 

				if (1 > nx || nx > n || 1 > ny || ny > m) continue;

				if (a[nx][ny] == '#') continue;

				int np = p ^ 1;
				int nid = id(nx, ny);

				if (dist[i][nid][np] > dist[i][u][p] + 1) {
					dist[i][nid][np] = dist[i][u][p] + 1; 

					dq.push({nid, np});
				}
			}
		}

		// for (int j = 0; j < n * m; ++j) cout << dist[i][j][0] << ' ' << dist[i][j][1] << '\n';
		// cout << '\n';
	}

	int ans = INF;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) if (a[i][j] != '#') {
			int node = id(i, j);
			int dist0 = 0, dist1 = 0;

			int cnt0 = 0, cnt1 = 0;

			for (int _ = 0; _ < P; ++_) {
				dist0 = max(dist0, dist[_][node][0]);
				dist1 = max(dist1, dist[_][node][1]);

				cnt0 += (dist[_][node][0] == 0);
				cnt1 += (dist[_][node][1] == 0);
			}

			if (dist0 < INF && (!cnt0 || cnt0 == P)) ans = min(ans, dist0);
			if (dist1 < INF && (!cnt1 || cnt1 == P)) ans = min(ans, dist1);
		}
	}

	cout << (ans == INF ? -1 : ans);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	if (fopen(task ".inp", "r")) {
		freopen(task ".inp", "r", stdin);
		freopen(task ".out", "w", stdout);
	}

	int t = 1; // cin >> t;
	while (t--) {
		solve(); // cout << '\n';
	}
}