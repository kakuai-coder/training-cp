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

const int maxN = 2e5 + 5, inf = 1e9 + 11;

int n, q;
int a[maxN];
vector<int> g[maxN];

int heavy[maxN], pos[maxN], head[maxN];
int depth[maxN], sz[maxN], par[maxN];
int cur_pos = 1;

struct SegmentTree {
	int tree[4 * maxN];

	SegmentTree() {
		memset(tree, 0, sizeof(tree));
	}

	void update(int id, int l, int r, int pos, int val) {
		if (l > pos || pos > r) return ;

		if (l == r) {
			tree[id] = val;
			return ;
		}

		int mid = (l + r) >> 1;

		update(id << 1, l, mid, pos, val);
		update(id << 1 | 1, mid + 1, r, pos, val);

		tree[id] = max(tree[id << 1], tree[id << 1 | 1]);
	}

	int query(int id, int l, int r, int u, int v) {
		if (l > v || r < u) return -inf;
		if (u <= l && r <= v) return tree[id];

		int mid = (l + r) >> 1;

		return max(query(id << 1, l, mid, u, v), query(id << 1 | 1, mid + 1, r, u, v));
	}

} seg;

void dfs(int u) {
	sz[u] = 1;

	int max_sz = 0;

	for (int v : g[u]) if (v ^ par[u]) {
		par[v] = u;
		depth[v] = depth[u] + 1;
		dfs(v);
		sz[u] += sz[v];
		if (maximize(max_sz, sz[v])) {
			heavy[u] = v;
		}
	}
}

void decomp(int u, int h) {
	head[u] = h;
	pos[u] = cur_pos++;

	if (heavy[u]) {
		decomp(heavy[u], h);
	}

	for (int v : g[u]) if (v != par[u] && v != heavy[u]) {
		decomp(v, v);
	}
}

int query(int u, int v) {

	int res = -inf;
	for (; head[u] != head[v]; v = par[head[v]]) {
		if (depth[head[u]] > depth[head[v]]) swap(u, v);
		maximize(res, seg.query(1, 1, n, pos[head[v]], pos[v]));
	}

	if (depth[u] > depth[v]) swap(u, v);

	maximize(res, seg.query(1, 1, n, pos[u], pos[v]));

	return res;
}


void kakuai(void) {
	// voi26 = winner
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) cin >> a[i];

	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	par[1] = 1;

	dfs(1);
	decomp(1, 1);

	for (int i = 1; i <= n; ++i) seg.update(1, 1, n, pos[i], a[i]);

	while (q--) {
		int op;
		cin >> op;
		if (op == 1) {
			int u, val;
			cin >> u >> val;
			seg.update(1, 1, n, pos[u], val);
		} else {
			int u, v;
			cin >> u >> v;
			cout << query(u, v) << ' ';
		}
	}

}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "euler_h"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
