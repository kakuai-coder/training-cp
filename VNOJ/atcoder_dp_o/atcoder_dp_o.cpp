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

const int MOD = (int) 1e9 + 7;

int n, a[30][30], dp[1 << 22];

void process(void) {
    cin >> n;
    FOR(i, 0, n - 1) FOR(j, 0, n - 1) cin >> a[i][j];

    dp[0] = 1;

    FOR(mask, 0, MASK(n) - 1) {
        int j = __builtin_popcount(mask);
        FOR(i, 0, n - 1) if (!((mask >> i) & 1) && a[j][i]) {
            dp[ONBIT(i, mask)] += dp[mask];
            dp[ONBIT(i, mask)] %= MOD;
        }
    }

    cout << dp[MASK(n) - 1];
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #define Task "atcoder_dp_o"
    if (fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

//    int t; cin >> t; while (t--)
    process();

    return 0;
}
