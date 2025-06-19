// Author: tinhnopro (ngh)
#include<bits/stdc++.h>

using namespace std;

#define el '\n'
#define fi first
#define se second
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORE(i, a, b) for (int i = (a); i <= (int) (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (int) (b); --i)
#define all(v) (v).begin(), (v).end()

#define mask(x) (1LL << (x))
#define getbit(i, mask) ((mask >> i) & 1LL)
#define onbit(i, mask) (mask | MASK(i))
#define offbit(i, mask) mask & ~(MASK(i))
#define cntbit(x) __builtin_popcountll(x)

#define name "icpc22_mt_a"

using ll = long long;
using ld = long double;
using ii = pair<int, int>;
using vi = vector<int>;

template<class X, class Y> bool maximize(X &a, Y b) { return a < b ? a = b, 1 : 0; }
template<class X, class Y> bool minimize(X &a, Y b) { return a > b ? a = b, 1 : 0; }

const int MAXN = 311; 
// const int MOD = 1e9 + 7; 
// const int INF = 1e9 + 11; 
// const ll INFF = (ll) 1e18 + 11;
// const int LOG = 22;
// const int BASE = 311;

int n, k;
char a[MAXN];
int dp[MAXN][MAXN][MAXN][2];

int solve(int l, int r, int p1, int p2, int p) {
    if (p1 == k) return 0;
    if (p2 == k) return 1; 
    int &res = dp[l][r][p1][p];
    if (~res) return res; 
    
    if (p == 0) {
        int mx = -2;
        maximize(mx, solve(l, r - 1, p1 + (a[r] == 'B'), p2, p ^ 1));
        maximize(mx, solve(l + 1, r, p1 + (a[l] == 'B'), p2, p ^ 1));
        res = mx; 
    } else {
        int mi = 1e9 + 11; 
        minimize(mi, solve(l, r - 1, p1, p2 + (a[r] == 'B'), p ^ 1));
        minimize(mi, solve(l + 1, r, p1, p2 + (a[l] == 'B'), p ^ 1));
        res = mi; 
    }

    return res;
}

int32_t main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);

    if (fopen(name".inp", "r")) {
        freopen(name".inp", "r", stdin);
        freopen(name".out", "w", stdout);
    }
    //___________________________________
    cin >> n >> k;
    FORE(i, 1, n) cin >> a[i];

    memset(dp, -1, sizeof dp);
    cout << (solve(1, n, 0, 0, 0) == 1 ? "YES" : "NO") << el; 

    return 0;
}
