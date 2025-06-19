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

int n, m, dp[MAXN];
vi adj[MAXN];

int dfs(int u) {
    if (dp[u]) return dp[u];
    for (int v : adj[u]) {
        dp[v] = dfs(v);
        maximize(dp[u], dp[v] + 1);
    }
    return dp[u];
}

void process(void) {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }

    FOR(i, 1, n) dfs(i);

    int longest = 0;
    FOR(i, 1, n) maximize(longest, dp[i]);

    cout << longest;
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

    file("atcoder_dp_g");

//	int t; cin >> t; while(t--)
	process();
	return 0;
}
