#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;

vector<int> adj[MAXN];
int down[MAXN], up[MAXN], par[MAXN], downD[MAXN];
int n;

void dfs_down(int u, int p) {
    down[u] = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs_down(v, u);
        down[u] = max(down[u], down[v] + 1);
    }
}

void dfs_up(int u, int p) {
	par[u] = p;
    int best1 = -1, best2 = -1;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (down[v] > best1) {
            best2 = best1;
            best1 = down[v];
        } else if (down[v] > best2) {
            best2 = down[v];
        }
    }

    downD[u] = best1 + best2 + 2;

    for (int v : adj[u]) {
        if (v == p) continue;
		downD[u] = max(downD[v], downD[u]);
        int use = (down[v] == best1) ? best2 : best1;
        up[v] = max(up[u] + 1, use + 2);
        dfs_up(v, u);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs_down(1, 1);
    up[1] = 0;
    dfs_up(1, 1);

    int64_t ans = 0;

    for (int u = 1; u <= n; ++u) {
		cout << up[u] << ' ' << downD[u] << '\n';
		ans = max(ans, 1LL * up[u] * downD[u]);
    }

    cout << ans;
}
