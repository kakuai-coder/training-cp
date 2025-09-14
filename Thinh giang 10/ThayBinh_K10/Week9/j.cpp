/*
Author: kakuai
created: 10.8.2025
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

const int MAXN = 1e5 + 5;


int n, k;
vector<int> g[MAXN];
int c[MAXN];
int64_t dp[25][MAXN];


void kakuai() {
	// voi26 = winner
	cin >> n >> k;

	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	for (int i = 1; i <= n; ++i) cin >> c[i];

	for (int i = 1; i <= n; ++i) {
		dp[0][i] = c[i];
	}

	for (int i = 1; i <= n; ++i) {
		dp[1][i] += dp[0][i];
		for (int j : g[i]) dp[1][i] += dp[0][j];
	}

	for (int j = 2; j <= k; ++j) {
		for (int u = 1; u <= n; ++u) {
			dp[j][u] = -1LL * (ssz(g[u]) - 1) * dp[j - 2][u];

			for (int v : g[u]) dp[j][u] += dp[j - 1][v];
		}
	}

	for (int i = 1; i <= n; ++i) cout << dp[k][i] << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "j"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
