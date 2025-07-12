/*
	Author: kakuai
	created: 2025.07.04 10:30:00
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T> bool maximize(T &a, const T &b) { return a < b ? (a = b, true) : false; }
template <typename T> bool minimize(T &a, const T &b) { return a > b ? (a = b, true) : false; }

#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif

const int maxN = 1010;

int n, m, C;
int a[maxN];
vector<int> adj[maxN];
i64 dp[maxN][maxN], inqueue[maxN][maxN]; 

void kakuai() {
	cin >> n >> m >> C;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
	}

	memset(dp, -0x3f, sizeof(dp));

	queue<pair<int, int>> q;
	dp[1][0] = 0;
	q.emplace(1, 0);

	i64 ans = 0;

	while (!q.empty()) {
		pair<int, int> x = q.front(); q.pop();

		int u = x.first; 
		int t = x.second;

		inqueue[u][t] = 1;

		for (int v : adj[u]) {
			i64 new_profit = dp[u][t] + a[v];
			if (!inqueue[v][t + 1] && new_profit > dp[v][t + 1]) {
				dp[v][t + 1] = new_profit;
				q.emplace(v, t + 1);

				if (v == 1) {
					i64 net = new_profit - 1LL * C * (t + 1) * (t + 1);
					maximize(ans, net);
				}
			}
		}
	}

	cout << ans << '\n';
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "b"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	kakuai();

	cerr << "\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}
