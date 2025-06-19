#include <bits/stdc++.h>

using namespace std;

#define int long long
#define FOR(i, a, b) for(int i = a; i <= b; i ++)
#define FORD(i, b, a) for(int i = b; i >= a; i --)
#define MASK(o) (1ll << (o))
#define __builtin_popcount __builtin_popcountll
#define C_BIT(mask) __builtin_popcount(mask)
#define BIT(mask, i) ((mask) & (1ll << (i)))
#define ONBIT(mask, i) ((mask) | (1ll << (i)))
#define ii pair<int, int>
#define fi first
#define se second
#define pb push_back

const int maxN = 29;

int n, m;
int bac[maxN];
int add = 0;
int c[maxN][maxN];
const int oo = 1e10 + 8;
int odd[maxN];
int C = 0;
vector<ii> Edge[maxN];

int dp[MASK(22) + 4];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> n >> m;

    FOR(i, 1, n)
        FOR(j, 1, n)
            c[i][j] = oo;

    FOR(i, 1, n)
        c[i][i] = 0;

    add = 0;
    FOR(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        bac[u] ++;
        bac[v] ++;
        Edge[u].pb({w, v});
        Edge[v].pb({w, u});
        add += w;
    }

    FOR(i, 1, n)
        for(auto x: Edge[i]) {
            c[i][x.se] = c[x.se][i] = min(c[i][x.se], x.fi);
        }

    FOR(k, 1, n)
        FOR(i, 1, n)
            FOR(j, 1, n)
                c[i][j] = min(c[i][j], c[i][k] + c[k][j]);

    FOR(i, 1, n) {
        if (c[1][i] == oo && bac[i] > 0) {
            cout << -1;
            return 0;
        }
        if (bac[i] % 2)
            odd[++C] = i;
    }

    FOR(i, 0, MASK(C) - 1)
        dp[i] = oo;

    dp[MASK(C) - 1] = 0;

    FORD(mask, MASK(C) - 1, 1) {
        FOR(p, 0, C - 2) FOR(i, p + 1, C - 1)
            if (BIT(mask, i) && BIT(mask, p) && i != p) {
                int m = MASK(i) + MASK(p);
                dp[mask - m] = min(dp[mask - m], dp[mask] + c[odd[i + 1]][odd[p + 1]]);
            }
    }

    cout << dp[0] + add;

    return 0;
}