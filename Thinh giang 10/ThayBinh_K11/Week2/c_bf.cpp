/*
    Author : kmv a.k.a kzhi
    K41 IT CHV
*/
#include <bits/stdc++.h>
using namespace std;


#define int long long
#define FOR(i,a,b) for (int i = a ; i <= b; ++ i)
#define FOD(i,a,b) for (int i = a; i >= b; -- i)


#define BIT(mask,i)       ((mask >> i) & 1)
#define MASK(i)                (1ll << (i))
#define OFFBIT(mask,i)  (mask &~(1ll<<(i)))
#define ONBIT(mask,i) (mask | (1ll << (i)))
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

const int N = 2e5 + 5;

int n, k;
ii a[N];
int w[N];
vector < ii > E[N];

namespace SUB1{
    int d[25][25];

    void bfs(int s){
        FOR (i, 1, n)
            d[s][i] = -1;
        d[s][s] = 0;

        queue < int > qu;
        qu.push(s);

        while (qu.size()){
            int u = qu.front();
            qu.pop();

            for (ii i : E[u]){
                if (d[s][i.fi] != -1)
                    continue;
                d[s][i.fi] = d[s][u] + i.se;
                qu.push(i.fi);
            }
        }
    }

    int cal(int mask){
        vi num;
        num.clear();

        FOR (i, 1, n)
            if (BIT(mask, i - 1))
                num.pb(i);

        int res = 0;

        FOR (i, 1, n){
            int r = 1e9;
            for (int j : num)
                minimize(r, d[i][j]);
            maximize(res, r);
        }

        return res;
    }

    void SOLVE(){
        FOR (i, 1, n)
            bfs(i);

        int ans = 1e18;

        FOR (i, 0, MASK(n) - 1)
            if (c_bit(i) == k)
                minimize(ans, cal(i));

        cout << ans;
    }
}

void SOLVE(){
    cin >> n >> k;
    FOR (i, 1, n - 1){
        cin >> a[i].fi >> a[i].se >> w[i];
        E[a[i].fi].pb({a[i].se, w[i]});
        E[a[i].se].pb({a[i].fi, w[i]});
    }

    if (n <= 20){
        SUB1 :: SOLVE();
        return;
    }
}

signed main(){
    Faster
    openfile("c")

    int q = 1;

//    cin >> q;

    while (q --){
        SOLVE();
    }

    return 0;
}