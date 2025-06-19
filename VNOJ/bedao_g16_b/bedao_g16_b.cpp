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

struct Node {
    int v;
    ll w;
    Node(int _v, ll _w) {
        v = _v;
        w = _w;
    }
};

int n, m;
vector<Node> adj[MAXN], DAG[MAXN];
int low[MAXN], num[MAXN], color[MAXN];
ll W[MAXN], dp[MAXN];
stack<int> st;
int scc = 0;

void dfs(int u) {
    static int timeDFS = 0;
    low[u] = num[u] = ++timeDFS;
    st.push(u);
    for (Node x : adj[u]) {
        int v = x.v;
        if (!num[v]) {
            dfs(v);
            minimize(low[u], low[v]);
        } minimize(low[u], num[v]);
    }
    if (low[u] == num[u]) {
        scc++;
        color[u] = scc;
        int v = -1;
        while (v != u) {
            v = st.top();
            low[v] = num[v] = n + 1;
            color[v] = scc;
            st.pop();
        }
    }
}

ll calc(ll x) {
    ll res = 0;
    while (x) {
        res += x;
        x /= 2;
    }
    return res;
}

void graph2DAG(void) {
    FOR(i, 1, n) if (!num[i]) dfs(i);
    FOR(i, 1, n) for (Node x : adj[i]) {
        if (color[x.v] == color[i]) {
            W[color[i]] += calc(x.w);
        } else {
            DAG[color[i]].push_back({color[x.v], x.w});
        }
    }
}

ll solve_dp(int u) {
    if (DAG[u].empty()) {
        return dp[u] = W[u];
    }
    if (dp[u]) return dp[u];
    ll cur = W[u];
    for (Node x : DAG[u]) {
        int v = x.v;
        ll w = x.w;
        maximize(cur, solve_dp(v) + w + W[u]);
    }
    return dp[u] = cur;
}

void process(void) {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    graph2DAG();
    memset(dp, 0, sizeof dp);
    solve_dp(color[1]);
    cout << dp[color[1]];
}

signed main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

    file("bedao_g16_b");

//	int t; cin >> t; while(t--)
	process();
	return 0;
}
