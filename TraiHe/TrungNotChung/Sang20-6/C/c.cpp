#include <bits/stdc++.h>
#define vi vector <int>
using namespace std;
int n, m;

main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    freopen("617062C.inp","r",stdin);
    freopen("617062C.out","w",stdout);
    int test;
    cin >> test;
    while (test--) {
        cin >> n >> m;
        vector<vi> adj(n+1);
        vector<pair<int,int>> edges(m);
        for (int i = 0, u, v; i < m; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            edges[i] = {u,v};
        }

        vector<int> deg = vector<int>(n+1);
        queue<int> q;
        vector<bool> inCore(n+1,true);
        for(int i=1;i<=n;i++){
            deg[i] = adj[i].size();
            if(deg[i] < 2){
                q.push(i);
                inCore[i] = false;
            }
        }
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int v: adj[u]){
                if(!inCore[v]) continue;
                if(--deg[v] == 1){
                    inCore[v] = false;
                    q.push(v);
                }
            }
        }

        vector<vi> cadj(n+1);
        int nCore = 0, mCore = 0;
        for(auto &e: edges){
            int u=e.first, v=e.second;
            if(inCore[u] && inCore[v]){
                cadj[u].push_back(v);
                cadj[v].push_back(u);
                mCore++;
            }
        }
        for(int i=1;i<=n;i++) if(inCore[i]) nCore++;

        if(nCore==0){
            cout << -1 << "\n";
            continue;
        }
        int start=-1;
        for(int i=1;i<=n;i++) if(inCore[i]){ start=i; break; }
        vector<bool> vis(n+1,false);
        function<void(int)> dfs1 = [&](int u){
            vis[u]=true;
            for(int v: cadj[u])
                if(!vis[v]) dfs1(v);
        };
        dfs1(start);
        bool single = true;
        for(int i=1;i<=n;i++){
            if(inCore[i] && !vis[i]){
                single = false; break;
            }
        }
        if(!single){
            cout << -1 << "\n";
            continue;
        }

        int k = mCore - nCore + 1;
        if(k==1){
            int best = n+1;
            for(int i=1;i<=n;i++)
                if(inCore[i])
                    best = min(best, i);
            cout << best << "\n";
            continue;
        }

        vector<int> cand;
        for(int i=1;i<=n;i++){
            if(inCore[i] && (int)cadj[i].size() >= k+1)
                cand.push_back(i);
        }
        sort(cand.begin(), cand.end());

        auto hasCycle = [&](int ban)->bool{
            vector<int> color(n+1,0);
            function<bool(int,int)> dfs = [&](int u,int p){
                color[u]=1;
                for(int v: cadj[u]){
                    if(v==ban) continue;
                    if(v==p) continue;
                    if(color[v]==0){
                        if(dfs(v,u)) return true;
                    }
else if(color[v]==1){
                        return true;
                    }
                }
                color[u]=2;
                return false;
            };
            for(int i=1;i<=n;i++){
                if(!inCore[i] || i==ban) continue;
                if(color[i]==0){
                    if(dfs(i,-1)) return true;
                }
            }
            return false;
        };

        int ans = -1;
        for(int v: cand){
            if(!hasCycle(v)){
                ans = v;
                break;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}