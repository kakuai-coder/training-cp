// Author: tinhnopro (ngh)
#include<bits/stdc++.h>

using namespace std;

#define el '\n'
#define fi first
#define se second
#define REP(i, a, b) for (int i = (a); i < (b); ++i)
#define FOR(i, a, b) for (int i = (a); i <= (int) (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (int) (b); --i)
#define all(v) (v).begin(), (v).end()

#define mask(x) (1LL << (x))
#define getbit(i, mask) ((mask >> i) & 1LL)
#define onbit(i, mask) (mask | MASK(i))
#define offbit(i, mask) mask & ~(MASK(i))
#define cntbit(x) __builtin_popcountll(x)

#define name "kquery2"

using ll = long long;
using ld = long double;
using ii = pair<int, int>;
using vi = vector<int>;

template<class X, class Y> bool maximize(X &a, Y b) { return a < b ? a = b, 1 : 0; }
template<class X, class Y> bool minimize(X &a, Y b) { return a > b ? a = b, 1 : 0; }

const int MAXN = 3e4 + 11; 
// const int MOD = 1e9 + 7; 
// const int INF = 1e9 + 11; 
// const ll INFF = (ll) 1e18 + 11;
// const int LOG = 22;
// const int BASE = 311;
const int BLOCK = 330;

int n, q, a[MAXN];
vector<int> s[MAXN / BLOCK + 2];

#define getBlock(id) ((id) - 1) / BLOCK + 1
#define getLeft(id) ((id) - 1) * BLOCK + 1
#define getRight(id) (id) * BLOCK

void update(int pos, int val) {
    int blockID = getBlock(pos);
    int idx = lower_bound(all(s[blockID]), a[pos]) - s[blockID].begin();
    s[blockID][idx] = val;
    a[pos] = val;
    sort(all(s[blockID]));
}

int query(int l, int r, int val) {
    int blockL = getBlock(l);
    int blockR = getBlock(r);

    int ans = 0;

    if (blockL == blockR) {
        FOR(i, l, r) ans += a[i] > val;
        return ans;
    }

    FOR(i, l, getRight(blockL)) ans += a[i] > val;
    FOR(i, getLeft(blockR), r) ans += a[i] > val;
    
    FOR(id, blockL + 1, blockR - 1) {
        ans += s[id].size() - (upper_bound(all(s[id]), val) - s[id].begin());
    }

    return ans; 
}

int32_t main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);

    if (fopen(name".inp", "r")) {
        freopen(name".inp", "r", stdin);
        freopen(name".out", "w", stdout);
    }
    //___________________________________
    cin >> n;
    FOR(i, 1, n) {
        cin >> a[i];
        s[getBlock(i)].push_back(a[i]);
    }
    
    FOR(i, 1, getBlock(n)) {
        sort(all(s[i]));
    }
    cin >> q;
    while(q--) {
        int type; cin >> type;
        if (type == 0) {   
            int i, v; cin >> i >> v;
            update(i, v);
        } else {
            int i, j, k; cin >> i >> j >> k;
            cout << query(i, j, k) << el;
        }
    }

    return 0;
}
