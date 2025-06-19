#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define BIT(x, i) ((x) & (1 << (i)))
#define MASK(x) (1 << (x))
#define ALL(v) (v).begin(), (v).end()
#define FOR(i, a, b) for (int i = (a), _b = (b); i < _b; ++i)
#define FORE(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORDE(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define file(name) if (fopen(name".inp", "r")) { freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;

template<class X, class Y> bool maximize(X &a, const Y &b) { return a < b ? a = b, 1 : 0; };
template<class X, class Y> bool minimize(X &a, const Y &b) { return a > b ? a = b, 1 : 0; };

/// Author: tinhnopro
// end of template

const int MAXN = 1e3 + 11, MAX = 1e6 + 11;
//const int MOD = 1e9 + 7;
//const int INF = 1e9 + 11; const ll INFF = 1e18 + 11;
const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};

int m, n, xmax, ymax, dmax, depth[MAXN][MAXN];
char a[MAXN][MAXN];
bool visited[MAXN][MAXN];

void dfs(int x, int y) {
    if (maximize(dmax, depth[x][y])) {
        xmax = x;
        ymax = y;
    }
    visited[x][y] = 1;
    FOR(i, 0, 4) {
        int adj_x = x + dx[i], adj_y = y + dy[i];
        if (adj_x == 0 || adj_x > m || adj_y  == 0 ||  adj_y > n) continue;
        if (visited[adj_x][adj_y] || a[adj_x][adj_y] == '#') continue;
        depth[adj_x][adj_y] = depth[x][y] + 1;
        dfs(adj_x, adj_y);
    }
}

void process(void) {
    cin >> m >> n;
    FORE(i, 1, m) FORE(j, 1, n) cin >> a[i][j];
    int ans = 0;
    FORE(i, 1, m) {
        FORE(j, 1, n) if (a[i][j] == '.') {
            xmax = ymax = dmax = -1;
            dfs(i, j);
				//    cout << xmax << " " << ymax << "\n";
						memset(depth, 0, sizeof depth);
						memset(visited, 0, sizeof visited);
						dmax = -1;
						dfs(xmax, ymax);
						ans = max(ans, dmax);
        }
    }

		cout << ans; 
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	file("F");
//	int t; cin >> t; while(t--)
	process();
	return 0;
}
