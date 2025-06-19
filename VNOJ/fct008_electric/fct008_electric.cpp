/*
    Author: tinhnopro (ngh)
    link: https://oj.vnoi.info/problem/fct008_electric
*/
#include<bits/stdc++.h>

using namespace std;

#define el '\n'
#define fi first
#define se second
#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define REPN(i, n) for (int i = 1; i <= (int) (n); ++i)
#define FOR(i, a, b) for (int i = (a); i <= (int) (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (int) (b); --i)
#define all(v) (v).begin(), (v).end()

#define mask(x) (1LL << (x))
#define getbit(i, mask) ((mask >> i) & 1LL)
#define onbit(i, mask) (mask | MASK(i))
#define offbit(i, mask) mask & ~(MASK(i))
#define cntbit(x) __builtin_popcountll(x)

#define name "fct008_electric"

using ll = long long;
using ld = long double;
using ii = pair<int, ll>;
using vi = vector<int>;

template<class X, class Y> bool maximize(X &a, Y b) { return a < b ? a = b, 1 : 0; }
template<class X, class Y> bool minimize(X &a, Y b) { return a > b ? a = b, 1 : 0; }

const int MAXN = 4e3 + 11; 
// const int MOD = 1e9 + 7; 
// const int INF = 1e9 + 11; 
// const ll INFF = (ll) 1e18 + 11;
const int LOG = 22;
// const int BASE = 311;

struct Edge {
    int u, v;
    ll w;
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

};

bool cmp(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

int n, m, q;
vector<Edge> edges; 
vector<ii> adj[MAXN];

struct DSU {
    int lab[MAXN];

    DSU() {
        memset(lab, -1, sizeof lab);
    }

    int find_par(int u) {
        return lab[u] < 0 ? u : lab[u] = find_par(lab[u]);
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

int up[LOG + 1][MAXN], depth[MAXN];
ll mx[LOG + 1][MAXN];

void dfs(int u, int parent) {
    for (ii &x : adj[u]) {
        int v = x.fi;
        int w = x.se;
        if (v == parent) continue;
        up[0][v] = u;
        mx[0][v] = w;
        depth[v] = depth[u] + 1; 
        dfs(v, u);
    }
}
ll lifting(int u, int v) {

    if (depth[u] < depth[v]) swap(u, v);
    
    ll ans = -1;

    FORD(i, LOG, 0) if (depth[up[i][u]] >= depth[v]) {
        maximize(ans, mx[i][u]);
        u = up[i][u];
    }

    if (u == v) return ans; 

    FORD(i, LOG, 0) if (up[i][u] != up[i][v]) {
        maximize(ans, mx[i][u]);
        maximize(ans, mx[i][v]);
        u = up[i][u];
        v = up[i][v];
    }

    maximize(ans, mx[0][u]);
    maximize(ans, mx[0][v]);

    return ans;
}

void buildLCA(void) {
    FOR(i, 1, LOG) FOR(u, 1, n) {
        up[i][u] = up[i - 1][up[i - 1][u]];
        mx[i][u] = max(mx[i - 1][up[i - 1][u]], mx[i - 1][u]);
    }
}

void process(void) {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v, w; 
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    sort(all(edges), cmp);
    ll mst = 0; 
    for (const Edge &x : edges) {
        if (!dsu.union_set(x.u, x.v)) continue;
        adj[x.u].push_back({x.v, x.w});
        adj[x.v].push_back({x.u, x.w});
        mst += x.w;
    }

    up[0][1] = 1; 
    mx[0][1] = 0;
    dfs(1, 1);
    buildLCA();

    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << mst - lifting(a, b) << el;
    }
}

int32_t main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);

    if (fopen(name".inp", "r")) {
        freopen(name".inp", "r", stdin);
        freopen(name".out", "w", stdout);
    }
    //___________________________________
    // int t; cin >> t; while (t--) 
    process();

    cerr << el << "Runtime: " << 1.0 * clock() / CLOCKS_PER_SEC << ".s" << el;
    return 0;
}
