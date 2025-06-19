/*
    Author : kmv a.k.a kzhi
    K41 IT CHV
*/
#include <bits/stdc++.h>
using namespace std;


#define ll long long
#define FOR(i,a,b) for (int i = a ; i <= b; ++ i)
#define FOD(i,a,b) for (int i = a; i >= b; -- i)


#define BIT(mask,i)       ((mask >> i) & 1)
#define MASK(i)                (1ll << (i))
#define OFFBIT(mask,i)  (mask &~(1ll<<(i)))
#define ONBIT(mask,i) (mask  (1ll << (i)))
#define lg2(x)    (63 - __builtin_clzll(x))
#define c_bit          __builtin_popcountll

#define vi vector < int >
#define all(a) a.begin(), a.end()
#define pb push_back

#define ii pair<int,int>
#define fi first
#define se second

#define openfile(TASK) if (fopen(TASK".inp","r"))\
        {freopen(TASK".inp","r",stdin);freopen(TASK".ans","w",stdout);}
#define endl '\n'
#define Faster ios_base::sync_with_stdio(false); \
                        cin.tie(0);  cout.tie(0);
#define TIME (1.0 * clock() / CLOCKS_PER_SEC)

#define mid(l,r) ((l + r) >> 1)
#define left(id) (id << 1)
#define right(id) ((id << 1) | 1)
#define ci const int

template <class X, class Y> bool maximize(X &a, const Y &b){if(a < b) return a = b, true;return false;}
template <class X, class Y> bool minimize(X &a, const Y &b){if(a > b) return a = b, true;return false;}

const int N = 1e5 + 5;

int n, a[N];

vector <int> u[N];

int f[N];

void ssnt(int n){
    for (int i = n; i >= 1; i --){
        for (int j = 1; j * i <= n; j ++)
            u[i * j].pb(i);
    }
}

struct DATA{
    int u, v, w;
};

bool cmp(DATA A, DATA B){
    return A.w > B.w;
}

vector < DATA > v;

struct DSU{
    int par[N], Max[N], Min[N];

    void init(int n){
        for (int i = 1; i <= n; i ++){
            par[i] = -1;
            Max[i] = Min[i] = i;
        }
    }

    int F(int x){
        if (par[x] < 0)
            return x;
        return par[x] = F(par[x]);
    }

    void Merge(int u, int v){
        u = F(u);
        v = F(v);
        if (u == v)
            return;
        if (par[u] > par[v])
            swap(u, v);
        par[u] += par[v];
        par[v] = u;
        maximize(Max[u], Max[v]);
        minimize(Min[u], Min[v]);
    }

    int last(int u){
        return Max[F(u)];
    }

    int fst(int u){
        return Min[F(u)];
    }
} dsu;

void SOLVE(){
    ssnt(1e5);

    cin >> n;
    FOR (i, 1, n){
        cin >> a[i];
    }

    FOR (i, 1, n){
        for (int j : u[a[i]])
            if (f[j] > 0)
                v.pb({i, f[j], j});

        for (int j : u[a[i]])
            if (f[j] == 0)
                f[j] = i;
    }

    sort(all(v), cmp);

    ll cost = 0;

    dsu.init(n);

    for (DATA i : v){
        if (dsu.F(i.u) != dsu.F(i.v)){
            cost += i.w;
            dsu.Merge(i.u, i.v);
        }
    }



    cout << 123456ll * (n - 1) - cost;
}

signed main(){
    Faster
    openfile("gstree")

    int q = 1;

//    cin >> q;

    while (q --){
        SOLVE();
    }

    return 0;
}
