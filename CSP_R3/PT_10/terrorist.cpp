/*
Author: kakuai
created: 2025.07.19
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

const int maxN = 2e5 + 5; 
const int Log = 20;

int n, m; 
vector<int> adj[maxN];

namespace tree {
	int depth[maxN], up[Log + 1][maxN];

	void dfs(int u, int par) {
		up[0][u] = par; 
		for (int i = 1; i <= Log; ++i) up[i][u] = up[i - 1][up[i - 1][u]];

		for (int v : adj[u]) if (v != par) {
			depth[v] = depth[u] + 1; 
			dfs(v, u); 
		}
	}

	int lca(int u, int v) {
		if (u == v) return u; 
		if (depth[u] < depth[v]) swap(u, v); 
		int k = depth[u] - depth[v]; 

		for (int i = 0; i <= Log; ++i) if ((k >> i) & 1) {
			u = up[i][u];
		}

		if (u == v) return u; 

		for (int i = Log; ~i; --i) if (up[i][u] != up[i][v]) {
			u = up[i][u]; 
			v = up[i][v];
		}

		return up[0][u];
	}
	
	void solve(void) {
		dfs(1, 1);
		int q; 
		cin >> q; 
		while (q--) {
			int u, v; 
			cin >> u >> v; 
			// cout << depth[u] << ' ' << depth[v] << ' ';
			int x = depth[u] + depth[v] - 2 * depth[lca(u, v)];

			cout << x << ' ' << x << '\n';
		}
	}
};

void kakuai(void) {
	// voi26 = winner
	cin >> n >> m; 
	for (int i = 1; i <= m; ++i) {
		int u, v; 
		cin >> u >> v; 
		adj[u].push_back(v); 
		adj[v].push_back(u);
	}

	if (m == n - 1) {
		tree::solve();
		return ;
	}
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "terrorist"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}