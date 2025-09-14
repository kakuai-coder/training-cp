// kakuai ^><^ || cherry  
#include <bits/stdc++.h>
#define task ""
using namespace std;

const int MAXN = 1e5 + 5;

struct edge_t {
	int u, v;
	bool used;

	edge_t() {
		u = v = used = 0;
	}

	edge_t(int _u, int _v) : u(_u), v(_v), used(0) {}

	int other(const int& x) {
		return x ^ u ^ v;
	}
};

int n, m; 
vector<int> g[MAXN];
edge_t edges[MAXN];
int num[MAXN], low[MAXN], comp[MAXN], rep[MAXN], timer = 0, compid = 0;
bool isBridge[MAXN], isCut[MAXN];
vector<int> bg[MAXN];

void minim(int &x, const int &y) {
	if (x > y) x = y;
}

void dfs_pre(int u, int p = 0) {
	num[u] = low[u] = ++timer; 

	int child = 0; 

	for (int &i : g[u]) {
		if (edges[i].used) continue;

		edges[i].used = true;

		int v = edges[i].other(u);

		if (!num[v]) {
			dfs_pre(v, u);
			minim(low[u], low[v]);

			if (low[v] == num[v]) isBridge[i] = 1; 

			++child;

			if (p == 0) {
				if (child > 1) isCut[u] = 1; 
			} else if (low[v] >= num[u]) isCut[u] = 1; 

		} else minim(low[u], num[v]);
	}
}

void dfs_mark(int u) {
	comp[u] = compid;
	if (!rep[compid]) rep[compid] = u;

	for (int &i : g[u]) {
		int v = edges[i].other(u);

		if (isBridge[i] || comp[v]) continue;

		dfs_mark(v);
	}
}

void solve(void) { 
	cin >> n >> m;
	for (int i = 1, u, v; i <= m; ++i) {
		cin >> u >> v; 
		g[u].push_back(i); 
		g[v].push_back(i);
		edges[i] = edge_t(u, v);
	}	

	for (int i = 1; i <= n; ++i) if (!num[i]) dfs_pre(i);

	for (int i = 1; i <= n; ++i) if (!comp[i]) {
		++compid; 
		dfs_mark(i);
	}

	int totBridge = 0, totCut = 0;

	for (int i = 1; i <= n; ++i) totCut += isCut[i];

	for (int i = 1; i <= m; ++i) if (isBridge[i]) {
		totBridge++;
		int u = comp[edges[i].u];
		int v = comp[edges[i].v];

		if (u == v) continue;

		bg[u].push_back(v); 
		bg[v].push_back(u);
	}

	cout << totCut << ' ' << totBridge;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	if (fopen(task ".inp", "r")) {
		freopen(task ".inp", "r", stdin);
		freopen(task ".out", "w", stdout);
	}

	int t = 1; // cin >> t;
	while (t--) {
		solve(); // cout << '\n';
	}
}