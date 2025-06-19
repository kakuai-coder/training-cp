#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
const int inf = 1e7 + 1;

array<int, 2> operator + (array<int, 2> a, array<int, 2> b){
    array<int, 2> c;
    c[0] = max(a[0], b[0]);
    c[1] = min(a[1], b[1]);
    return c;
}

struct SegmentTree{
    array<int, 2> st[N << 2];
    bool lzy[N << 2];

    void flip(int id){
        swap(st[id][0], st[id][1]);
        st[id][0] = -st[id][0];
        st[id][1] = -st[id][1];

        lzy[id] ^= 1;
    }

    void push(int id){
        if(lzy[id]){
            flip(id << 1);
            flip(id << 1 | 1);

            lzy[id] = 0;
        }
    }

    void reset(int n){
        n <<= 2;
        for(int i = 1; i <= n; ++i)
            st[i][0] = st[i][1] = lzy[i] = 0;
    }

    void Negate(int id, int l, int r, int u, int v){
        if(v < l or u > r) return;
        if(u <= l and r <= v) flip(id);
        else{
            push(id);
            int m = l + r >> 1;
            Negate(id << 1, l, m, u, v);
            Negate(id << 1 | 1, m + 1, r, u, v);

            st[id] = st[id << 1] + st[id << 1 | 1];
        }
    }

    void Upd(int id, int l, int r, int kth, int val){
        if(l == r) st[id][0] = st[id][1] = val, lzy[id] = 0;
        else{
            push(id);
            int m = l + r >> 1;
            if(kth <= m) Upd(id << 1, l, m, kth, val);
            else Upd(id << 1 | 1, m + 1, r, kth, val);

            st[id] = st[id << 1] + st[id << 1 | 1];
        }
    }

    int _qry(int id, int l, int r, int u, int v){
        if(v < l or u > r) return -inf;
        if(u <= l and r <= v) return st[id][0];

        int m = l + r >> 1;
        push(id);
        return max(_qry(id << 1, l, m, u, v), _qry(id << 1 | 1, m + 1, r, u, v));
    }

    int qry(int id, int l, int r, int u, int v){
        if(u > v) return -inf;
        return _qry(id, l, r, u, v);
    }
} segtree;

int n, sz[N], h[N], par[N], heavy[N], id_node[N], id_path[N], head[N], w[N], id_edge[N], timer, cur_id;
vector<pair<int, int>> g[N];
vector<int> chain[N];

int dfs_sz(int u, int e){
    sz[u] = 1;
    for(auto [v,i] : g[u]) if(v != e){
        h[v] = h[u] + 1;
        par[v] = u;
        sz[u] += dfs_sz(v, u);

        if(sz[heavy[u]] < sz[v]) heavy[u] = v;
    }

    return sz[u];
}

void dfs_hld(int u, int cur_head){
    id_node[u] = ++timer;
    head[u] = cur_head;

    if(!heavy[u]) return;

    for(auto [v, i] : g[u]) if(v == heavy[u]){
        chain[cur_head].push_back((id_edge[i] = id_path[v] = ++cur_id));
        dfs_hld(v, cur_head);
        break;
    }

    for(auto [v, i] : g[u]) if(v != par[u] and v != heavy[u]){
        chain[v].push_back((id_edge[i] = id_path[v] = ++cur_id));
        dfs_hld(v, v);
    }
}

void path_negate(int a, int b){
    if(a == b) return;

    while(head[a] != head[b]){
        if(h[head[a]] < h[head[b]]) swap(a, b);

        segtree.Negate(1, 1, n - 1, id_path[head[a]], id_path[a]);

        a = par[head[a]];
    }

    if(h[a] > h[b]) swap(a, b);
    segtree.Negate(1, 1, n - 1, id_path[a] + 1, id_path[b]);
}

int path_query(int a, int b){
    if(a == b) return 0;

    int ans = -inf;
    while(head[a] != head[b]){
        if(h[head[a]] < h[head[b]]) swap(a, b);

        ans = max(ans, segtree.qry(1, 1, n - 1, id_path[head[a]], id_path[a]));

        a = par[head[a]];
    }

    if(h[a] > h[b]) swap(a, b);
    return max(ans, segtree.qry(1, 1, n - 1, id_path[a] + 1, id_path[b]));
}

void testcase(){
    cin >> n;
    for(int i = 1; i < n; ++i){
        int u, v; cin >> u >> v >> w[i];
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }

    dfs_sz(1, 1);
    dfs_hld(1, 1);

    for(int i = 1; i < n; ++i)
        segtree.Upd(1, 1, n - 1, id_edge[i], w[i]);

    string t;
    while(cin >> t){
        if(t[0] == 'D') break;
        if(t[0] == 'C'){
            int edge, new_w; cin >> edge >> new_w;
            segtree.Upd(1, 1, n - 1, id_edge[edge], new_w);
        }
        else if(t[0] == 'N') {
            int a, b; cin >> a >> b;
            path_negate(a, b);
        }
        else{
            int a, b; cin >> a >> b;
            cout << path_query(a, b) << "\n";
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL); cout.tie(NULL);
	if (fopen("qtreex.inp", "r")) {
		freopen("qtreex.inp", "r", stdin);
		freopen("qtreex.ans", "w", stdout);
	}
    int tc; cin >> tc;
    for(int i = 0; i < tc; ++i){
        testcase();
        timer = cur_id = 0;
        for(int i = 1; i <= n; ++i){
            chain[i].clear();
            g[i].clear();
            sz[i] = par[i] = heavy[i] = h[i] = id_node[i] = id_path[i] = id_edge[i] = head[i] = w[i] = 0;
        }
        segtree.reset(n);
    }

    return 0;
}

