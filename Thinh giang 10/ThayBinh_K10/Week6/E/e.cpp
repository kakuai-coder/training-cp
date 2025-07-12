#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define BIT(x, i) ((x) & (1 << (i)))
#define MASK(x) (1 << (x))
#define ALL(v) (v).begin(), (v).end()
#define FOR(i, a, b) for (int i = (a), _b = (b); i < _b; ++i)
#define FORE(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORDE(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define file(name) if (fopen(name".inp", "r")) { freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;

template<class X, class Y> bool maximize(X &a, const Y &b) { return a < b ? a = b, 1 : 0; };
template<class X, class Y> bool minimize(X &a, const Y &b) { return a > b ? a = b, 1 : 0; };

/// Author: tinhnopro
// end of template

const int MAXN = 5e5 + 11, MAX = 1e6 + 11;
//const int MOD = 1e9 + 7;
const int INF = 1e9 + 11; const ll INFF = 1e18 + 11;
//const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};

int bit[MAXN], n, q, a[MAXN];

void update(int x) {
    for (; x <= n; x += x & - x) bit[x]++;
}

int Get(int x) {
    int res = 0;
    for (; x >= 1; x &= x - 1) res += bit[x];
    return res;
}

void Compress() {
    vector<pii> v;
    FORE(i, 1, n) v.push_back({a[i], i});
    sort(ALL(v));
    int cnt = 0, last = INF;
    FOR(i, 0, n) {
        if (last != v[i].fi) {
            cnt++;
            last = v[i].fi;
        }
        a[v[i].se] = cnt;
    }
}

void process(void) {
    cin >> n;
    FORE(i, 1, n) cin >> a[i];
    ll res = 0;
    Compress();
//    FORE(i, 1, n) cout << a[i] << "\n";
    FORDE(i, n, 1) {
        res += Get(a[i] - 1);
        update(a[i]);
    }
    cout << res;
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	file("A");
//	int t; cin >> t; while(t--)
	process();
	return 0;
}
