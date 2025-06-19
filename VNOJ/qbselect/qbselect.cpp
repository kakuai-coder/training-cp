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

const int MAXN = 1e4 + 11;
const int INF = 1e9 + 11;

int n, a[MAXN][4], dp[MAXN][MASK(4) + 1];
vector<int> select_row;

void process(void) {
    cin >> n;
    FOR(i, 0, 3) FOR(j, 0, n - 1) {
        cin >> a[j][i];
    }

    FOR(i, 0, n - 1) FOR(j, 0, MASK(4) - 1) dp[i][j] = -INF;

    FOR(mask, 0, MASK(4) - 1) {
        int last1 = -2;
        bool check = true;
        FOR(i, 0, 3) if ((mask >> i) & 1) {
            if (i - last1 < 2) {
                check = false;
                break;
            }
            last1 = i;
        }
        if (!check) continue;
        select_row.push_back(mask);
    }


    int ans = -INF;
    FOR(i, 0, n - 1) FOR(j, 0, 3) maximize(ans, a[i][j]);
    if (ans <= 0) {
        cout << ans;
        return ;
    }

    FOR(i, 0, n - 1) for (int mask : select_row) {
        int res = 0;
        FOR(bit, 0, 3) if ((mask >> bit) & 1) {
            res += a[i][bit];
        }
        if (i == 0) {
            dp[i][mask] = res;
            continue;
        }
        for (int mask2 : select_row) {
            bool check = true;
            FOR(bit, 0, 3) if (((mask >> bit) & 1) && ((mask2 >> bit) & 1)) {
                check = false;
                break;
            }
            if (!check || dp[i - 1][mask2] == -INF) continue;
            maximize(dp[i][mask], res + dp[i - 1][mask2]);
        }
        maximize(ans, dp[i][mask]);
    }
    cout << ans;
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #define Task "qbselect"
    if (fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

//    int t; cin >> t; while (t--)
    process();

    return 0;
}
