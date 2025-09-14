/*
Author: kakuai
created: 9.8.2025
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

const int MaxN = 5e4 + 5;

int n;
vector<pair<int, int> > g[MaxN];
int depth[MaxN], max_depth = -1, far = -1;

void dfs(int u, int par) {

	if (maximize(max_depth, depth[u])) far = u;

	for (auto &x : g[u]) {
		int v = x.first;
		int w = x.second;

		if (v == par) continue;

		depth[v] = depth[u] + w;

		dfs(v, u);
	}
}

void kakuai(void) {
	// voi26 = winner
	cin >> n;

	for (int i = 1; i < n; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}

	dfs(1, 1);

	memset(depth, 0, sizeof(depth));
	max_depth = -1;

	dfs(far, far);

	cout << depth[far] << '\n';

}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "f"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
