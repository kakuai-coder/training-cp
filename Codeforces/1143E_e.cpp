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
        {freopen(TASK".inp","r",stdin);freopen(TASK".out","w",stdout);}
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

const int N = 1e6 + 5;
const int LOG = lg2(N);

int n, m, tv;

int a[N], b[N];

int f[N];

int lst[LOG + 1][N];

int pos[N];

int res[LOG + 1][N];

int nxt(int i){
    if (i == m)
        return 1;
    return i + 1;
}

int get(int l, int r){
    int lk = lg2(r - l + 1);

    return min(res[lk][l], res[lk][r - MASK(lk) + 1]);
}

void SOLVE(){
    cin >> m >> n >> tv;
    FOR (j, 1, m){
        cin >> b[j];
        pos[b[j]] = j;
    }
    
    FOR (i, 1, n)
        cin >> a[i];


    FOR (i, 1, m)
        f[i] = n + 1;

    FOR (i, 0, lg2(m))
        lst[i][n + 1] = n + 1;

    FOD (i, n, 1){
        int p = pos[a[i]];

        lst[0][i] = f[b[nxt(p)]];

        f[a[i]] = i;
    }

    for (int j = 1; j <= lg2(m); j ++)
        for (int i = 1; i <= n; i ++){
            lst[j][i] = lst[j - 1][lst[j - 1][i]];
        }

    for (int i = 1; i <= n; i ++){
        int k = m;
        int p = i;

        res[0][i] = n + 1;

        for (int j = lg2(m); j >= 0; j --){
            if (k > MASK(j)){
                k -= MASK(j);
                p = lst[j][p];
            }
        }

        res[0][i] = p;

    }

    FOR (j, 1, lg2(n))
        for (int i = 1; i + MASK(j) - 1 <= n; i ++)
            res[j][i] = min(res[j - 1][i], res[j - 1][i + MASK(j - 1)]);

    while (tv --){
        int l, r;
        cin >> l >> r;

        if (r - l + 1 < m){
            cout << "0";
            continue;
        }

        int p = get(l, r - m + 1);

        if (p <= r)
            cout << "1";
        else
            cout << "0";
    }
}

signed main(){
    Faster
    openfile("MATCH")

    int q = 1;

//    cin >> q;

    while (q --){
        SOLVE();
    }

    return 0;
}