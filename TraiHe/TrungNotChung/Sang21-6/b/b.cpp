#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100000;
int n, d;
int tp[MAXN+1], f[MAXN+1];
vector<int> g[MAXN+1];
int tour[2*MAXN+2], in[MAXN+1], out[MAXN+1], T;
int up[MAXN+1][17], depth[MAXN+1];

struct Query {
    int l, r, lca, idx;
    bool operator<(Query const& o) const {
        int b1 = l / block, b2 = o.l / block;
        if (b1 != b2) return b1 < b2;
        return (b1&1) ? r > o.r : r < o.r;
    }
    static int block;
};
int Query::block;

ll answer[MAXN+1];
bool vis[MAXN+1];
ll cnt[2][MAXN+1];
ll cur = 0;

void dfs(int u, int p){
    in[u] = T; tour[T++] = u;
    up[u][0] = p;
    for(int i=1;i<17;i++) up[u][i] = up[ up[u][i-1] ][i-1];
    for(int v:g[u]) if(v!=p){
        depth[v]=depth[u]+1;
        dfs(v,u);
    }
    out[u] = T; tour[T++] = u;
}

int lca(int u,int v){
    if(depth[u]<depth[v]) swap(u,v);
    int diff = depth[u]-depth[v];
    for(int i=0;i<17;i++) if(diff>>i&1) u=up[u][i];
    if(u==v) return u;
    for(int i=16;i>=0;i--){
        if(up[u][i]!=up[v][i]){
            u=up[u][i];
            v=up[v][i];
        }
    }
    return up[u][0];
}

void toggle(int u){
    int t = tp[u];
    int x = f[u];
    if(vis[u]){
        vis[u]=false;
        if(t==0) cur -= cnt[1][x];
        else      cur -= cnt[0][x];
        cnt[t][x]--;
    } else {
        if(t==0) cur += cnt[1][x];
        else      cur += cnt[0][x];
        cnt[t][x]++;
        vis[u]=true;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    vector<int> vals;
    for(int i=1;i<=n;i++) cin>>tp[i];
    for(int i=1;i<=n;i++){
        cin>>f[i];
        vals.push_back(f[i]);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for(int i=1;i<=n;i++){
        f[i] = lower_bound(vals.begin(), vals.end(), f[i]) - vals.begin();
    }
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    T=0;
    depth[1]=0;
    dfs(1,1);

    cin>>d;
    vector<Query> qs(d);
    Query::block = max(1,(int)(sqrt(T)));
    for(int i=0,u,v;i<d;i++){
        cin>>u>>v;
        int w = lca(u,v);
        if(in[u] > in[v]) swap(u,v);
        if(w==u){
            qs[i] = { in[u], in[v], 0, i };
        } else {
            qs[i] = { out[u], in[v], w, i };
        }
    }
    sort(qs.begin(), qs.end());

    int L=0, R=-1;
    for(auto &q: qs){
        while(L > q.l) toggle(tour[--L]);
        while(R < q.r) toggle(tour[++R]);
        while(L < q.l) toggle(tour[L++]);
        while(R > q.r) toggle(tour[R--]);
        if(q.lca){
            toggle(q.lca);
        }
        answer[q.idx] = cur;
        if(q.lca){
            toggle(q.lca);
        }
    }

    for(int i=0;i<d;i++){
        cout<<answer[i]<<"\n";
    }
    return 0;
}
