#include<bits/stdc++.h>

// Author: Tinhnopro (a.k.a NVT)

using namespace std;

#define el '\n'
#define pii pair<int, int>
#define fi first
#define se second
#define vi vector<int>
#define ll long long
#define ld long double
//#define int long long
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define FORA(it, v) for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
#define SZ(v) (int) (v).size()
#define ALL(v) (v).begin(), (v).end()
#define MASK(x) (1LL << (x))
#define BIT(x, i) ((i) & MASK(x))
#define ONBIT(x, i) ((i) | MASK(x))
#define OFFBIT(x, i) ((i) & ~MASK(x))

template <class X, class Y> bool maximize(X &a, const Y &b) { return a < b ? a = b, 1 : 0; }
template <class X, class Y> bool minimize(X &a, const Y &b) { return a > b ? a = b, 1 : 0; }

int n, c[20][20];
int dp[(1 << 20) + 1][20];

int calc(int i, int mask) {
    if (mask == 0) return 0;
    if (~dp[mask][i]) return dp[mask][i];
    int res = 1e9 + 11;
    FOR(j, 1, n) if ((mask >> (j - 1)) & 1) {
        minimize(res, calc(j, OFFBIT(j - 1, mask)) + c[j][i]);
    }
    return dp[mask][i] = res;
}

void process(void) {
    cin >> n;
    FOR(i, 1, n) FOR(j, 1, n) cin >> c[i][j];

    int res = 1e9 + 11;
    memset(dp, -1, sizeof dp);
    FOR(i, 1, n) {
        minimize(res, calc(i, MASK(n) - 1));
    }
    cout << res;
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #define Task "lem3"
    if (fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

//    int t; cin >> t; while (t--)
    process();

    return 0;
}
