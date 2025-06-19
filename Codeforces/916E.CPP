/**
 * author: tinhnopro (tinh nop)
 * created: 2024-12-06
**/
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 0
#endif // LOCAL

#include <bits/stdc++.h>

using namespace std;

const int maxN = 1e5 + 5;
const int LOG = 17;

int n, q;
int64_t c[maxN];
vector<int> adj[maxN];
int depth[maxN], st[LOG + 1][maxN];

int timeIn[2 * maxN], timeOut[2 * maxN];

struct SegmentTree {
	int64_t st[8 * maxN], lazy[8 * maxN];

	SegmentTree() {
		memset(st, 0, sizeof(st));
	}

	void down(const int& id, const int& l, const int& r, const int& mid) {
		if (!lazy[id]) return ;

		lazy[id << 1] += lazy[id];
		lazy[id << 1 | 1] += lazy[id];

		st[id << 1] += 1LL * (mid - l + 1) * lazy[id];
		st[id << 1 | 1] += 1LL * (r - mid) * lazy[id];

		lazy[id] = 0;
	}

	void update(int id, int l, int r, int u, int v, int val) {
		if (l > v || r < u) return ;
		if (u <= l && r <= v) {
			st[id] += 1LL * (r - l + 1) * val;
			lazy[id] += val;
			return ;
		}

		int mid = (l + r) >> 1;
		down(id, l, r, mid);

		update(id << 1, l, mid, u, v, val);
		update(id << 1 | 1, mid + 1, r, u, v, val);

		st[id] = st[id << 1] + st[id << 1 | 1];
	}

	int64_t sum(int id, int l, int r, int u, int v) {
		if (l > v || r  < u) return 0;
		if (u <= l && r <= v) {
			return st[id];
		}

		int mid = (l + r) >> 1;
		down(id, l, r, mid);

		return sum(id << 1, l, mid, u, v) + sum(id << 1 | 1, mid + 1, r, u, v);
	}
};

void dfs(int u, int parent) {
	static int timeDFS = 0;
	timeIn[u] = ++timeDFS;

	st[0][u] = parent;
	for (int i = 1; i <= LOG; ++i) st[i][u] = st[i - 1][st[i - 1][u]];

	for (int v : adj[u]) if (v ^ parent) {
		depth[v] = depth[u] + 1;
		dfs(v, u);
	}

	timeOut[u] = timeDFS;
}

int lca(int u, int v) {
	if (u == v) return u;

	if (depth[u] < depth[v]) swap(u, v);

	int len = depth[u] - depth[v];

	for (int i = 0; (1 << i) <= len; ++i) if ((len >> i) & 1) {
		u = st[i][u];
	}

	if (u == v) return u;

	for (int i = LOG; ~i; --i) if (st[i][u] != st[i][v]) {
		u = st[i][u];
		v = st[i][v];
	}

	return st[0][u];
}

int dynamic_lca(int u, int v, int root) {
	return (lca(u, v) ^ lca(u, root) ^ lca(root, v));
}

SegmentTree seg;

bool isAncestor(int u, int v) {
	return timeIn[u] <= timeIn[v] && timeOut[v] <= timeOut[u];
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (fopen("916E.inp", "r")) {
		freopen("916E.inp", "r", stdin);
		freopen("916E.out", "w", stdout);
	}

	cin >> n >> q;

	for (int i = 1; i <= n; ++i) cin >> c[i];

	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	int root = 1;
	st[0][1] = 1;
	dfs(root, 1);

	for (int i = 1; i <= n; ++i) seg.update(1, 1, 2 * n, timeIn[i], timeIn[i], c[i]);

	while (q--) {
		int type; cin >> type;

		if (type == 1) {
			int u; cin >> u;
			root = u;
		} else if (type == 2) {
			int u, v, x; cin >> u >> v >> x;

			int l = dynamic_lca(u, v, root);

			if (l == root) {
				seg.update(1, 1, 2 * n, timeIn[1], timeOut[1], x);
				continue;
			} else if (isAncestor(l, root)) {
				int len = depth[root] - depth[l] - 1;
				int d = root;
				for (int i = 0; (1 << i) <= len; ++i) if ((len >> i) & 1) {
					d = st[i][d];
				}
				seg.update(1, 1, 2 * n, timeIn[1], timeOut[1], x);
				seg.update(1, 1, 2 * n, timeIn[d], timeOut[d], -x);

			} else {
				seg.update(1, 1, 2 * n, timeIn[l], timeOut[l], x);
			}
		} else {
			int u; cin >> u;

			if (u == root) {
				cout << seg.sum(1, 1, 2 * n, timeIn[1], timeOut[1]) << '\n';
			} else if (isAncestor(u, root)) {
				int len = depth[root] - depth[u] - 1;
				int d = root;
				for (int i = 0; (1 << i) <= len; ++i) if ((len >> i) & 1) {
					d = st[i][d];
				}
				cout << seg.sum(1, 1, 2 * n, timeIn[1], timeOut[1]) -
								seg.sum(1, 1, 2 * n, timeIn[d], timeOut[d]) << '\n';
			} else {
				cout << seg.sum(1, 1, 2 * n, timeIn[u], timeOut[u]) << '\n';
			}
		}
	}
}

