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

const int MaxN = 1e5 + 5;

int n;
vector<int> g[MaxN];
int depth[MaxN], up[MaxN];
int max_depth = -1, far = -1;

void dfs(int u, int par) {

	if (maximize(max_depth, depth[u])) far = u;

	for (int v : g[u]) if (v ^ par) {
		up[v] = u;
		depth[v] = depth[u] + 1;
		dfs(v, u);
	}
}

void kakuai(void) {
	// voi26 = winner
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	vector<int> path;

	dfs(1, 1);


	max_depth = -1;
	int x = far;
	memset(depth, 0, sizeof(depth));

	dfs(far, far);

	int y = far;

	while (y != x) {
		path.push_back(y);
		y = up[y];
	}

	path.push_back(x);

	reverse(path.begin(), path.end());

	int sz = size32(path);

	set<int> ans;

	if (sz & 1) {
		ans.insert(path[sz / 2]);
	} else {
		ans.insert(path[sz / 2]);
		ans.insert(path[sz / 2 - 1]);
	}

	cout << size32(ans) << '\n';

	for (int x : ans) cout << x << ' ';

}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "e"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
