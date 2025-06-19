/*
    Author: tinhnopro
    created: 2025.06.15 15:19:40
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 10
#endif // LOCAL

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
    template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 1e6 + 5;

int n, m; 
vector<pair<int, int> > adj[maxN];
int deg[maxN], used[maxN];
int id = 0; 

void dfs(int u, vector<int>& path) {
    while (!adj[u].empty()) {
        
        pair<int, int> x = adj[u].back();
        int v = x.first, id = x.second;
        adj[u].pop_back();
        if (used[id]) continue;
        used[id] = true;
        dfs(v, path);
    }
    path.push_back(u);
}

void tinhnop() {
    cin >> n >> m; 
    int d = n + 1; 
    for (int i = 1; i <= m; ++i) {
        int u, v; 
        cin >> u >> v; 
        adj[u].push_back({v, id}); 
        adj[v].push_back({u, id});
        deg[u]++;
        deg[v]++; 
        id++; 
    }

    vector<int> odd; 

    for (int i = 1; i <= n; ++i) if (deg[i] % 2 == 1) {
        adj[i].push_back({n + 1, id}); 
        adj[n + 1].push_back({i, id});
        id++;
        odd.push_back(i); 
    }

    vector<int> path;

    if (odd.empty()) {
        cout << 0;
        return ;
    }
    
    dfs(odd[0], path);

    debug(path);

    while (path.size() && path.back() != n + 1) path.pop_back(); 
    if (path.empty()) {
        cout << 0;
        return ;
    }
    path.pop_back();
    
    if (path.empty()) {
        cout << 0;
        return ;
    }

    debug(path);

    vector<vector<int>> cur_path;
    vector<int> cur; 

    while (path.size()) {
        if (path.back() == n + 1) {
            debug(cur_path);
            cur_path.push_back(cur); 
            cur.clear();
            path.pop_back();
            continue;
        }
        cur.push_back(path.back());
        path.pop_back();
    }

    cur_path.push_back(cur);

    cout << cur_path.size() << '\n'; 

    for (auto &x : cur_path) {
        reverse(x.begin(), x.end());
        cout << x.size();
        for (int d : x) cout << " " << d;
        cout << '\n'; 
    }
}

//_____________________________________________________________________________________________
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    #define cherry "drgame"
    if (fopen(cherry".inp", "r")) {
        freopen(cherry".inp", "r", stdin);
        freopen(cherry".out", "w", stdout);
    }

    // int Ntest; cin >> Ntest; while (Ntest--)
    tinhnop();

    cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
    return 0;
}