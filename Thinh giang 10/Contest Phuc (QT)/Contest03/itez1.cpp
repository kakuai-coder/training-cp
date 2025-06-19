#include <bits/stdc++.h>

using namespace std;

#define el  "\n"
#define fi  first
#define se  second
#define name "itez1"
#define BIT(x, i) ((x) & (1 << (i)))
#define MASK(x) (1 << (x))
#define ALL(v) ((v).begin(), (v).end())
#define FOR(i, a, b) for (int i = (a), _b = (b); i < _b; ++i)
#define FORE(ti, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORDE(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)

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

int n, q, a[MAXN], seg[4 * MAXN];

void build(int id, int l, int r) {
    if (l == r) return void (seg[id] = a[l]);
    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    seg[id] = max(seg[id << 1], seg[id << 1 | 1]);
}

void update(int id, int l, int r, int pos, int val) {
    if (l > pos || pos > r) return ;
    if (l == r)  return void(seg[id] = val);
    int mid = (l + r) >> 1;
    update(id << 1, l, mid, pos, val);
    update(id << 1 | 1, mid + 1, r, pos, val);
    seg[id] = max(seg[id << 1], seg[id << 1 | 1]);
}

int query(int id, int l, int r, int u, int v) {
    if (l > v || r < u) return -INF;
    if ( u <= l && r <= v) return seg[id];
    int mid = (l + r) >> 1;
    return max(query(id << 1, l, mid, u, v),
               query(id << 1 | 1, mid + 1, r, u, v));
}

void process(void) {
    cin >> n;
    FORE(i, 1, n) cin >> a[i];
    build(1, 1, n);
    cin >> q;
    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) update(1, 1, n, x, y);
        else cout << query(1, 1, n, x, y) << el;
    }
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	if (fopen(name".inp", "r")) {
        freopen(name".inp", "r", stdin);
        freopen(name".out", "w", stdout);
	}
//	int t; cin >> t; while(t--)
	process();
	return 0;
}
