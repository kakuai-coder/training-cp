#include <bits/stdc++.h>
using namespace std;
const long long oo = 1e18 + 7;
int n;
long long ans;
int par[200005];
vector <pair <int, int>> g[200005];
long long dp[200005][2], rr[200005][2], pre[200005][2], suf[200005][2];
long long res1[200005], res2[200005], pree[200005], suff[200005];

void DFS(int u, int parent) {
    for (auto r : g[u]) {
        int v = r.first;
        int w = r.second;
        if (v == parent) continue;
        par[v] = w;
        DFS(v, u);
        if (dp[v][1] + w > dp[u][0]) {
            dp[u][0] = dp[v][1] + w;
            if (dp[u][0] > dp[u][1]) swap(dp[u][0], dp[u][1]);
        }
        res1[u] = max(res1[u], res1[v]);
        pre[v][0] = dp[u][0];
        pre[v][1] = dp[u][1];
        pree[v] = res1[u];
    }
    dp[u][0] = dp[u][1] = res1[u] = 0;
    for (int j = g[u].size() - 1; j >= 0; j--) {
        int v = g[u][j].first;
        int w = g[u][j].second;
        if (v == parent) continue;
        if (dp[v][1] + w > dp[u][0]) {
            dp[u][0] = dp[v][1] + w;
            if (dp[u][0] > dp[u][1]) swap(dp[u][0], dp[u][1]);
        }
        res1[u] = max(res1[u], res1[v]);
        suf[v][0] = dp[u][0];
        suf[v][1] = dp[u][1];
        suff[v] = res1[u];
    }
    res1[u] = max(res1[u], dp[u][0] + dp[u][1]);
}

void reroot(int u, int parent) {
    for (int j = 0; j < g[u].size(); j++) {
        int v = g[u][j].first;
        int w = g[u][j].second;
        if (v == parent) continue;
        rr[u][0] = rr[u][1] = res2[u] = 0;
        if (rr[parent][1] + par[u] > rr[u][0]) {
            rr[u][0] = rr[parent][1] + par[u];
            if (rr[u][0] > rr[u][1]) swap(rr[u][0], rr[u][1]);
        }
        res2[u] = max(res2[u], res2[parent]);
        if (j > 0) {
            int res = g[u][j - 1].first;
            if (res == parent) {
                if (j > 1) {
                    res = g[u][j - 2].first;
                    if (pre[res][0] > rr[u][0]) {
                        rr[u][0] = pre[res][0];
                        if (rr[u][0] > rr[u][1]) swap(rr[u][0], rr[u][1]);
                    }
                    if (pre[res][1] > rr[u][0]) {
                        rr[u][0] = pre[res][1];
                        if (rr[u][0] > rr[u][1]) swap(rr[u][0], rr[u][1]);
                    }
                    res2[u] = max(res2[u], pree[res]);
                }
            } else {
                if (pre[res][0] > rr[u][0]) {
                    rr[u][0] = pre[res][0];
                    if (rr[u][0] > rr[u][1]) swap(rr[u][0], rr[u][1]);
                }
                if (pre[res][1] > rr[u][0]) {
                    rr[u][0] = pre[res][1];
                    if (rr[u][0] > rr[u][1]) swap(rr[u][0], rr[u][1]);
                }
                res2[u] = max(res2[u], pree[res]);
            }
        }
        if (j + 1 < g[u].size()) {
            int res = g[u][j + 1].first;
            if (res == parent) {
                if (j + 2) {
                    res = g[u][j + 2].first;
if (suf[res][0] > rr[u][0]) {
                        rr[u][0] = suf[res][0];
                        if (rr[u][0] > rr[u][1]) swap(rr[u][0], rr[u][1]);
                    }
                    if (suf[res][1] > rr[u][0]) {
                        rr[u][0] = suf[res][1];
                        if (rr[u][0] > rr[u][1]) swap(rr[u][0], rr[u][1]);
                    }
                    res2[u] = max(res2[u], suff[res]);
                }
            } else {
                if (suf[res][0] > rr[u][0]) {
                    rr[u][0] = suf[res][0];
                    if (rr[u][0] > rr[u][1]) swap(rr[u][0], rr[u][1]);
                }
                if (suf[res][1] > rr[u][0]) {
                    rr[u][0] = suf[res][1];
                    if (rr[u][0] > rr[u][1]) swap(rr[u][0], rr[u][1]);
                }
                res2[u] = max(res2[u], suff[res]);
            }
        }
        res2[u] = max(res2[u], rr[u][0] + rr[u][1]);
        ans = min(ans, max(res1[v], res2[u]));
        reroot(v, u);
    }
}

main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    ans = oo;
    DFS(1, 0);
    reroot(1, 0);
//    for (int i = 1; i <= n; i++) {
//        cout << i << " ";
//        for (auto v : g[i]) cout << v.first << " ";
//        cout << '\n';
//    }

    cout << ans << '\n';

    return 0;
}