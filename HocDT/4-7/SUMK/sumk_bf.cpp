#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using str = string;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <class T>
using vector2 = vector<vector<T>>;
template <class T>
using vector3 = vector<vector2<T>>;
#define sp ' '
#define nl '\n'
#define fi first
#define se second
#define size(a) ((int)(a).size())
#define all(a) begin(a), end(a)
#define tvl (tv * 2)
#define tvr (tv * 2 + 1)
#define FOR(i, l, r) for (int i = (l), _r = (r); i <= _r; i++)
#define FORD(i, r, l) for (int i = (r), _l = (l); i >= _l; i--)
#define FORIN(it, a) for (auto& it : a)
#define bmask(i) (1LL << (i))
#define bget(i, n) ((n) >> (i) & 1)
const ll MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
void addmod(ll& a, ll b) { a = (a + b % MOD) % MOD; }
void submod(ll& a, ll b) { a = (a + MOD - b % MOD) % MOD; }
void mulmod(ll& a, ll b) { a = a * (b % MOD) % MOD; }
template <class T, class... C>
void assign(int n, const T& v, C&&... a) {
    using e = int[];
    e{(a.assign(n, v), 0)...};
}
template <class... C>
void resize(int n, C&&... a) {
    using e = int[];
    e{(a.resize(n), 0)...};
}
////////////////////////////////////////
template <class... T>
void print(T&&... a) {
    cout << flush;
    clog << "\n[debug] ";
    using e = int[];
    e{(clog << a << sp, 0)...};
    clog << endl;
}
template <class Ch, class Tr, class C>
basic_ostream<Ch, Tr>& operator<<(basic_ostream<Ch, Tr>& cout, C a) {
    cout << "{ ";
    FORIN(it, a) cout << it << sp;
    return cout << "}";
}
template <class T1, class T2>
ostream& operator<<(ostream& cout, pair<T1, T2> a) {
    return cout << '(' << a.fi << sp << a.se << ')';
}
void logtime() {
    print("[time]", clock() * 1.0 / CLOCKS_PER_SEC);
}


// sumk
// dp, monotonic stack, binsearch


int n, m;
vector<int> a;
///////////////////////////////////////////////////////////////////////////////
namespace subf {
    ////////////////////////////////////////
    ////////////////////////////////////////
    void main() {
        vector2<ll> dp, dpsum, invalid;
        assign(n + 1, vector<ll>(m + 1), dp, dpsum, invalid);
        
        dp[0][0] = dpsum[0][0] = 1;
        deque<int> stk{0};
        a[0] = INF;
        
        
        ll ans = 1;
        FOR(idx, 1, n) {
            invalid[idx] = invalid[idx - 1];
            
            while (a[stk.back()] < a[idx]) {
                int last = stk.back();
                stk.pop_back();
                FOR(i, 0, m) {
                    submod(invalid[idx][i], dp[last][i]);
                }
            }
            
            
            int lo = 0, hi = size(stk) - 1, pre = 0;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (a[stk[mid]] > a[idx]) {
                    pre = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            
            
            FOR(sum, a[idx], m) {
                dp[idx][sum] = (dpsum[stk[pre]][sum - a[idx]] - invalid[stk[pre]][sum - a[idx]] + MOD) % MOD;
                addmod(ans, dp[idx][sum]);
            }
            FOR(i, 0, m) dpsum[idx][i] = (dpsum[idx - 1][i] + dp[idx][i]) % MOD;
            
            
            stk.push_back(idx);
            FOR(i, 0, m) {
                addmod(invalid[idx][i], dp[idx][i]);
            }
        }
        
        cout << ans;
    }
    void run() {
        main();
        exit(0);
    }
}
////////////////////////////////////////////////////////////////////////////////
int main() {
    #define TASK "sumk"
    // freopen(TASK".inp", "r", stdin);
    // freopen(TASK".out", "w", stdout);
    cin.tie(nullptr)->sync_with_stdio(false);
    atexit(logtime);
    ////////////////////////////////////////
    cin >> n >> m;
    
    resize(n + 1, a);
    FOR(i, 1, n) {
        cin >> a[i];
    }
    
    subf::run();
    ////////////////////////////////////////
    return 0;
}