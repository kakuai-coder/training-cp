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

const int MAXN = 2011;

int n, a[MAXN];
ll T, d[MAXN];

void Dijsktra(void) {
    FOR(i, 1, a[1] - 1) d[i] = 1e18 + 11;
    d[0] = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll> >, greater<pair<ll, ll> > > pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        ll u = pq.top().se;
        ll d_u = pq.top().fi;
        pq.pop();
        if (d_u > d[u]) continue;
        FOR(i, 2, n) {
            int v = (d[u] + a[i]) % a[1];
            if (d[v] > d[u] + a[i]) {
                d[v] = d[u] + a[i];
                pq.push({d[v], v});
            }
        }
    }
}

void process(void) {
    cin >> n >> T;
    FOR(i, 1, n) cin >> a[i];
    sort(a + 1, a + n + 1);
    Dijsktra();
    ll ans = 0;
    FOR(i, 0, a[1] - 1) if (d[i] != 1e18 + 11) {
        ans += max(0ll, (T - d[i]) / a[1] + 1);
    }
    cout << ans;
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #define Task "money"
    if (fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

    // int t; cin >> t; while (t--)
    process();

    return 0;
}
