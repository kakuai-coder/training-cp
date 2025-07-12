/*
	Author: kakuai
	created: 2025.07.04 17:50:13
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

constexpr int MAXN = 300000 + 5;
constexpr int LOG   = 19;

int up[LOG][MAXN];
int depth[MAXN];
int head[MAXN];
int valArr[MAXN];

void kakuai() {
    int N;
    cin >> N;
    int nodeCnt = 0;

    depth[0] = 0;
    for (int k = 0; k < LOG; ++k) up[k][0] = 0;
    head[0] = 0;

    auto lca = [&](int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int k = 0; k < LOG; ++k) {
            if (diff & (1 << k)) u = up[k][u];
        }
        if (u == v) return u;
        for (int k = LOG - 1; k >= 0; --k) {
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        }
        return up[0][u];
    };

    for (int i = 1; i <= N; ++i) {
        char op;
        cin >> op;
        if (op == 'a') {
            int v;
            cin >> v;
            int prev = head[v];
            int cur  = ++nodeCnt;
            valArr[cur] = i;
            up[0][cur]  = prev;
            depth[cur]  = depth[prev] + 1;
            for (int k = 1; k < LOG; ++k) {
                up[k][cur] = up[k-1][ up[k-1][cur] ];
            }
            head[i] = cur;
        }
        else if (op == 'b') {
            int v;
            cin >> v;
            int topNode = head[v];
            cout << valArr[topNode] << '\n';
            head[i] = up[0][topNode];
        }
        else if (op == 'c') {
            int v, w;
            cin >> v >> w;
            head[i] = head[v];
            int u1 = head[i];
            int u2 = head[w];
            int z  = lca(u1, u2);
            cout << depth[z] << '\n';
        }
    }
}

//_____________________________________________________________________________________________
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    #define cherry "d"
    if (fopen(cherry".inp", "r")) {
        freopen(cherry".inp", "r", stdin);
        freopen(cherry".out", "w", stdout);
    }

    // int Ntest; cin >> Ntest; while (Ntest--)
    kakuai();

    cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
    return 0;
}
