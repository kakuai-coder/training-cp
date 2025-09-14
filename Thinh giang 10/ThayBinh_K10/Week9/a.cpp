/*
Author: kakuai
created: 5.8.2025
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

const int MaxN = 1e5 + 5, Log = 17;

int n, m;
vector<pair<int, int> > g[MaxN];
int depth[MaxN], up[Log + 1][MaxN];
int64_t h[MaxN];

void dfs(int u, int par) {

	up[0][u] = par;

	for (int i = 1; i <= Log; ++i) up[i][u] = up[i - 1][up[i - 1][u]];

	for (auto &x : g[u]) {
		int v = x.first;
		int w = x.second;
		if (v == par) continue;

		depth[v] = depth[u] + 1;
		h[v] = h[u] + w;

		dfs(v, u);
	}
}

int lca(int u, int v) {
	if (u == v) return u;

	if (depth[u] < depth[v]) swap(u, v);

	int diff = depth[u] - depth[v];

	for (int i = 0; i <= Log; ++i) if ((diff >> i) & 1) {
		u = up[i][u];
	}

	if (u == v) return u;

	for (int i = Log; ~i; --i) if (up[i][u] != up[i][v]) {
		u = up[i][u];
		v = up[i][v];
	}

	return up[0][u];
}

void kakuai(void) {
	// voi26 = winner
	cin >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}

	dfs(1, 1);

	while (m--) {
		int u, v;
		cin >> u >> v;

		int l = lca(u, v);

		cout << h[u] + h[v] - 2 * h[l] << '\n';
	}
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "a"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
