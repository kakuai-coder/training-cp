#include <bits/stdc++.h>

using namespace std;

#define el  "\n"
#define ll  long long
#define ull unsigned long long
#define pii pair<int, int>
#define vi  vector<int>
#define fi  first
#define se  second
#define ALL(v) (v).begin(), (v).end()
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define FORX(i, a, b, x) for (int i = (a), _b = (b); i <= _b; i += (x))
#define BIT(x, i) ((x) & (1LL << (i)))
#define MASK(x) (1LL << (x))
#define ONBIT(x, i) ((x) | (1LL << (i)))
#define OFFBIT(x, i) ((x) & ~(1LL << (i)))
#define file(name) if (fopen(name".inp", "r")) freopen(name".inp", "r", stdin), freopen(name".out", "w", stdout)

template<class X, class Y> bool maximize(X &a, const Y &b) { return a < b ? a = b, 1 : 0; };
template<class X, class Y> bool minimize(X &a, const Y &b) { return a > b ? a = b, 1 : 0; };

/// Author: tinhnopro
// end of template

const int MAXN = (int) 5e5 + 11;
//const int MOD = (int) 1e9 + 7;
//const ll INF = (ll) 1e18 + 11;
//const ll BASE = 311;
//const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};

int lab[MAXN], n, q;
map<int, int> cnt[MAXN];

int find_par(int u) {
    return (lab[u] > 0 ? lab[u] = find_par(lab[u]) : u);
}

void union_set(int a, int b) {
    a = find_par(a);
    b = find_par(b);

    if (a == b) return ;

    if (lab[a] > lab[b]) swap(a, b);
    lab[a] += lab[b];
    lab[b] = a;

    for (pii x : cnt[b]) {
        cnt[a][x.fi] += x.se;
        cnt[b][x.fi] = 0;
    }
}

void process(void) {
    cin >> n >> q;
    FOR(i, 1, n) {
        int x; cin >> x;
        lab[i] = -1;
        cnt[i][x]++;
    }

    while (q--) {
        int type, u, v;
        cin >> type >> u >> v;
        if (type == 1) {
            union_set(u, v);
        } else {
            u = find_par(u);
            cout << cnt[u][v] << el;
        }
    }
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

    file("colquery");

//	int t; cin >> t; while(t--)
	process();
	return 0;
}
