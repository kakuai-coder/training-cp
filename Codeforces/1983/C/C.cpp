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
#define FOR(i, a, b) for (int i = (a), _b = (b); i < _b; ++i)
#define FORE(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORDE(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define BIT(x, i) ((x) & (1LL << (i)))
#define MASK(x) (1LL << (x))
#define ONBIT(x, i) ((x) | (1LL << (i)))
#define OFFBIT(x, i) ((x) & ~(1LL << (i)))
#define file(name) if (fopen(name".inp", "r")) freopen(name".inp", "r", stdin), freopen(name".out", "w", stdout)

template<class X, class Y> bool maximize(X &a, const Y &b) { return a < b ? a = b, 1 : 0; };
template<class X, class Y> bool minimize(X &a, const Y &b) { return a > b ? a = b, 1 : 0; };

/// Author: tinhnopro
// end of template

const int MAXN = 5e5 + 11;
//const int MOD = 1e9 + 7;
//const ll INF = 1e9 + 11;
//const ll BASE = 311;
//const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};

struct D {
    int x, y, z;
    D(int _x, int _y, int _z) {
        x = _x; y = _y, z = _z;
    }
};

int n;
ll a[3][MAXN], tot;
pii x[3];

bool check(int x_0, int x_1, int x_2) {
    FORE(i, 1, n) if (a[x_0][i] >= tot) {
        x[x_0] = {1, i};
        break;
    }
    if (x[x_0].se == -1) return false;
    x[x_1].fi = x[x_0].se + 1;
    FORE(i, x[x_1].fi, n) if (a[x_1][i] - a[x_1][x[x_1].fi - 1] >= tot) {
        x[x_1].se = i;
        break;
    }
    if (x[x_1].se == -1) return false;
    x[x_2].fi = x[x_1].se + 1;
    FORE(i, x[x_2].fi, n) if (a[x_2][i] - a[x_2][x[x_2].fi - 1] >= tot) {
        x[x_2].se = i;
        break;
    }
    if (x[x_2].se == -1) return false;
    else return true;
}

void process(void) {
    cin >> n;
    FORE(i, 1, n) cin >> a[0][i];
    FORE(i, 1, n) cin >> a[1][i];
    FORE(i, 1, n) cin >> a[2][i];

    FORE(i, 1, n) a[0][i] = a[0][i - 1] + a[0][i];
    FORE(i, 1, n) a[1][i] = a[1][i - 1] + a[1][i];
    FORE(i, 1, n) a[2][i] = a[2][i - 1] + a[2][i];

    tot = a[0][n];
    tot = tot / 3 + (tot % 3 != 0);
    vector <D> l;
    l.push_back({0, 1, 2});
    l.push_back({0, 2, 1});
    l.push_back({1, 0, 2});
    l.push_back({1, 2, 0});
    l.push_back({2, 1, 0});
    l.push_back({2, 0, 1});

    for (D k : l) {
        FOR(i, 0, 3) x[i].fi = x[i].se = -1;
        if (check(k.x, k.y, k.z)) {
            FOR(i, 0, 3) cout << x[i].fi << " " << x[i].se << " ";
            cout << el;
            return ;
        }
    }
    cout << -1 << el;
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

    file("C");

	int t; cin >> t; while(t--)
	process();

	return 0;
}
