/*
Author: kakuai
created: 2025.06.26 09:46:44
*/
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

template <typename T> bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T> bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
template <class T> int ssize(const T &a) { return (int)a.size(); }
#endif

const int N = 200000 + 5;
const int LOG = 18;

int n, q;
vector<int> adj[N];
int sz[N], depth[N], parent[N][LOG];
i64 sum[N], sum_in[N];

void dfs1(int u, int p) {
	sz[u] = 1;
	parent[u][0] = p;
	for (int i = 1; i < LOG; ++i)
			parent[u][i] = parent[parent[u][i-1]][i-1];
	sum_in[u] = 0;
	for (int v : adj[u]) {
			if (v == p) continue;
			depth[v] = depth[u] + 1;
			dfs1(v, u);
			sz[u] += sz[v];
			sum_in[u] += sum_in[v] + sz[v];
	}
}

void dfs2(int u, int p) {
	for (int v : adj[u]) {
			if (v == p) continue;
			sum[v] = sum[u] - 2LL * sz[v] + n;
			dfs2(v, u);
	}
}

int lca(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);
	int diff = depth[u] - depth[v];
	for (int i = 0; i < LOG; ++i)
			if (diff >> i & 1) u = parent[u][i];
	if (u == v) return u;
	for (int i = LOG-1; i >= 0; --i) {
			if (parent[u][i] != parent[v][i]) {
					u = parent[u][i];
					v = parent[v][i];
			}
	}
	return parent[u][0];
}

int jump(int u, int k) {
	for (int i = 0; i < LOG; ++i)
			if (k >> i & 1) u = parent[u][i];
	return u;
}

void kakuai() {
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
			adj[i].clear();
			sum[i] = 0;
	}
	for (int i = 1, u, v; i < n; ++i) {
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
	}
	depth[1] = 0;
	dfs1(1, 0);
	sum[1] = sum_in[1];
	dfs2(1, 0);
	
	while (q--) {
		int u, v;
		cin >> u >> v;
		if (depth[u] < depth[v]) swap(u, v);
		int w = lca(u, v);
		int dist = depth[u] + depth[v] - 2 * depth[w];
		int k = (dist - 1) / 2;
		int mid = jump(u, k);
		int p = parent[mid][0];
		int t1 = (dist + 1) / 2;
		int t2 = dist - (dist - 1) / 2;
		
		i64 cost_u = sum[u] - (sum[p] - (sum_in[mid] + sz[mid]) + (i64)(n - sz[mid]) * t1);
		i64 cost_v = sum[v] - (sum_in[mid] + (i64)sz[mid] * t2);
		cout << cost_u + cost_v << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	kakuai();
	cerr <<"\n[runtime] "<< (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}
