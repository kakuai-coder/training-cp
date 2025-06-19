#include <bits/stdc++.h>
using namespace std;
static const int MOD = 1000000007;

// giờ là void, và không còn UB nữa
inline void add(int &a, int b) {
    int t = a + b;
    if (t >= MOD) t -= MOD;
    a = t;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, p;
    cin >> n >> m >> p;
    vector<int> special(p);
    for(int i = 0; i < p; i++)
        cin >> special[i];

    vector<vector<int>> adj(n+1);
    vector<int> indegree(n+1, 0);
    for(int i = 0, u, v; i < m; i++){
        cin >> u >> v;
        adj[u].push_back(v);
        indegree[v]++;
    }

    // 1) Topo sort
    vector<int> topo;
    topo.reserve(n);
    queue<int> q;
    for(int v = 1; v <= n; v++)
        if(indegree[v] == 0) q.push(v);
    while(!q.empty()){
        int u = q.front(); q.pop();
        topo.push_back(u);
        for(int w: adj[u])
            if(--indegree[w] == 0)
                q.push(w);
    }

    // 2) idx[v] = vị trí của v trong topo
    vector<int> idx(n+1);
    for(int i = 0; i < n; i++)
        idx[topo[i]] = i;

    // 3) T = {1} + special + {n}
    vector<int> T;
    T.reserve(p+2);
    T.push_back(1);
    for(int x: special)
        if(x != 1) T.push_back(x);
    if(T.back() != n) T.push_back(n);

    // 4) DP trên từng đoạn
    vector<int> dp(n+1, 0);
    long long ans = 1;

    for(int i = 1; i < (int)T.size(); i++){
        int u = T[i-1], v = T[i];
        if(idx[u] > idx[v]){
            cout << 0 << "\n";
            return 0;
        }
        dp[u] = 1;
        for(int t = idx[u]; t <= idx[v]; t++){
            int x = topo[t];
            if(dp[x] == 0) continue;
            for(int w: adj[x]){
                if(idx[w] <= idx[v])
                    add(dp[w], dp[x]);
            }
        }
        int ways = dp[v];
        ans = ans * ways % MOD;
        // reset dp để dùng cho đoạn sau
        for(int t = idx[u]; t <= idx[v]; t++)
            dp[topo[t]] = 0;

        if(ways == 0){
            cout << 0 << "\n";
            return 0;
        }
    }

    cout << ans << "\n";
    return 0;
}