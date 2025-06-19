// Author: tinhnopro (ngh)
#include<bits/stdc++.h>

using namespace std;

#define el '\n'
#define fi first
#define se second
#define REP(i, a, b) for (int i = (a); i < (b); ++i)
#define FOR(i, a, b) for (int i = (a); i <= (int) (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (int) (b); --i)
#define all(v) (v).begin(), (v).end()

#define mask(x) (1LL << (x))
#define getbit(i, mask) ((mask >> i) & 1LL)
#define onbit(i, mask) (mask | MASK(i))
#define offbit(i, mask) mask & ~(MASK(i))
#define cntbit(x) __builtin_popcountll(x)

#define name "icpc22_mt_c"

using ll = long long;
using ld = long double;
using ii = pair<int, int>;
using vi = vector<int>;

template<class X, class Y> bool maximize(X &a, Y b) { return a < b ? a = b, 1 : 0; }
template<class X, class Y> bool minimize(X &a, Y b) { return a > b ? a = b, 1 : 0; }

const int MAXN = 1e5 + 11; 
// const int MOD = 1e9 + 7; 
// const int INF = 1e9 + 11; 
// const ll INFF = (ll) 1e18 + 11;
// const int LOG = 22;
// const int BASE = 311;

int n, k;
vi adj[MAXN];
ll dp[MAXN][11];

int32_t main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);

    if (fopen(name".inp", "r")) {
        freopen(name".inp", "r", stdin);
        freopen(name".out", "w", stdout);
    }
    //___________________________________
    cin >> n >> k;
    FOR(i, 1, n) {
        int l, r; cin >> l >> r;
        adj[r].push_back(l);
    }

    FOR(i, 0, n) dp[i][0] = 1;

    FOR(j, 1, k) {
        FOR(r, 1, n) {
            dp[r][j] = dp[r - 1][j];
            for (int &l : adj[r]) {
                dp[r][j] += dp[l - 1][j - 1]; 
            }
        }
    } 

    FOR(i, 1, n) {
        FOR(j, 1, k) cout << dp[i][j] << " ";
        cout << el;
    }

    cout << dp[n][k];

    return 0;
}
