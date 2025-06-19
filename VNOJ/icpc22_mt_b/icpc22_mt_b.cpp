// Author: tinhnopro (ngh)
#include<bits/stdc++.h>

using namespace std;

#define el '\n'
#define fi first
#define se second
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORE(i, a, b) for (int i = (a); i <= (int) (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (int) (b); --i)
#define all(v) (v).begin(), (v).end()

#define mask(x) (1LL << (x))
#define getbit(i, mask) ((mask >> i) & 1LL)
#define onbit(i, mask) (mask | MASK(i))
#define offbit(i, mask) mask & ~(MASK(i))
#define cntbit(x) __builtin_popcountll(x)

#define name "icpc22_mt_b"

using ll = long long;
using ld = long double;
using ii = pair<int, int>;
using vi = vector<int>;

template<class X, class Y> bool maximize(X &a, Y b) { return a < b ? a = b, 1 : 0; }
template<class X, class Y> bool minimize(X &a, Y b) { return a > b ? a = b, 1 : 0; }

const int MAXN = 1e5 + 11; 
const int MOD = 1e9 + 7; 
// const int INF = 1e9 + 11; 
// const ll INFF = (ll) 1e18 + 11;
// const int LOG = 22;
const int BASE = 311;

string s;
int q, n; 
ll d[MAXN];

struct Hash {
    ll h[MAXN], Pow[MAXN];

    void init(string &s) {
        s = " " + s; 
        Pow[0] = 1;
        h[0] = 0;
        FORE(i, 1, n) {
            Pow[i] = Pow[i - 1] * BASE % MOD;
            h[i] = (h[i - 1] * BASE % MOD + (s[i] - 'A' + 1)) % MOD;
        }
    }

    ll getHash(int l, int r) {
        return (h[r] - h[l - 1] * Pow[r - l + 1] % MOD + 2 * MOD) % MOD;
    }
} ngh;

int getLen(int pos) {
    int l = 1, r = n, res = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (ngh.getHash(pos, pos + mid - 1) == ngh.getHash(1, mid)) {
            res = mid;
            l = mid + 1;
        } else r = mid - 1;
    }
    return res;
}

int32_t main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);

    if (fopen(name".inp", "r")) {
        freopen(name".inp", "r", stdin);
        freopen(name".out", "w", stdout);
    }
    //___________________________________
    cin >> s >> q;
    n = s.size();
    ngh.init(s);
    FORE(i, 1, n) {
        int l = getLen(i);
        if (l == -1) continue;
        d[1]++;
        d[l + 1]--;
    }

    FORE(i, 1, n) d[i] += d[i - 1];

    while (q--) {
        int l; cin >> l;
        if (ngh.getHash(1, l) != ngh.getHash(n - l + 1, n)) {
            cout << "NO\n";
            continue;
        } 
        if (d[l] < 3) {
            cout << "NO\n";
        } else cout << "YES " << d[l] << el; 
    }

    return 0;
}
