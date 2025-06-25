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

const int N = 2e5 + 1;

int n, m;
set<int> s1[N * 4], s2[N * 4];
string a[N];
int dem = 0;
ii len[N];

void upd(ci &id, ci &l, ci &r, ci &u, ci &v, ci &val){
    if (v < l || r < u)
        return;

    if (u <= l && r <= v){
        s1[id].insert(val);
        return;
    }

    s2[id].insert(val);

    int mid = mid(l, r);
    upd(left(id), l, mid, u, v, val);
    upd(right(id), mid + 1, r, u, v, val);
}

void upd2(ci &id, ci &l, ci &r, ci &u, ci &v, ci &val){
    if (v < l || r < u)
        return;

    if (u <= l && r <= v){
        s1[id].erase(val);
        return;
    }

    s2[id].erase(val);

    int mid = mid(l, r);
    upd2(left(id), l, mid, u, v, val);
    upd2(right(id), mid + 1, r, u, v, val);
}

int Get(ci &id, ci &l, ci &r, ci &u, ci &v){
    if (v < l || r < u)
        return -1;

    int res = -1;


    if (u <= l && r <= v){
        if (s2[id].size())
            maximize(res, *s2[id].rbegin());
        if (s1[id].size())
            maximize(res, *s1[id].rbegin());
        return max(res, -1);
    }

    if (s1[id].size())
        maximize(res, *s1[id].rbegin());

    int mid = mid(l, r);

    int res1 = Get(left(id), l, mid, u, v);
    int res2 = Get(right(id), mid + 1, r, u, v);

    res = max({res, res1, res2});

    return res;
}

void SOLVE(){
    cin >> n >> m;

    while (m --){
        int tp, l, r;
        cin >> tp;
        if (tp == 1){
            dem ++;
            cin >> a[dem];
            cin >> l >> r;
            len[dem] = {l, r};
            upd(1, 1, n, l, r, dem);
        }
        else{
            cin >> l >> r;
            int id = Get(1, 1, n, l, r);
            if (id == -1)
                cout << id << endl;
            else
            cout << a[id] << endl;
            if (id > 0)
                upd2(1, 1, n, len[id].fi, len[id].se, id);
        }
    }
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
