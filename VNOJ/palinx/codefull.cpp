#include <bits/stdc++.h>
#define task "palinx"
#define ll long long
#define double long double
#define ii pair<int,int>
#define fi first
#define se second
#define c_bit(i)       __builtin_popcountll(i)
#define Bit(mask,i)    ((mask >> i) & 1)
#define onbit(mask,i)  ((mask) | (1LL << i))
#define offbit(mask,i) ((mask) &~ (1LL << i))
using namespace std;
const int maxn = 1e6 + 5;
const ll oo = 1e18;
const int mod = 1e9 + 7;
const int base = 311;
const int dx[] = {0,1,0,-1} , dy[] = {1,0,-1,0};
int n, len[maxn]; string s[maxn]; ll Pow[maxn]; vector<ll> Hash[maxn], rHash[maxn];
unordered_map<ll, int> mark;
ll get(int i, int l, int r)
{
    return Hash[i][r] - Hash[i][l - 1] * Pow[r - l + 1];
}
ll getRev(int i, int l, int r)
{
    return rHash[i][len[i] - l + 1] - rHash[i][len[i] - r] * Pow[r - l + 1];
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    if(fopen(task".inp","r")){
       freopen(task".inp","r",stdin);
       freopen(task".out","w",stdout);
    }
    cin >> n;
    for(int i = 1;i <= n;i ++) cin >> len[i] >> s[i];
    Pow[0] = 1;
    for(int i = 1;i <= 1e6;i ++) Pow[i] = Pow[i - 1] * base;
    for(int i = 1;i <= n;i ++){
        s[i] = ' ' + s[i];
        Hash[i].assign(len[i] + 1, 0);
        rHash[i].assign(len[i] + 1, 0);
        for(int j = 1;j <= len[i];j ++){
            Hash[i][j] = Hash[i][j - 1] * base + s[i][j] - 'a' + 1;
            rHash[i][j] = rHash[i][j - 1] * base + s[i][len[i] - j + 1] - 'a' + 1;
        }
        mark[Hash[i][len[i]]] ++;
    }
    ll res = 0;
    for(int i = 1;i <= n;i ++){
        for(int j = 2;j <= len[i];j ++){
            if(get(i, j, len[i]) != getRev(i, j, len[i])) continue;
            res += mark[getRev(i, 1, j - 1)];
        }
        for(int j = 1;j < len[i];j ++){
            if(get(i, 1, j) != getRev(i, 1, j)) continue;
            res += mark[getRev(i, j + 1, len[i])];
        }
        res += mark[getRev(i, 1, len[i])];
    }
    cout << res;
    return 0;
}
