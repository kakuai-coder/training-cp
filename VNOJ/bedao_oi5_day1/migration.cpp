// Author: tinhnopro (tinh nop)
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5011;
const int64_t INF = (int64_t) 1e18 + 11;

int n;
vector<pair<int, int> > adj[MAXN];
int sz[MAXN];
int64_t dp[MAXN][MAXN][2], dist[MAXN];

void minimize(int64_t &a, int64_t b) {
    if (a > b) a = b;
}

void dfs(int u, int parent = -1) {
    for (auto &x : adj[u]) if (x.first != parent) {
        dist[x.first] = dist[u] + x.second;
        dfs(x.first, u);
    }
}

void dfs_dp(int u, int parent = -1) {
    memset(dp[u], 0x3f, sizeof(dp[u]));
    sz[u] = 1;
    dp[u][1][0] = dp[u][0][0] = 0;
    dp[u][1][1] = -dist[u];
    for (auto &x : adj[u]) if (x.first != parent) {
        int v = x.first;
        int w = x.second;
        dfs_dp(v, u);
        for (int cntu = sz[u]; cntu >= 0; --cntu) {
            for (int cntv = 0; cntv <= sz[v]; ++ cntv) {
                int64_t W = 2 * w * (cntv > 0);
                minimize(dp[u][cntu + cntv][0], dp[u][cntu][0] + dp[v][cntv][0] + W);
                minimize(dp[u][cntu + cntv][1], dp[u][cntu][1] + dp[v][cntv][0] + W);
                minimize(dp[u][cntu + cntv][1], dp[u][cntu][0] + dp[v][cntv][1] + W);
            }
        }
        sz[u] += sz[v];
    }
}

void run_case(void) {
    cin >> n;
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    dfs(1);
    dfs_dp(1);
    for (int i = 1; i <= n; ++i) {
        cout << dp[1][i][1] << '\n';
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    if (fopen("migration.inp", "r")) {
        freopen("migration.inp", "r", stdin);
        freopen("migration.out", "w", stdout);
    }

    int tests = 1;
    // cin >> tests;
    while (tests--) run_case();
    cerr << "\nRuntime: " << 1.0 * clock() / CLOCKS_PER_SEC << ".s tinhnop";
}

