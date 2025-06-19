#include <bits/stdc++.h>
 
using namespace std;
 
#define el  "\n"
#define fi  first
#define se  second
#define name "A"
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
 
int n, m, visited[MAXN];
ll dp[MAXN];
vector<pii> adj[MAXN];
 
void dfs(int u) {
    visited[u] = 1;
    for (pii x : adj[u]) {
        int v = x.fi, w = x.se;
        if (!visited[v]) dfs(v);
        maximize(dp[u], dp[v] + w);
    }
}
 
void process(void) {
    cin >> n >> m;
    FORE(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
		int s, t; 
		cin >> s >> t; 
		
		memset(dp, -0x3f, sizeof(dp));
		dp[t] = 0;

		dfs(s);

		if (dp[s] > -INFF) cout << dp[s]; 
		else cout << "NO PATH";
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