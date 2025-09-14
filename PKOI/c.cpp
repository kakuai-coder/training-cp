/*
Author: kakuai
created: 3.8.2025
*/
#include <bits/stdc++.h>

using namespace std;

namespace std {

template <typename T>
using pqmin = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
bool maximize(T &a, const T &b) {
	return a < b ? a = b, true : false;
}
template <typename T>
bool minimize(T &a, const T &b) {
	return a > b ? a = b, true : false;
}

template <typename T>
int size32(const T &a) {
	return (int)a.size();
}

template <typename T, int D>
struct Vec : public vector<Vec<T, D - 1>> {
	static_assert(D >= 1, "Error");
	template <typename... Args>
	Vec(int n = 0, Args... args)
		: vector<Vec<T, D - 1>>(n, Vec<T, D - 1>(args...)) {}
};
template <typename T>
struct Vec<T, 1> : public vector<T> {
	Vec(int n = 0, const T &val = T()) : vector<T>(n, val) {}
};
}  // namespace std

int n;

void kakuai(void) {
	// voi26 = winner
	cin >> n;

	Vec<int, 2> a(n + 2, n + 2, 0);
	vector<pair<int, int> > pos;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			string s;
			cin >> s;

			if (s == "*") {
				pos.push_back({i, j});
				a[i][j] = 0;
			} else {
				a[i][j] = stoi(s);
			}
		}
	}

	int M = size32(pos);
	const int64_t inf = (int64_t) 1e18 + 11;

	vector<int64_t> dp(1 << M + 1, inf), sum(1 << M + 1, 0), cost(1 << M + 1, inf);
	Vec<int64_t, 3> dist(M + 1, n + 1, n + 1, 0);
	int dx[] = {0, 0, 1, -1};
	int dy[] = {1, -1, 0, 0};

	for (int s = 0; s < M; ++s) {
		int x = pos[s].first;
		int y = pos[s].second;

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) dist[s][i][j] = inf;
		}

		dist[s][x][y] = 0;

		pqmin<array<int64_t, 3> > pq;
		pq.push({dist[s][x][y], x, y});

		while (!pq.empty()) {
			array<int64_t, 3> top = pq.top();
			pq.pop();

			int64_t d_u = top[0];
			int u = top[1];
			int v = top[2];

			if (d_u > dist[s][u][v]) continue;

			for (int k = 0; k < 4; ++k) {
				int nu = u + dx[k];
				int nv = v + dy[k];

				if (nu < 1 || nu > n || nv < 1 || nv > n) continue;

				if (dist[s][nu][nv] > dist[s][u][v] + a[nu][nv]) {
					dist[s][nu][nv] = dist[s][u][v] + a[nu][nv];
					pq.push({dist[s][nu][nv], nu, nv});
				}
			}
		}
	}

	dp[0] = 0;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) if (a[i][j] > 0) {
			sum[0] = 0;
			for (int mask = 1; mask < (1 << M); ++mask) {
				int b = __builtin_ctz(mask);
				sum[mask] = sum[mask ^ (1 << b)] + dist[b][i][j];
				minimize(cost[mask], sum[mask]);
			}
		}
	}

	for (int mask = 1; mask < (1 << M); ++mask) {
		if (__builtin_popcount(mask) == 1) {
			dp[mask] = 0;
			continue;
		}

		for(int i = mask; i; i = (i - 1) & mask){
			minimize(dp[mask], dp[i] + dp[i ^ mask] + cost[mask]);
		}
	}

	cout << dp[(1 << M) - 1];
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "c"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
