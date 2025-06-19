/*
    Author : kmv a.k.a kzhi
    K41 IT CHV
*/
#include <bits/stdc++.h>
using namespace std;


//#define int long long
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

#define db double

template <class X, class Y> bool maximize(X &a, const Y &b){if(a < b) return a = b, true;return false;}
template <class X, class Y> bool minimize(X &a, const Y &b){if(a > b) return a = b, true;return false;}

const int N = 1e5 + 5;
const db pi = acos(-1.0);

struct Point{
    double x, y;

    Point(){}

    Point(double x, double y): x(x), y(y){}

    bool operator < (const Point &a) const{
        if(x != a.x) return x < a.x;
        return y < a.y;
    }

    Point operator - (const Point &a) const{
        return Point(x - a.x, y - a.y);
    }

    double det(const Point &a) const{
        return x * a.y - y * a.x;
    }

    double angle(){
        double angle = atan2(y, x);
        if(angle < -pi / 2) angle += 2 * pi;
        return angle;
    }
};

int n;
Point ps[N], qs[N];
double angle[N];

Point p1, p2;
int tb;

int convex_hull(){
    sort(ps + 1, ps + n + 1);
    int k = 1;

    for(int i = 1; i <= n; ++i){
        while(k > 1 && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) --k;
        qs[k ++] = ps[i];
    }

    for(int i = n - 1, t = k; i >= 1; --i){
        while(k > t && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) --k;
        qs[k ++] = ps[i];
    }

    return k - 1;
}

int getp(double a){
    return lower_bound(angle, angle + tb, a) - angle;
}

bool inter(){
    if(n <= 1) return false;

    int a = getp((p1 - p2).angle());
    int b = getp((p2 - p1).angle());
    if((p1 - p2).det(qs[a] - p2) * (p1 - p2).det(qs[b] - p2) <= 0) return true;
    return false;
}

void SOLVE(){
    cin >> n;
    FOR (i, 1, n)
        cin >> ps[i].x >> ps[i].y;

    tb = convex_hull();

    FOR (i, 1, tb)
        angle[i] = (qs[i + 1] - qs[i]).angle();

    while (cin >> p1.x >> p1.y >> p2.x >> p2.y){
        if (inter())
            cout << "BAD\n";
        else
            cout << "GOOD\n";
    }
}

signed main(){
    Faster
    openfile("HWAYS")

    int q = 1;

//    cin >> q;

    while (q --){
        SOLVE();
    }

    return 0;
}
