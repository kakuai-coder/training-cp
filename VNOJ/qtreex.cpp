/**
 * author: tinhnopro (tinh nop)
 * created: 2024-12-10
**/
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 0
#endif // LOCAL

#include <bits/stdc++.h>

using namespace std;

const int maxN = 1e4 + 5, inf = 1e9 + 11;

struct Node {
	int v, w;

	Node() : v(0), w(0) {}
	Node(int _v, int _w) : v(_v), w(_w) {}
};

struct edge_t {
	int u, v, w;

	edge_t() : u(0), v(0), w(0) {}
	edge_t(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};

struct node_t {
	int mx, mi, lazy;

	node_t() {
		lazy = 0;
		mx = 0;
		mi = 0;
	}

	node_t operator + (const node_t& other) {
		node_t ret;
		ret.mx = max(mx, other.mx);
		ret.mi = min(mi, other.mi);
		ret.lazy = 0;

		return ret;
	}

	void down() {
		swap(mx, mi);
		mx = -mx;
		mi = -mi;
		lazy ^= 1;
	}
};

struct SegmentTree {
	node_t st[4 * maxN];

	SegmentTree() {
		for (int i = 1; i < 4 * maxN; ++i) st[i] = node_t();
	}

	void down(int id) {
		if  (!st[id].lazy) return ;
		st[id << 1].down();
		st[id << 1 | 1].down();
		st[id].lazy = 0;
	}

	void update(int id, int l, int r, int u, int val) {
		if (l > u || u > r) return ;
		if (l == r) {
			st[id].mx = val;
			st[id].mi = val;
			st[id].lazy = 0;
			return ;
		}

		down(id);
		int mid = (l + r) >> 1;

		update(id << 1, l, mid, u, val);
		update(id << 1 | 1, mid + 1, r, u, val);

		st[id] = st[id << 1] + st[id << 1 | 1];
	}

	void update2(int id, int l, int r, int u, int v) {
		if (l > v || r < u) return ;
		if (u <= l && r <= v) {
			st[id].down();
			return ;
		}

		down(id);
		int mid = (l + r) >> 1;

		update2(id << 1, l, mid, u, v);
		update2(id << 1 | 1, mid + 1, r, u, v);

		st[id] = st[id << 1] + st[id << 1 | 1];
	}

	int query(int id, int l, int r, int u, int v) {
		if (l > v || r < u) return -inf;
		if (u <= l && r <= v) {
			return st[id].mx;
		}

		down(id);
		int mid = (l + r) >> 1;

		return max(query(id << 1, l, mid, u, v),
							query(id << 1 | 1, mid + 1, r, u, v));
	}
} seg;

int n;
vector<Node> adj[maxN];
vector<edge_t> edges;
int depth[maxN], par[maxN], sz[maxN];
int head[maxN], pos[maxN];

int curPos = 1;

void dfs(int u) {
	sz[u] = 1;
	for (Node x : adj[u]) if (x.v ^ par[u]) {
		par[x.v] = u;
		depth[x.v] = depth[u] + 1;

		dfs(x.v);

		sz[u] += sz[x.v];
	}
}

void hld(int u, int h) {
	pos[u] = curPos++;
	head[u] = h;

	int nxt = 0;
	for (Node x : adj[u]) if (x.v ^ par[u]) {
		if (nxt == 0 || sz[x.v] > sz[nxt]) nxt = x.v;
	}

	if (nxt) hld(nxt, h);

	for (Node x : adj[u]) if (x.v != par[u] && x.v != nxt) {
		hld(x.v, x.v);
	}
}

int getpath(int u, int v) {
	int res = -inf;

	for (; head[u] != head[v]; v = par[head[v]]) {
		if (depth[head[u]] > depth[head[v]]) swap(u, v);
		res = max(res, seg.query(1, 1, n, pos[head[v]], pos[v]));
	}

	if (depth[u] > depth[v]) swap(u, v);

	res = max(res, seg.query(1, 1, n, pos[u] + 1, pos[v]));

	return res;
}

void updpath(int u, int v) {
	for (; head[u] != head[v]; v = par[head[v]]) {
		if (depth[head[u]] > depth[head[v]]) swap(u, v);
		seg.update2(1, 1, n, pos[head[v]], pos[v]);
	}

	if (depth[u] > depth[v]) swap(u, v);
	seg.update2(1, 1, n, pos[u] + 1, pos[v]);
}

void reset() {
	curPos = 1;
	for (int i = 1; i <= n; ++i) {
		adj[i].clear();
		par[i] = depth[i] = head[i] = pos[i] = 0;
	}
	edges.clear();
	seg = SegmentTree();
}

void solve() {
	cin >> n;
	reset();
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
		edges.emplace_back(u, v, w);
	}

	par[1] = 1;
	dfs(1);
	hld(1, 1);

	for (int i = 0; i < n - 1; ++i) {
		int u = edges[i].u;
		int v = edges[i].v;
		int w = edges[i].w;

		if (depth[u] > depth[v]) swap(u, v);

		seg.update(1, 1, n, pos[v], w);
	}

	string op;

	while (cin >> op) {
		if (op == "DONE") break;
		int a, b;
		cin >> a >> b;

		if (op == "CHANGE") {
			a--;
			int u = edges[a].u;
			int v = edges[a].v;
			int w = edges[a].w;

			if (depth[u] > depth[v]) swap(u, v);
			edges[a].w = b;
			seg.update(1, 1, n, pos[v], b);

		} else if (op == "NEGATE") {
			updpath(a, b);
		} else {
			if (a == b) cout << 0 << '\n';
			else cout << getpath(a, b) << '\n';
		}
	}
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (fopen("qtreex.inp", "r")) {
		freopen("qtreex.inp", "r", stdin);
		freopen("qtreex.out", "w", stdout);
	}

	int t; cin >> t;
	while (t--) {
		solve();
	}
}
