#include <bits/stdc++.h>

using namespace std;

#define el  "\n"
#define ll  long long
#define ull unsigned long long
#define pii pair<ll, ll>
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

//const int MAXN = (int) 5e5 + 11;
//const int MOD = (int) 1e9 + 7;
//const ll INF = (ll) 1e18 + 11;
//const ll BASE = 311;
//const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};

int q;
multiset<pii> s;

void process(void) {
    cin >> q;
    ll cur = 0;
    ll cnt = 0;
    while (q--) {
        int type; ll x;
        cin >> type >> x;

        if (type == 1) {
            s.insert({x - cur, ++cnt});
        } else if (type == 2) {
            cur += x;
        } else {
            while (true) {
                auto it = s.lower_bound({x - cur, 0});
                if (it == s.end() || it->fi > x - cur) break;
                s.erase(it);
            }
        }
    }
    vector<pii> v;
    for (pii x : s) v.push_back({x.se, x.fi});
    sort(ALL(v));
    cout << v.size() << el;
    for (pii x : v) cout << x.se + cur << " ";
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

    file("bedao_m24_c");

//	int t; cin >> t; while(t--)
	process();
	return 0;
}
