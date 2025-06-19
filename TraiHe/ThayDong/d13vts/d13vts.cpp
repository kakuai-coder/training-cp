#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> chains;
int res = 0;

void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v])
            dfs(v, adj, visited);
}

bool isConnected(const vector<string>& selected) {
    vector<vector<int>> adj(7); 
    vector<int> deg(7, 0);

    for (auto& s : selected) {
        int u = s[0] - '0';
        int v = s.back() - '0';
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    int start = -1;
    for (int i = 0; i < 7; ++i)
        if (deg[i]) {
            start = i;
            break;
        }

    if (start == -1) return false; 

    vector<bool> visited(7, false);
    dfs(start, adj, visited);

    for (int i = 0; i < 7; ++i)
        if (deg[i] && !visited[i])
            return false;

    for (int i = 0; i < 7; ++i)
        if (deg[i] % 2 != 0)
            return false;

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

		
    cin >> n;
    chains.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> chains[i];

    for (int mask = 0; mask < (1 << n); ++mask) {
        vector<string> subset;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
                subset.push_back(chains[i]);

        if (subset.size() >= 3 && isConnected(subset))
            res = max(res, (int)subset.size());
    }

    cout << res << '\n';
    return 0;
}
