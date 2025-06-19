#include<bits/stdc++.h>

// Author: Tinhnopro (a.k.a NVT)

using namespace std;

#define el '\n'
#define pii pair<int, int>
#define fi first
#define se second
#define vi vector<int>
#define ll long long
#define ld long double
//#define int long long
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define FORA(it, v) for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
#define SZ(v) (int) (v).size()
#define ALL(v) (v).begin(), (v).end()
#define MASK(x) (1LL << (x))
#define BIT(x, i) ((i) & MASK(x))
#define ONBIT(x, i) ((i) | MASK(x))
#define OFFBIT(x, i) ((i) & ~MASK(x))

template <class X, class Y> bool maximize(X &a, const Y &b) { return a < b ? a = b, 1 : 0; }
template <class X, class Y> bool minimize(X &a, const Y &b) { return a > b ? a = b, 1 : 0; }


const char vowels[] = {'a', 'e', 'i', 'o', 'u'};

void process(void) {
    int n;
    cin >> n;
    string s = "";
    int k = n / 5;
    int x = n % 5;
    FOR(i, 0, 4) {
        FOR(j, 1, k) s.push_back(vowels[i]);
        if (x) {
            s.push_back(vowels[i]);
            x--;
        }
    }
    cout << s << el;
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #define Task "A"
    if (fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

    int t; cin >> t; while (t--)
    process();

    return 0;
}
