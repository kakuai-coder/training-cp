/*
	Author: kakuai
	created: 2025.06.24 09:49:53
*/
#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5 + 5;
int n, m, q;
vector<int> adj[maxN];
int depth[maxN], tin[maxN], tout[maxN], timer;
int diffArr[maxN], sumToRoot[maxN];

vector<int> euler;
int first[maxN], height[maxN];
int log2Val[2 * maxN], st[20][2 * maxN];

void dfs(int u, int p) {
	tin[u] = ++timer;
	first[u] = euler.size();
	height[u] = depth[u];
	euler.push_back(u);

	for (int v : adj[u]) {
		if (v == p) continue;
		depth[v] = depth[u] + 1;
		dfs(v, u);
		euler.push_back(u);
	}

	tout[u] = timer;
}

void build_lca() {
	int N = euler.size();
	for (int i = 0; i < N; ++i)
		st[0][i] = euler[i];

	for (int k = 1; (1 << k) <= N; ++k) {
		for (int i = 0; i + (1 << k) <= N; ++i) {
			int u = st[k - 1][i];
			int v = st[k - 1][i + (1 << (k - 1))];
			st[k][i] = (height[u] < height[v]) ? u : v;
		}
	}

	log2Val[1] = 0;
	for (int i = 2; i < 2 * maxN; ++i)
		log2Val[i] = log2Val[i >> 1] + 1;
}

int lca(int u, int v) {
	int L = first[u], R = first[v];
	if (L > R) swap(L, R);
	int k = log2Val[R - L + 1];
	int a = st[k][L];
	int b = st[k][R - (1 << k) + 1];
	return (height[a] < height[b]) ? a : b;
}

bool isAnc(int u, int v) {
	return tin[u] <= tin[v] && tout[v] <= tout[u];
}

bool get_intersection(int a, int b, int c, int d, int &P, int &Q) {
	int l1 = lca(a,b), l2 = lca(c,d);
	int pts[4] = { lca(a,c), lca(a,d), lca(b,c), lca(b,d) };
	int valid = 0;
	for (int i = 0; i < 4; ++i) {
		int u = pts[i];
		if (isAnc(l1,u) && (isAnc(u,a)||isAnc(u,b))
		 && isAnc(l2,u) && (isAnc(u,c)||isAnc(u,d)))
			valid |= 1<<i;
	}
	if (__builtin_popcount(valid) < 2) return false;
	int best = -1;
	for (int m = valid; m; m = (m-1)&valid) {
		if (__builtin_popcount(m) != 2) continue;
		int i = __builtin_ctz(m), j = __builtin_ctz(m^(1<<i));
		int u = pts[i], v = pts[j];
		int w = lca(u,v);
		int d_uv = depth[u] + depth[v] - 2*depth[w];
		if (d_uv > best) {
			best = d_uv;
			P = u; Q = v;
		}
	}
	return true;
}

void dfs_propagate(int u, int p) {
	for (int v : adj[u]) if (v != p) {
		dfs_propagate(v, u);
		diffArr[u] += diffArr[v];
	}
}

void dfs_sum(int u, int p) {
	for (int v : adj[u]) if (v != p) {
		sumToRoot[v] = sumToRoot[u] + diffArr[v];
		dfs_sum(v, u);
	}
}

void kakuai() {
	cin >> n >> m >> q;
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	depth[1] = 0;
	dfs(1, 0);
	build_lca();

	int a, b, c, d, p, q2;
	while (m--) {
		cin >> a >> b >> c >> d;
		diffArr[a] += 1;
		diffArr[b] += 1;
		diffArr[lca(a, b)] -= 2;
		if (get_intersection(a, b, c, d, p, q2)) {
			diffArr[p] -= 1;
			diffArr[q2] -= 1;
			diffArr[lca(p, q2)] += 2;
		}
	}
	dfs_propagate(1, 0);
	sumToRoot[1] = diffArr[1];
	dfs_sum(1, 0);

	while (q--) {
		int e, f;
		cin >> e >> f;
		int L = lca(e, f);
		cout << sumToRoot[e] + sumToRoot[f] - 2 * sumToRoot[L] << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	kakuai();
	return 0;
}
