/*
Author: kakuai
created: 6.8.2025
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

int n, s;
vector<int> g[MaxN];
int cnt = 0, lim, dp[MaxN];

void dfs(int u, int par) {
	dp[u] = 0;
	for (int v : g[u]) if (v ^ par) {
		dfs(v, u);

		if (dp[u] + dp[v] + 1 > lim) {
			cnt++;
			minimize(dp[u], dp[v] + 1);
		} else maximize(dp[u], dp[v] + 1);
	}
}

bool check(int x) {
	cnt = 0;
	lim = x;

	dfs(1, 1);

	return cnt <= s;
}

void kakuai(void) {
	// voi26 = winner
	cin >> n >> s;
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	int l = 0, r = n + 1;

	while (r - l > 1) {
		int mid = (l + r) >> 1;

		if (check(mid)) r = mid;
		else l = mid;
	}

	cout << r;
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
