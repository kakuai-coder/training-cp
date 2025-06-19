#include <bits/stdc++.h>
#define all(v) v.begin(),v.end()
#define ii pair <int, int>
#define vi vector <int>
#define vvi vector <vi>
#define vvvi vector <vvi>
#define ld long double
#define ll long long
#define pb push_back
#define BIT(mask,i) (((mask) >> (i)) & 1ll)
#define MASK(i) (1ll << i)
#define ONBIT(mask,i) (mask  (1ll << (i)))
#define OFFBIT(mask, i) (mask &~ (1ll << (i)))
#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define FORM(i,mask) for (int i = mask; i; i = (i - 1) & mask)
#define FORV(v,h) for (auto v : h)
using namespace std;
const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 105;
const ll oo = 1e18 + 7;
const int base = 31;
const int BLOCK = sqrt(MAXN);
const int LOG = 63 - __builtin_clzll(MAXN);
int n, m;
int w[45], v[45], c[45];
ll ans;
vector <pair <int, ll>> a, b;

void get1() {
    ll wei = 0;
    ll val = 0;
    FOR(i,n / 2 + 1,n) {
        if (c[i]) {
            wei += w[i];
            val += v[i];
        }
    }
    if (wei <= 0LL + m) b.pb({wei, val});
}

void sinh1(int i) {
    if (i == n + 1) {
        get1();
        return;
    }
    FOR(j,0,1) {
        c[i] = j;
        sinh1(i + 1);
    }
}

void get2() {
    ll wei = 0;
    ll val = 0;
    FOR(i,1,n / 2) {
        if (c[i]) {
            wei += w[i];
            val += v[i];
        }
    }
    if (wei <= 0LL + m) a.pb({wei, val});
}

void sinh2(int i) {
    if (i == n / 2 + 1) {
        get2();
        return;
    }
    FOR(j,0,1) {
        c[i] = j;
        sinh2(i + 1);
    }
}

main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    freopen("dttui1.inp", "r", stdin);
    freopen("dttui1.ans", "w", stdout);

    cin >> n >> m;
    FOR(i,1,n) cin >> w[i] >> v[i];

    sinh2(1);
    sinh1(n / 2 + 1);
    sort(all(a));
    sort(all(b));

    for (int i = 0; i < a.size(); ++i) cerr << a[i].first << ' ' << a[i].second << '\n';
    cerr << '\n';
    for (int i = 0; i < b.size(); ++i) cerr << b[i].first << ' ' << b[i].second << '\n';

    ll MAX = -oo;
    FOR(j,0,a.size() - 1) {
        MAX = max(MAX, a[j].second);
        a[j].second = MAX;
    }
    int j = a.size() - 1;
    FORV(res,b) {
        ll wei = res.first;
        ll val = res.second;
        while (j >= 1 && a[j].first + wei > m) j--;

        cout << wei << ' ' << val << '\n';
        cout << a[j].first << ' ' << a[j].second << "\n\n";
        if (a[j].first + wei <= m) ans = max(ans, val + a[j].second);
    }

    cout << ans << '\n';

    return 0;
}
