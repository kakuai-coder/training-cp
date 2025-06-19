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

#define int long long 

template <class X, class Y> bool maximize(X &a, const Y &b) { return a < b ? a = b, 1 : 0; }
template <class X, class Y> bool minimize(X &a, const Y &b) { return a > b ? a = b, 1 : 0; }

const int MAXN = 2e5 + 11;
const int INF = 1e18 + 11;

int n, seg[4 * MAXN], lazy[4 * MAXN];
vi col[MAXN];

void down(int id) {
    if (lazy[id] == 0) return;
    seg[id << 1] += lazy[id];
    seg[id << 1 | 1] += lazy[id];
    lazy[id << 1] += lazy[id];
    lazy[id << 1 | 1] += lazy[id];
    lazy[id] = 0;
}

void update(int id, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return ;
    if (u <= l &&  r <= v) {
        lazy[id] += val;
        seg[id] += val;
        return ;
    }
    int mid = (l + r) >> 1;
    down(id);
    update(id << 1, l, mid, u, v, val);
    update(id << 1 | 1, mid + 1, r, u, v, val);
    seg[id] = max(seg[id << 1], seg[id << 1 | 1]);
}

int getmax(int id, int l, int r, int u, int v) {
    if (v < l || r < u) return -INF;
    if (u <= l && r <= v) return seg[id];
    int mid = (l + r) >> 1;
    down(id);
    return max(getmax(id << 1, l, mid, u, v), getmax(id << 1 | 1, mid + 1, r, u, v));
}

void process(void) {
    cin >> n;
    FOR(i, 1, n) {
        int a, c; 
        cin >> a >> c;
        col[c].push_back(a);
    }

    FOR(i, 1, MAXN - 1) {
        FOR(j, 1, SZ(col[i]) - 1) {
            col[i][j] += col[i][j - 1];
        }
    }

    int q; cin >> q;
    while (q--) {
        int type, c, x;
        cin >> type >> c >> x;
        if (type == 2) {
            int val = getmax(1, 1, MAXN - 1, c, c);
            int l = 0, r = col[c].size() - 1, res = -1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (col[c][mid] + val * (mid + 1) <= x) {
                    res = mid;
                    l = mid + 1;
                } else r = mid - 1; 
            }
            cout << res + 1 << el;
        } else {
            update(1, 1, MAXN - 1, 1, c - 1, x);
            update(1, 1, MAXN - 1, c + 1, MAXN - 1, x); 
        }
    }
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #define Task "c"
    if (fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

    // int t; cin >> t; while (t--)
    process();

    return 0;
}
