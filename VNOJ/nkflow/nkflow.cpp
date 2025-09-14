/*
Author: kakuai
created: ..
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
int ssz(const T &a) {
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

const int MAXN = 1009, INF = 1e9 + 11;

int n, m, s, t;
int c[MAXN][MAXN], f[MAXN][MAXN], dist[MAXN], id[MAXN];
vector<int> g[MAXN];

void bfs() {
	for (int i = 1; i <= n; ++i) dist[i] = INF;
	queue<int> q;

	dist[s] = 0;
	q.push(s);

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int &v : g[u]) {
			if (dist[v] != INF) continue;
			if (f[u][v] == c[u][v]) continue;

			dist[v] = dist[u] + 1;

			q.push(v);
		}
	}
}

int dfs(int u, int cur) {
	if (cur == 0) return 0;
	if (u == t) return cur;

	for (; id[u] < ssz(g[u]); ++id[u]) {
		int v = g[u][id[u]];

		if (dist[v] != dist[u] + 1) continue;
		if (f[u][v] == c[u][v]) continue;

		int delta = dfs(v, min(c[u][v] - f[u][v], cur));

		if (delta == 0) continue;

		f[u][v] += delta;
		f[v][u] -= delta;

		return delta;
	}

	return 0;
}

void kakuai() {
	// voi26 = winner
	cin >> n >> m >> s >> t;

	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v >> c[u][v];
		g[u].push_back(v);
		g[v].push_back(u);
	}

	long long mxflow = 0;

	while (true) {
		bfs();

		if (dist[t] == INF) break;

		for (int i = 1; i <= n; ++i) id[i] = 0;

		while (int delta = dfs(s, INF)) {
			mxflow += delta;
		}
	}

	cout << mxflow;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "nkflow"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
