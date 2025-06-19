/*
    Author: Tinhnopro (Tinh nop)
    From: CHV Phu Tho
 */
#include <bits/stdc++.h>

using namespace std;

template <typename T, int D>
struct vec : public vector<vec<T, D - 1>> {
    static_assert(D >= 1);
    template <typename... Args>
    vec(int n = 0, Args... args) : vector<vec<T, D - 1>>(n, vec<T, D - 1>(args...)) {}
};

template <typename T>
struct vec<T, 1> : public vector<T> {
    vec(int n = 0, T val = T()) : vector<T>(n, val) {}
};

template <typename T>
using tpair = pair<T, T>;

template <typename T>
int Size(const T &a) { return a.size(); }

template <typename T1, typename T2>
bool maximize(T1 &a, T2 b) {
    return a < b ? a = b, true : false;
}

template <typename T1, typename T2>
bool minimize(T1 &a, T2 b) {
    return a > b ? a = b, true : false;
}
// End of tempalte
const int MAXN = 1e5 + 11;
const int LOG = 17;

int n;
vector <int> adj[MAXN];
int depth[MAXN], par[LOG + 10][MAXN];

void dfs(int u, int parent = 0) {
    par[0][u] = parent;
    for (int i = 1; i <= LOG; ++i) par[i][u] = par[i - 1][par[i - 1][u]];
    for (auto &v : adj[u]) if (v != parent) {
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

int LCA(int u, int v) {
    if (u == v) return u;
    if (depth[u] < depth[v]) swap(u, v);

    for (int i = LOG; i >= 0; --i) if (depth[par[i][u]] >= depth[v]) {
        u = par[i][u];
    }

    if (u == v) return u;

    for (int i = LOG; i >= 0; --i) if (par[i][u] != par[i][v]) {
        u = par[i][u];
        v = par[i][v];
    }

    return par[0][u];
}

void Tinhnopro(void) {
    while (cin >> n) {
        if (n == 0) return ;

        for(int i = 1; i <= n; ++i) {
            adj[i].clear();
        }

        for (int i = 1, u, v; i < n; ++i) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int root = 1;
        depth[root] = 1;
        dfs(root, root);

        int q; cin >> q; while (q--) {
            char op;
            cin >> op;
            if (op == '!') {
                cin >> root;
            } else {
                int u, v; cin >> u >> v;
                cout << (LCA(u, v) ^ LCA(u, root) ^ LCA(v, root)) << '\n';
            }
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#define name "hbtlca"
    if (fopen(name".inp", "r"))
        freopen(name".inp", "r", stdin),
        freopen(name".out", "w", stdout);

    // int t; cin >> t; while (t--)
    Tinhnopro();

    cerr << "\nRuntime: " << 1.0 * clock() / CLOCKS_PER_SEC << ".s \n";
    return 0;
}
