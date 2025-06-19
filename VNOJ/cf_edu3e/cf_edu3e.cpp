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

struct Edge {
    int u, v, w;

    Edge() {
         u = v = w = 0;
    }

    Edge(int _u, int _v, int _w) {
        u = _u; v = _v; w = _w;
    }

    bool operator <(const Edge &other) {
        return w < other.w;
    }
};

struct DSU {
    int lab[MAXN];

    DSU() {
        memset(lab, -1, sizeof lab);
    }

    int find_par(int u) {
        return lab[u] > 0 ? lab[u] = find_par(lab[u]) : u;
    }

    bool union_set(int u, int v) {
        u = find_par(u);
        v = find_par(v);

        if (u == v) return false;

        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
} dsu;

int n, m;
Edge edges[MAXN];
ll totalW = 0;
map<pii, int> mark;

void kruskal(void) {
    sort(edges + 1, edges + m + 1);
    FOR(i, 1, m) {
        if (!dsu.union_set(edges[i].u, edges[i].v)) continue;
        totalW += edges[i].w;
        int u = edges[i].u, v = edges[i].v;
        mark[{u, v}] = mark[{v, u}] = edges[i].w;
    }
}

void process(void) {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }
    kruskal();
    cout << totalW << el;
    FOR(i, 1, m) {
        int u = edges[i].u, v = edges[i].v;
        ll res = totalW - mark[{u, v}] + edges[i].w;
        cout << res << el;
    }
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

    file("cf_edu3e");

//	int t; cin >> t; while(t--)
	process();
	return 0;
}
