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

#define name "E"

using ll = long long;
using ld = long double;
using ii = pair<int, int>;
using vi = vector<int>;

template<class X, class Y> bool maximize(X &a, Y b) {
    return a < b ? a = b, 1 : 0;
}
template<class X, class Y> bool minimize(X &a, Y b) {
    return a > b ? a = b, 1 : 0;
}

const int MAXN = 1e5 + 11;
// const int MOD = 1e9 + 7;
// const int INF = 1e9 + 11; const ll INFF = (ll) 1e18 + 11;
const int LOG = 31;
// const int BASE = 311;
// const int BLOCK = 330;

int n, k, a[MAXN], pref[MAXN];

struct Trie {
    struct Node {
        int cnt = 0;
        Node *child[2];

        Node() {
            child[0] = child[1] = nullptr;
        }
    };

    Node *root;

    Trie() {
        root = new Node();
    }

    void add(const int &s) {
        Node *p = root;
        FORD(i, LOG, 0) {
            int b = getbit(i, s);
            if (p->child[b] == nullptr) p->child[b] = new Node();
            p = p->child[b];
        }
        p->cnt = max(p->cnt, s);
    }

    ll calc(int x) {
        Node *p = root;
        FORD(i, LOG, 0) {
            int b1 = getbit(i, x);

			if (p->child[b1 ^ 1] != nullptr) b1 = b1 ^ 1;
			p = p->child[b1];
        }
        return x ^ (p->cnt);
    }
} trie;

int32_t main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    if (fopen(name".inp", "r")) {
        freopen(name".inp", "r", stdin);
        freopen(name".out", "w", stdout);
    }
    //___________________________________
    cin >> n;
    FOR(i, 1, n) cin >> a[i];
    FOR(i, 1, n) pref[i] = pref[i - 1] ^ a[i];

    trie.add(0);

    ll res = 0;
    FOR(i, 1, n) {
        res = max(res, trie.calc(pref[i]));
        trie.add(pref[i]);
    }

    cout << res;

    return 0;
}
