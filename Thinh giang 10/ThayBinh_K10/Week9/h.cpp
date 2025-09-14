/*
	Author: kakuai (sửa theo yêu cầu)
	created: 2025.08.01
*/
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
const int NMAX = 300000 + 5;

int n;
vector<int> adj[NMAX];

// dfs1 results
int downv[NMAX];        // longest downward arm (edges) from u
int diam_sub[NMAX];     // diameter inside subtree u

// dfs2 / reroot results
int upDepth[NMAX];      // longest distance from u to a node outside subtree u
int diam_out[NMAX];     // best diameter entirely outside subtree u

// dfs1: compute downv and diam_sub
void dfs1(int u, int p) {
	downv[u] = 0;
	int best_child_diam = 0;

	// keep top3 down among children
	int d1 = -1, id1 = -1;
	int d2 = -1, id2 = -1;
	int d3 = -1, id3 = -1;

	for (int v : adj[u]) if (v != p) {
		dfs1(v, u);
		// update best child diam
		if (diam_sub[v] > best_child_diam) best_child_diam = diam_sub[v];

		int dv = downv[v];
		// insert dv into top3
		if (dv > d1) { d3 = d2; id3 = id2; d2 = d1; id2 = id1; d1 = dv; id1 = v; }
		else if (dv > d2) { d3 = d2; id3 = id2; d2 = dv; id2 = v; }
		else if (dv > d3) { d3 = dv; id3 = v; }
	}

	// compute downv[u] (max arm)
	if (d1 >= 0) downv[u] = d1 + 1;
	else downv[u] = 0;

	// compute diam_sub[u]
	int best = best_child_diam; // some child's internal diam
	// single arm (path starting at u going down)
	best = max(best, downv[u]);
	// path through u connecting two child branches
	if (d1 >= 0 && d2 >= 0) {
		// two child arms: (d1+1) + (d2+1) = d1 + d2 + 2
		best = max(best, d1 + d2 + 2);
	}
	diam_sub[u] = best;
}

// dfs2: compute upDepth and diam_out (reroot)
void dfs2(int u, int p) {
	// prepare top3 down among children and top2 diam_sub among children
	int d1 = -1, id1 = -1;
	int d2 = -1, id2 = -1;
	int d3 = -1, id3 = -1;
	int diam1 = -1, idd1 = -1;
	int diam2 = -1, idd2 = -1;

	for (int v : adj[u]) if (v != p) {
		int dv = downv[v];
		if (dv > d1) { d3 = d2; id3 = id2; d2 = d1; id2 = id1; d1 = dv; id1 = v; }
		else if (dv > d2) { d3 = d2; id3 = id2; d2 = dv; id2 = v; }
		else if (dv > d3) { d3 = dv; id3 = v; }

		int db = diam_sub[v];
		if (db > diam1) { diam2 = diam1; idd2 = idd1; diam1 = db; idd1 = v; }
		else if (db > diam2) { diam2 = db; idd2 = v; }
	}

	// also consider diam_out[u] as candidate for children (already set)
	for (int v : adj[u]) if (v != p) {
		// compute upDepth[v]
		// candidate1: go up from u further
		int cand1 = upDepth[u] + 1;
		// candidate2: go to best sibling subtree: best sibling down + 2
		int best_sib_down = -1;
		if (id1 != -1) {
			if (v != id1) best_sib_down = d1;
			else best_sib_down = d2;
		}
		int cand2 = (best_sib_down >= 0) ? (best_sib_down + 2) : -1000000000;
		upDepth[v] = max(cand1, cand2);
		if (upDepth[v] < 0) upDepth[v] = 0; // ensure non-negative

		// compute diam_out[v]: best diameter entirely outside subtree v
		int best_out = 0;
		// option A: diam_out[u] (some diameter outside u's subtree)
		best_out = max(best_out, diam_out[u]);
		// option B: some sibling subtree diam
		int best_sib_diam = 0;
		if (idd1 != -1) {
			if (v != idd1) best_sib_diam = diam1;
			else best_sib_diam = diam2;
		}
		best_out = max(best_out, best_sib_diam);

		// option C: a path through u built from two arms that are not in v's subtree
		// arms available: arm_up = upDepth[u], and arms from siblings: down[sib]+1
	 // need top two arms among {upDepth[u], all siblings' (down+1)}
		int arm_up = upDepth[u];
		// get top2 sibling downs excluding v
		int sd1 = -1, sd2 = -1;
		// sdX are raw down[v] values (not +1)
	 if (d1 != -1) {
		 if (v != id1) sd1 = d1, sd2 = d2;
		 else sd1 = d2, sd2 = d3;
	 }
	 // convert to arm lengths (edges from u): sibling arm = sd + 1
	 int arm1 = -1, arm2 = -1;
	 if (arm_up >= 0) arm1 = arm_up;
	 // collect candidate arms: arm_up and sd1+1 and sd2+1
	 vector<int> arms;
	 if (arm_up >= 0) arms.push_back(arm_up);
	 if (sd1 >= 0) arms.push_back(sd1 + 1);
	 if (sd2 >= 0) arms.push_back(sd2 + 1);
	 // find top2 in arms
	 sort(arms.begin(), arms.end(), greater<int>());
	 if (!arms.empty()) best_out = max(best_out, arms[0]); // single arm path
	 if ((int)arms.size() >= 2) best_out = max(best_out, arms[0] + arms[1]);

		// also possible path made by two sibling arms (already considered if arms contains sd1+1 and sd2+1)
		// finalize
		diam_out[v] = best_out;

		// recurse
		dfs2(v, u);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	if (!(cin >> n)) return 0;
	for (int i = 1; i <= n; ++i) {
		adj[i].clear();
		downv[i] = 0;
		diam_sub[i] = 0;
		upDepth[i] = 0;
		diam_out[i] = 0;
	}
	for (int i = 0; i < n-1; ++i) {
		int u,v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	// root at 1
	dfs1(1, 0);
	upDepth[1] = 0;
	diam_out[1] = 0;
	dfs2(1, 0);

	// answer: consider each edge u-v where parent is u and v is child in dfs1 rooted tree.
	// We computed diam_sub for every node's subtree (w.r.t root=1)
	// diam_out[v] holds diameter of component outside subtree v
	long long ans = 0;
	// To find parent relation, derive parent by checking which side is subtree: use down propagation:
	// We'll run a small BFS to get parent[] from root 1
	vector<int> parent(n+1, 0);
	parent[1] = 0;
	queue<int> q;
	q.push(1);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v : adj[u]) if (v != parent[u]) {
			parent[v] = u;
			q.push(v);
		}
	}

	for (int v = 2; v <= n; ++v) {
		// consider edge parent[v] - v
		int d1 = diam_sub[v];
		int d2 = diam_out[v];
		long long prod = 1LL * d1 * d2;
		if (prod > ans) ans = prod;
	}
	// Also consider edges where parent is 1? above covers all v>=2.
	cout << ans << '\n';
	return 0;
}
