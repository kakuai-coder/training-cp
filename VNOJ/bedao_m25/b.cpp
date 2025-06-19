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
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define SZ(v) (int) (v).size()
#define ALL(v) (v).begin(), (v).end()
#define MASK(x) (1LL << (x))
#define ONBIT(i, mask) (mask | MASK(i))
#define OFFBIT(i, mask) mask & ~(MASK(i))

template <class X, class Y> bool maximize(X &a, const Y &b) { return a < b ? a = b, 1 : 0; }
template <class X, class Y> bool minimize(X &a, const Y &b) { return a > b ? a = b, 1 : 0; }

ll n, A, B, C;

ll gcd(ll a, ll b) {
    ll r; 
    while (b) {
        r = a % b; 
        a = b;
        b = r;
    }
    return a;
}

ll lcm_optimize(ll A, ll B) {
    ll x = gcd(A, B);
    A /= x;
    A *= B;
    if (A < 0) A = (ll) 1e18 + 11;
    return A;
}

ll count_div(ll x) {
    ll res = 1;
    for (int i = 2; i * i <= x; ++i) {
        ll cnt = 0; 
        while (x % i == 0) {
            x /= i;
            cnt++;
        }
        res = res * (cnt + 1);
    }
    if (x != 1) res = res * 2;
    return res; 
}

void process(void) {
    cin >> n >> A >> B >> C;
    ll x = lcm_optimize(lcm_optimize(A, B), C);
    ll ans = 0;
    ll d = lcm_optimize(A, B);
    if (n % d == 0) {
        ans += count_div(n / d);
    }

    d = lcm_optimize(A, C);
    if (n % d == 0) {
        ans += count_div(n / d);
    }

    d = lcm_optimize(B, C);
    if (n % d == 0) {
        ans += count_div(n / d);
    }

    if (n % x == 0) {
        ans -= 2 * count_div(n / x);
    }

    cout << ans; 
}
signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // int t; cin >> t; while (t--)
    process();

    return 0;
}
