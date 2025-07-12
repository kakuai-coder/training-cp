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

ll p2[70];
ll p3[70];

int dp[10005][62][40];

//map < ll, int > mp[62][40];

int sol(int i, int m2, int m3){
    if (~dp[i][m2 + 1][m3 + 1])
        return dp[i][m2 + 1][m3 + 1];
    int cur = 0;

    for (int j2 = 0; j2 < m2 && p2[j2] <= i / p3[m3 + 1]; j2 ++){
        for (int j3 = m3 + 1; j3 <= 37 && p3[j3] <= i / p2[j2]; j3 ++){
            int p = p2[j2] * p3[j3];
            if (p <= i){
                maximize(cur, sol(i - p, j2, j3) + 1);
            }
        }
    }

    return dp[i][m2 + 1][m3 + 1] = cur;
}

int cal(ll i, int m2, int m3){
    if (i <= 10000)
        return sol(i, m2, m3);

//    if (mp[m2][m3].count(i))
//        return mp[m2][m3][i];

    int cur = 0;

    for (int j2 = 0; j2 < m2 && p2[j2] <= i / p3[m3 + 1]; j2 ++){
        ll p = 1ll * p2[j2] * p3[m3 + 1];
        maximize(cur, cal(i - p, j2, m3 + 1) + 1);
    }

//    mp[m2][m3][i] = cur;
    return cur;
}

void SOLVE(){
    ll n;
    cin >> n;
//    FOR (i, 0, 61)
//        FOR (j, 0, 38)
//            mp[i][j].clear();
    cout << cal(n, 60, -1) << endl;
}

signed main(){
    Faster
    openfile("POW23")

    int q = 1;

    p2[0] = p3[0] = 1;

    for (int i = 1; i <= 60; i ++){
        p2[i] = p2[i - 1] * 2;
    }

    for (int i = 1; i <= 38; i ++){
        p3[i] = p3[i - 1] * 3;
    }

    memset(dp, -1, sizeof(dp));

    cin >> q;

    while (q --){
        SOLVE();
    }

    return 0;
}