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
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define SZ(v) (int) (v).size()
#define ALL(v) (v).begin(), (v).end()
#define MASK(x) (1LL << (x))
#define ONBIT(i, mask) (mask | MASK(i))
#define OFFBIT(i, mask) mask & ~(MASK(i))

template <class X, class Y> bool maximize(X &a, const Y &b) { return a < b ? a = b, 1 : 0; }
template <class X, class Y> bool minimize(X &a, const Y &b) { return a > b ? a = b, 1 : 0; }

const int MAXN = 1e6 + 11;
const int MOD = 1e9 + 7; 
int n, a[MAXN];
ll prefOdd[MAXN], prefEven[MAXN], cntOdd[MAXN], cntEven[MAXN];

void process(void) {
    cin >> n;
    FOR(i, 1, n) cin >> a[i];
    FOR(i, 1, n) {
        prefOdd[i] = prefOdd[i - 1];
        prefEven[i] = prefEven[i - 1];
        if (a[i] & 1) prefOdd[i] += a[i];
        else prefEven[i] += a[i]; 
        cntOdd[i] = cntOdd[i - 1] + (a[i] & 1);
        cntEven[i] = cntEven[i - 1] + !(a[i] & 1);
    }
    ll ans = 0;
    FOR(i, 1, n) {
        if (a[i] & 1) ans += prefEven[i] + 1LL * a[i] * cntEven[i];
        else ans += prefOdd[i] + 1LL * a[i] * cntOdd[i];
        // cout << prefOdd[i] << " " << prefEven[i] << el;
        ans %= MOD;
    }

    cout << ans; 
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #define Task ""
    if (fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

    // int t; cin >> t; while (t--)
    process();

    return 0;
}
