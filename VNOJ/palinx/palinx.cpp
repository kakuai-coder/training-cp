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
const ll MOD = (int) 1e9 + 8277;
//const ll INF = (ll) 1e18 + 11;
const ll BASE = 311;
//const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};

struct Hash {
    vector<ll> hashS, hashRS, Pow;
    int length;

    void init(const string &s) {
        length = s.size();

        string t = " " + s;
        string rev = " ";
        FORD(i, length, 1) rev.push_back(t[i]);

        hashS.assign(length + 1, 0);
        hashRS.assign(length + 1, 0);
        Pow.assign(length + 1, 0);

        Pow[0] = 1;

        FOR(i, 1, length) {
            Pow[i] = Pow[i - 1] * BASE % MOD;
            hashS[i] = (hashS[i - 1] * BASE + t[i] - 'a' + 1) % MOD;
            hashRS[i] = (hashRS[i - 1] * BASE + rev[i] - 'a' + 1) % MOD;
        }
    }

    ll getHash(int i, int j) {
        return (hashS[j] - hashS[i - 1] * Pow[j - i + 1] + MOD * MOD) % MOD;
    }

    ll getHashR(int i, int j) {
        return (hashRS[length - i + 1] - hashRS[length - j] * Pow[j - i + 1] + MOD * MOD) % MOD;
    }

    bool isPalin(int i, int j) {
        return (getHash(i, j) == getHashR(i, j));
    }
};

vector<Hash> v;
int n;
map<ll, int> cnt;

void process(void) {
    cin >> n;
    v.resize(n + 1);
    FOR(i, 1, n) {
        string s;
        int len;
        cin >> len >> s;
        v[i].init(s);
        cnt[v[i].hashS[v[i].length]]++;
    }
    ll ans = 0;
    FOR(i, 1, n) {
        ans += cnt[v[i].getHashR(1, v[i].length)];
        FOR(j, 1, v[i].length - 1) {
            if (v[i].isPalin(j + 1, v[i].length)) {
                ans += cnt[v[i].getHashR(1, j)];
            }
            if (v[i].isPalin(1, j)) {
                ans += cnt[v[i].getHashR(j + 1, v[i].length)];
            }
        }
    }
    cout << ans;
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

    file("palinx");

//	int t; cin >> t; while(t--)
	process();
	return 0;
}
