#include <bits/stdc++.h>

using namespace std;

#define el  "\n"
#define ll  long long
#define ull unsigned long long
#define pii pair<int, int>
#define vi  vector<int>
#define fi  first
#define se  second
#define ALL(v) (v).begin(), (v).end()
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define FORX(i, a, b, x) for (int i = (a), _b = (b); i <= _b; i += (x))
#define BIT(x, i) ((x) & (1LL << (i)))
#define MASK(x) (1LL << (x))
#define ONBIT(x, i) ((x) | (1LL << (i)))
#define OFFBIT(x, i) ((x) & ~(1LL << (i)))
#define file(name) if (fopen(name".inp", "r")) freopen(name".inp", "r", stdin), freopen(name".out", "w", stdout)

template<class X, class Y> bool maximize(X &a, const Y &b) { return a < b ? a = b, 1 : 0; };
template<class X, class Y> bool minimize(X &a, const Y &b) { return a > b ? a = b, 1 : 0; };

/// Author: tinhnopro
// end of template

const int MAXN = (int) 5e5 + 11;
//const int MOD = (int) 1e9 + 7;
//const ll INF = (ll) 1e18 + 11;
//const ll BASE = 311;
//const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};

int n, m, q;
pii edges[MAXN];
int mark[MAXN], queries[MAXN], res[MAXN];

struct DSU {
    int lab[MAXN];
    int num_cc;

    DSU() {
        memset(lab, 0, sizeof lab);
        num_cc = 0;
    }

    void make_set(int u) {
        lab[u] = -1;
    }

    int find_par(int u) {
        return lab[u] > 0 ? lab[u] = find_par(lab[u]) : u;
    }

    void union_set(int u, int v) {
        u = find_par(u);
        v = find_par(v);
        if (u == v) return ;
        num_cc--;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
    }
} dsu;

void process(void) {
    cin >> n >> m >> q;
    FOR(i, 1, m) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
    }
    FOR(i, 1, n) dsu.make_set(i);
    FOR(i, 1, q) {
        cin >> queries[i];
        mark[queries[i]] = 1;
    }
    dsu.num_cc = n;
    FOR(i, 1, m) if (!mark[i]) dsu.union_set(edges[i].fi, edges[i].se);

    FORD(i, q, 1) {
        res[i] = dsu.num_cc;
        int id = queries[i];
        dsu.union_set(edges[id].fi, edges[id].se);
    }
    FOR(i, 1, q) cout << res[i] << el;
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

    file("qhroad");

//	int t; cin >> t; while(t--)
	process();
	return 0;
}
