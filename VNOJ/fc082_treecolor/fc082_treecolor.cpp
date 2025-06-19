// Author: tinhnopro (ngh)
#include<bits/stdc++.h>

using namespace std;

#define el '\n'
#define fi first
#define se second
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORE(i, a, b) for (int i = (a); i <= (int) (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (int) (b); --i)
#define all(v) (v).begin(), (v).end()

#define mask(x) (1LL << (x))
#define getbit(i, mask) ((mask >> i) & 1LL)
#define onbit(i, mask) (mask | MASK(i))
#define offbit(i, mask) mask & ~(MASK(i))
#define cntbit(x) __builtin_popcountll(x)

#define name "fc082_treecolor"

using ll = long long;
using ld = long double;
using ii = pair<int, int>;
using vi = vector<int>;

template<class X, class Y> bool maximize(X &a, Y b) { return a < b ? a = b, 1 : 0; }
template<class X, class Y> bool minimize(X &a, Y b) { return a > b ? a = b, 1 : 0; }

const int MAXN = 1e5 + 11; 
// const int MOD = 1e9 + 7; 
// const int INF = 1e9 + 11; 
// const ll INFF = (ll) 1e18 + 11;
// const int LOG = 22;
// const int BASE = 311;

int n, c[MAXN], ans[MAXN];
vi adj[MAXN];
set<int> s[MAXN];

void dfs(int u, int parent) {
    s[u].insert(c[u]);
    for (int &v : adj[u]) if (v != parent) {
        dfs(v, u);
        if (s[u].size() < s[v].size()) swap(s[u], s[v]);
        for (int x : s[v]) s[u].insert(x);
        s[v].clear();
    }
    ans[u] = s[u].size();
}

int32_t main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);

    if (fopen(name".inp", "r")) {
        freopen(name".inp", "r", stdin);
        freopen(name".out", "w", stdout);
    }
    //___________________________________
    cin >> n;
    FORE(i, 1, n - 1) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    FORE(i, 1, n) cin >> c[i];

    dfs(1, 1);

    FORE(i, 1, n) cout << ans[i] << el; 

    return 0;
}
