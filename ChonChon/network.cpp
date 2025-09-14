// kakuai ^><^ || cherry  
#include <bits/stdc++.h>
#define task "network"

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
bool isBridge[MAXN], used[MAXN];
vector<int> bg[MAXN];
int depth[MAXN]; 

void dfs_pre(int u) {
	num[u] = low[u] = ++timer; 

	for (int &i : g[u]) {
		if (edges[i].used) continue;

		edges[i].used = true;

		int v = edges[i].other(u);

		if (!num[v]) {
			dfs_pre(v);
			low[u] = min(low[u], low[v]);

			if (low[v] > num[u]) isBridge[i] = 1; 

		} else low[u] = min(low[u], num[v]);
	}
}

void dfs_mark(int u) {
	comp[u] = compid;
	used[u] = 1; 
	if (!rep[compid]) rep[compid] = u;

	for (int &i : g[u]) {
		int v = edges[i].other(u);

		if (isBridge[i] || used[v]) continue;

		dfs_mark(v);
	}
}

pair<int, int> bfs(int root) {
	for (int i = 1; i <= compid; ++i) depth[i] = -1; 

	queue<int> q; 

	q.push(root); 

	depth[root] = 0;

	while (!q.empty()) {
		int u = q.front(); 
		q.pop(); 

		for (int &v : bg[u]) if (depth[v] == -1) {
			depth[v] = depth[u] + 1; 
			q.push(v);
		} 
	}

	int far = root; 

	for (int i = 1; i <= compid; ++i) if (depth[i] > depth[far]) far = i;

	return {far, depth[far]};
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

	for (int i = 1; i <= n; ++i) if (!used[i]) {
		++compid; 
		dfs_mark(i);
	}

	int totBridge = 0;

	for (int i = 1; i <= m; ++i) if (isBridge[i]) {
		totBridge++;
		int u = comp[edges[i].u];
		int v = comp[edges[i].v];

		if (u == v) continue;

		bg[u].push_back(v); 
		bg[v].push_back(u);
	}

	if (totBridge == 0) {
		cout << 1 << ' ' << 2;
		return ;
	}

	auto a = bfs(1);
	auto b = bfs(a.first);

	int repa = rep[a.first];
	int repb = rep[b.first];

	if (repa == 0 || repb == 0) {
		cout << 1 << ' ' << 2;
	} else {
		cout << repa << ' ' << repb;
	}
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