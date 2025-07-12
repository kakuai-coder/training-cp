/*
    Author : kmv a.k.a kzhi
    K41 IT CHV
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long
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

int n;

int fb[75];

string bit(int s){
    string res = "";

    for (int i = 73; i >= 1; i --){
        if (fb[i] > s && res.size() == 0)
            continue;
        if (fb[i] > s)
            res = res + '0';
        else{
            s -= fb[i];
            res = res + '1';
        }
    }

    return res;
}

int dp[75][2][2][75];
string S;

int sol(int i, bool ok, int last, int cnt){
    if (i == S.size())
        return cnt;

    if (~dp[i][ok][last][cnt])
        return dp[i][ok][last][cnt];

    int cur = 0;

    int lim = 1;
    if (!ok)
        lim = S[i] - '0';

    FOR (j, 0, lim){
        if (j == last && j == 1)
            continue;
        bool nok = ok | (j < lim);
        int ncnt = cnt;
        if (cnt == 0 && j == 0)
            ncnt = cnt;
        else
            ncnt = cnt + 1;

        cur += sol(i + 1, nok, j, ncnt);
    }

    return dp[i][ok][last][cnt] = cur;
}

int calc(int x){
    S = bit(x);

    memset(dp, -1, sizeof(dp));

    return sol(0, 0, 0, 0);
}

int f[75][2][2][75];

int cal(int i, int ok, int last, int cnt){
    if (i == S.size())
        return cnt;

    if (~f[i][ok][last][cnt])
        return f[i][ok][last][cnt];

    int cur = 0;

    int lim = 1;
    if (!ok)
        lim = S[i] - '0';

    FOR (j, 0, lim){
        if (j == last && j == 1)
            continue;
        int nok = ok | (j < lim);
        int ncnt = cnt;
        if (j == 1)
            ncnt ++;

        cur += cal(i + 1, nok, j, ncnt);
    }

    return f[i][ok][last][cnt] = cur;
}

void SOLVE(){
    cin >> n;

    fb[1] = 1;
    fb[2] = 2;
    FOR (i, 3, 73){
        fb[i] = fb[i - 1] + fb[i - 2];
    }

    int l = 0, r = 1e15 + 1;

    while (l + 1 < r){
        int mid = mid(l, r);
        if (calc(mid) <= n)
            l = mid;
        else
            r = mid;
    }

    S = bit(l);

    memset(f, -1, sizeof(f));

    int ans = cal(0, 0, 0, 0);

    int len = n - calc(l);

    string t = bit(l + 1);

    int dem = 0;

    for (int i = 0; i < len; i ++)
        if (t[i] == '1')
            dem ++;

    cout << dem + ans;
}

signed main(){
    Faster
    openfile("FINARY")

    int q = 1;

//    cin >> q;

    while (q --){
        SOLVE();
    }

    return 0;
}