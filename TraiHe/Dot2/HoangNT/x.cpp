///*** Sown_Vipro ***///
/// ->TEAM SELECTION TEST<- ///

#include<bits/stdc++.h>
using namespace std;
//#pragma GCC optimize ("O3")
//#pragma GCC optimize ("unroll-loops")
//#pragma GCC target("popcnt")
#define F first
#define S second
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pair<int, int> >
#define FOR(i, a, b) for(int i = a; i <= b; ++i)
#define REP(i, a, b) for(int i = a; i >= b; --i)
#define all(s) s.begin(), s.end()
#define szz(s) int(s.size())
const string NAME = "sown";
const int N = 1e6 + 5, MAX = 5, oo = 1e9 + 5, MOD = 1e9 + 7;
void maxi(int &x, int y){ if(x < y) x = y; }
void mini(int &x, int y){ if(x > y) x = y; };
void add(int &x, int y){ x += y; x += MOD * (x < 0); x -= MOD * (x >= MOD); };
int n;
int a[N], p[20][N], L[N], R[N], lg[N];

int g(int l, int r){
    if(l > r) return 0;
    int k = lg[r - l + 1];
//    cout << "TEST:" << l << " " << r << " " << k << " " << << "\n";
    return max(p[k][l], p[k][r - (1 << k) + 1]);
}

int f(int l, int r, int d){
    int i = r;
    while(l <= r){
        int mid = (l + r) / 2;
//        cout << mid << " " << g(mid, i) << "\n";
        if(g(mid, i) < d){
            r = mid - 1;
        }
        else l = mid + 1;
    }
//    cout << l << " " << r << "\n";
    return l;
}

int e(int l, int r, int d){
    int i = l;
    while(l <= r){
        int mid = (l + r) / 2;
//        cout << mid << " " << g(i, mid) << "\n";
        if(g(i, mid) < d) l = mid + 1;
        else r = mid - 1;
    }
    return r;
}

void solve(){
    cin >> n;

    FOR(i, 1, n){
        lg[i] = 31 - __builtin_clz(i);
//        cout << lg[i] << "\n";
    }

    int mx = 0;
    FOR(i, 1, n){
        cin >> a[i];
        p[0][i] = a[i];
        mx = max(mx, a[i]);
    }

    FOR(k, 1, 18){
        FOR(i, 1, n){
            p[k][i] = max(p[k - 1][i], p[k - 1][i + (1 << k - 1)]);
        }
    }

    stack<int> st;
    st.push(0);
    FOR(i, 1, n){
        while(a[st.top()] >= a[i]){
            st.pop();
        }
        L[i] = st.top() + 1;
        st.push(i);
//        FOR(d, 1, MAX / a[i]){
//
//        }
    }

    while(st.size()) st.pop();
    st.push(n + 1);

    REP(i, n, 1){
        while(a[st.top()] >= a[i]){
            st.pop();
        }
        R[i] = st.top() - 1;
        st.push(i);

//        cout << L[i] << " " << R[i] << "\n";
    }
//    cout << e(2, 3, 4) << "\n";
    long long res = 0;
    FOR(i, 1, n){
        FOR(d, 1, mx / a[i]){
            int l1 = f(L[i], i, a[i] * (d + 1));
            int l2 = f(L[i], i, a[i] * d) - 1;
//
            int r1 = e(i, R[i], a[i] * d) + 1;
            int r2 = e(i, R[i], a[i] * (d + 1));
            res += 1ll * (l2 - l1 + 1) * (r2 - i + 1) * d;
            res += 1ll * (i - l2) * (r2 - r1 + 1) * d;
//            if((l2 - l1 + 1) && (r2 - r1 + 1)) res -= (r2 - r1 + 1) * d;
//            cout << i << " " << d << " " << (l2 - l1 + 1) * (r2 - i + 1) + (i - l2 + 1) * (r2 - r1 + 1) << "\n";
           cout << l1 << " " << l2 << " " << r1 << " " << r2 << "\n";
        }
    }
    cout << res;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    if(fopen((NAME + ".inp").c_str(), "r")){
        freopen((NAME + ".inp").c_str(), "r", stdin);
        freopen((NAME + ".out").c_str(), "w", stdout);
    }
    int t = 1;
//    cin >> t;
    while(t--){
        solve();
    }
}