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

const int N = 5e4 + 5;
const int Block = sqrt(N);

int n, tv, a[N];
int d1[N], d2[N];

ll res = 0;
ll ans[N];

struct Quest{
    int id, tp, r1, r2;
};

bool cmp(Quest A, Quest B){
    if (A.r1 / Block != B.r1 / Block)
        return A.r1 / Block < B.r1 / Block;
    return A.r2 < B.r2;
}

vector < Quest > v;

void Add1(int i){
    if (i == 0)
        return;
    d1[a[i]] ++;
    res += d2[a[i]];
}

void Rem1(int i){
    if (i == 0)
        return;
    d1[a[i]] --;
    res -= d2[a[i]];
}

void Add2(int i){
    if (i == 0)
        return;
    d2[a[i]] ++;
    res += d1[a[i]];
}

void Rem2(int i){
    if (i == 0)
        return;
    d2[a[i]] --;
    res -= d1[a[i]];
}

void SOLVE(){
    cin >> n;
    FOR (i, 1, n)
        cin >> a[i];

    cin >> tv;

    FOR (i, 1, tv){
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        v.pb({i, 1, r1, r2});
        v.pb({i, 1, l1 - 1, l2 - 1});
        v.pb({i, -1, r1, l2 - 1});
        v.pb({i, -1, l1 - 1, r2});
    }

    sort(all(v), cmp);

    FOR (i, 1, n){
        Add1(i);
        Add2(i);
    }

    int R1 = n, R2 = n;

    for (Quest i : v){
        int id = i.id;
        int tp = i.tp;
        int r1 = i.r1;
        int r2 = i.r2;

        while (r1 > R1)
            Add1(++ R1);
        while (r1 < R1)
            Rem1(R1 --);
        while (r2 > R2)
            Add2(++ R2);
        while (r2 < R2)
            Rem2(R2 --);

        ans[id] += 1ll * tp * res;
    }

    FOR (i, 1, tv)
        cout << ans[i] << endl;
}

signed main(){
    Faster
    openfile("B")

    int q = 1;

//    cin >> q;

    while (q --){
        SOLVE();
    }

    return 0;
}