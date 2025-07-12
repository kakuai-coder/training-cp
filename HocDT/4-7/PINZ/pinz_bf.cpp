#include <bits/stdc++.h>
#define ii pair <int, int>
#define vi vector <int>
#define vvi vector <vi>
#define vvvi vector <vvi>
#define ld long double
#define ll long long
#define pb push_back
#define BIT(mask,i) (((mask) >> (i)) & 1ll)
#define MASK(i) (1ll << i)
#define ONBIT(mask,i) (mask | (1ll << (i)))
#define OFFBIT(mask, i) (mask &~ (1ll << (i)))
#define FOR(i,a,b) for (int i=a;i<=b;i++)
#define FORD(i,a,b) for (int i=a;i>=b;i--)
#define FORV(v,h) for (auto v:h)
using namespace std;
const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 105;
const ll oo = 1e18 + 7;
const int LOG = 63 - __builtin_clzll(MAXN);
int n, k;
int a[MAXN], b[MAXN], c[MAXN], d[MAXN], dp[MAXN];
int st[4 * MAXN];
vector <ii> vt[MAXN];

void upd(int id, int l, int r, int u, int v, int val) {
    if (l > v || r < u) return;
    if (l >= u && r <= v) {
        st[id] = max(st[id], val);
        return;
    }
    int mid = (l + r) / 2;
    upd(id * 2, l, mid, u, v, val);
    upd(id * 2 + 1, mid + 1, r, u, v, val);
    st[id] = max(st[id * 2], st[id * 2 + 1]);
}

int get(int id, int l, int r, int u, int v) {
    if (l > v || r < u) return 0;
    if (l >= u && r <= v) return st[id];
    int mid = (l + r) / 2;
    return max(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
}

main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> k;
    FOR(i,1,k) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
        vt[a[i]].pb({1, i});
        vt[b[i] + 1].pb({0, i});
    }

    FOR(i,0,n + 1) {
        sort(vt[i].begin(), vt[i].end());
        FORV(r,vt[i]) {
            int type = r.first;
            int pos = r.second;
            if (type) dp[pos] = get(1, 0, n + 2, 0, c[pos] - 1) + 1;
            else upd(1, 0, n + 2, d[pos], d[pos], dp[pos]);
        }
    }
    int ans = 0;
    FOR(i,0,n + 1) ans = max(ans, dp[i]);

    cout << ans << '\n';

    return 0;
}
