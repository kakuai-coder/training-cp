/*
Author: kakuai
created: 28.7.2025
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
vector<pair<int, int> > g[maxN];
pair<int, int> edges[maxN];

int comp[maxN], low[maxN], tin[maxN], cnt[maxN];
bool isBridge[maxN], vist[maxN];

int up[Log + 1][maxN], depth[maxN], h[maxN];
vector<int> gtree[maxN];
int timeDFS = 0, cntComp = 0;

void dfs_tarjan(int u, int par) {
	low[u] = tin[u] = ++timeDFS;

	for (auto &x : g[u]) if (x.first != par) {
		int v = x.first;
		int id = x.second;
		if (!tin[v]) {
			dfs_tarjan(v, u);

			minimize(low[u], low[v]);

			if (low[v] > tin[u]) {
				isBridge[id] = 1;
			}

		} else minimize(low[u], tin[v]);
	}
}

void dfs_comp(int u, int par) {
	vist[u] = 1;
	comp[u] = cntComp;

	for (auto &x : g[u]) {
		int v, id;
		tie(v, id) = x;

		if (vist[v] || isBridge[id]) continue;

		dfs_comp(v, u);
	}
}

void buildTree(void) {
	for (int i = 1; i <= n; ++i) if (!tin[i]) dfs_tarjan(i, i);

	for (int i = 1; i <= n; ++i) if (!vist[i]) {
		++cntComp;
		dfs_comp(i, i);
	}

	for (int i = 1; i <= m; ++i) if (isBridge[i]) {
		int u, v;
		tie(u, v) = edges[i];

		gtree[comp[u]].push_back(comp[v]);
		gtree[comp[v]].push_back(comp[u]);
	}
}


void dfs_tree(int u, int par) {
	up[0][u] = par;
	vist[u] = 1;

	for (int i = 1; i <= Log; ++i) up[i][u] = up[i - 1][up[i - 1][u]];

	h[u] = h[par] + cnt[u];

	for (int v : gtree[u]) if (v != par) {
		depth[v] = depth[u] + 1;
		dfs_tree(v, u);
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

	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;

		g[u].emplace_back(v, i);
		g[v].emplace_back(u, i);

		edges[i] = {u, v};
	}

	buildTree();

	for (int i = 1; i <= n; ++i) {
		for (auto &e : g[i]) {
			int v = e.first;

			if (comp[i] == comp[v]) {
				cnt[comp[i]]++;
			}
		}
	}

	for (int i = 1; i <= cntComp; ++i) cnt[i] = cnt[i] / 2;

	memset(vist, 0, sizeof(vist));

	for (int i = 1; i <= cntComp; ++i) if (!vist[i]) dfs_tree(i, i);

	int q;
	cin >> q;
	while (q--) {
		int u, v;
		cin >> u >> v;
		u = comp[u];
		v = comp[v];

		int l = lca(u, v);

		int d = depth[v] + depth[u] - 2 * depth[l];
		int d2 = h[u] + h[v] - 2 * h[l] + cnt[l];
		cout << d << ' ' << d + d2 << '\n';
	}

}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry ""
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
