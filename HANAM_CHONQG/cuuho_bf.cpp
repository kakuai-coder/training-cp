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

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;
const int Block = sqrt(N) + 5;

int n, x[N], d[N];
ll dp[N];
ll t[Block][N];

ll sum(int bl, int l, int r){
    if (r + bl > n)
        return t[bl][l];
    return (t[bl][l] - t[bl][r + bl] + 1ll * MOD * MOD) % MOD;
}

void SOLVE(){
    cin >> n;
    FOR (i, 1, n)
        cin >> d[i] >> x[i];

    FOD (i, n, 1){
        dp[i] = 1;

        if (i + d[i] <= n && x[i] > 0 && d[i] > 0){
            if (1ll * d[i] * d[i] > n)
                for (int j = 1; j <= x[i] && i + j * d[i] <= n; j ++)
                    dp[i] = (dp[i] + dp[i + j * d[i]]) % MOD;
            else{
                int m = min(x[i], (n - i) / d[i]);
                dp[i] = (dp[i] + sum(d[i], i + d[i], i + m * d[i])) % MOD;
            }
        }

        for (int j = 1; j * j <= n; j ++){
            if (i + j > n)
                t[j][i] = dp[i];
            else
                t[j][i] = (t[j][i + j] + dp[i]) % MOD;
        }
    }

    cout << dp[1];
}

signed main(){
    Faster
    openfile("CUUHO")

    int q = 1;

//    cin >> q;

    while (q --){
        SOLVE();
    }

    return 0;
}
