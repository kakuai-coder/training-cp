#include <bits/stdc++.h>

#define TIME (1.0 * clock() / CLOCKS_PER_SEC)
#define all(v) (v).begin(), (v).end()

using namespace std;

template <typename T>
bool maxim(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}

template <typename T>
bool minim(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}

template <typename T>
int siz(const T &a) {
    return a.size();
}

///mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 2e5 + 5, LOG = 20;

struct Node {
    int v, c, e;

    Node(int _v = 0, int _c = 0, int _e = 0) : v(_v), c(_c), e(_e) {}
};

int n;
vector<Node> g[MAXN];
int sum[MAXN], depth[MAXN], up[LOG + 1][MAXN];

void dfs_pre(int u, int pre) {

    up[0][u] = pre;

    for (int i = 1; i <= LOG; ++i) up[i][u] = up[i - 1][up[i - 1][u]];

    for (Node &x : g[u]) {
        int v = x.v;

        if (v == pre) continue;

        depth[v] = depth[u] + 1;

        dfs_pre(v, u);
    }
}

int lca(int u, int v) {
    if (u == v) return u;

    if (depth[u] < depth[v]) swap(u, v);

    for (int i = LOG; ~i; --i) if (depth[up[i][u]] >= depth[v]) {
        u = up[i][u];
    }

    if (u == v) return u;

    for (int i = LOG; ~i; --i) if (up[i][u] != up[i][v]) {
        u = up[i][u];
        v = up[i][v];
    }

    return up[0][u];
}

int64_t ans = 0;

void dfs_calc(int u, int pre) {
    for (Node &x : g[u]) {
        int v = x.v;
        int c = x.c;
        int e = x.e;

        if (v == pre) continue;

        dfs_calc(v, u);

        sum[u] += sum[v];

        if (1LL * c * sum[v] > e) {
            ans += e;
        } else {
            ans += 1LL * c * sum[v];
        }
    }
}

void kakuai(void) {
    cin >> n;

    for (int i = 1; i < n; ++i) {
        int u, v, c, e;

        cin >> u >> v >> c >> e;

        g[u].push_back({v, c, e});
        g[v].push_back({u, c, e});
    }

    dfs_pre(1, 0);

    for (int i = 1; i < n; ++i) {
        sum[i]++;
        sum[i + 1]++;
        sum[lca(i, i + 1)] -= 2;
    }

    dfs_calc(1, 0);

    cout << ans;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

#define cherry "travel"
    if (fopen(cherry".inp", "r")) {
        freopen(cherry".inp", "r", stdin);
        freopen(cherry".out", "w", stdout);
    }

    int T = 1;
//    cin >> T;
    while (T--) {
        kakuai();
//        cout << '\n';
    }

    cerr << '\n' << TIME << "ms\n";
}
