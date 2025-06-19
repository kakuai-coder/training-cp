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
const int INF = (int) 1e9 + 11;
//const ll BASE = 311;
//const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};

int n, NodeA, NodeB, par[MAXN], depth[MAXN], max_dist[MAXN];
vi adj[MAXN], path;
bool vist[MAXN], isPath[MAXN];

void create_path(int u) {
    vist[u] = 1;
    for (int v : adj[u]) if (!vist[v]) {
        par[v] = u;
        create_path(v);
    }
}

void find_path(int u, int v) {
    par[u] = 0;
    create_path(u);

    while (v != u) {
        path.push_back(v);
        isPath[v] = true;
        v = par[v];
    }
    isPath[u] = true;
    path.push_back(u);

    reverse(ALL(path));
}

void dfs(int u) {
    max_dist[u] = 1;
    for (int v : adj[u]) {
        if (v == par[u]) continue;
        depth[v] = depth[u] + 1;
        dfs(v);
        if (isPath[v]) continue;
        maximize(max_dist[u], max_dist[v] + 1);
    }
}

void process(void) {
    cin >> n;
    FOR(i, 1, n - 1) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> NodeA >> NodeB;

    find_path(NodeA, NodeB);
    memset(vist, 0, sizeof vist);
    depth[NodeA] = 1;
    dfs(NodeA);

//    for (int x : path) cout << x << " ";
//    cout << el;

//    FOR(i, 1, n) cout << depth[i] << " ";
//    cout << el;

//    FOR(i, 1, n) cout << max_dist[i] << " ";
//    cout << el;

    int ans = -INF, distA = 0;
    FOR(i, 0, path.size() - 2) {
        int u = path[i];
        int v = path[i + 1];
        maximize(distA, max_dist[u] + depth[u] - depth[NodeA]);
        int distB = max_dist[v] + depth[NodeB] - depth[v];
        maximize(distB, max_dist[NodeB]);
//        cout << distA << " " << distB << el;
        maximize(ans, min(distA, distB));
    }
    cout << ans;
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

    file("bedao_r02_tourist");

//	int t; cin >> t; while(t--)
	process();
	return 0;
}
