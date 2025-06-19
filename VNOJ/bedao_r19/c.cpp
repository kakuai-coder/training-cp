#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define BIT(x, i) ((x) & (1 << (i)))
#define MASK(x) (1 << (x))
#define ALL(v) (v).begin(), (v).end()
#define FOR(i, a, b) for (int i = (a), _b = (b); i < _b; ++i)
#define FORE(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORDE(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define file(name) if (fopen(name".inp", "r")) { freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;

template<class X, class Y> bool maximize(X &a, const Y &b) { return a < b ? a = b, 1 : 0; };
template<class X, class Y> bool minimize(X &a, const Y &b) { return a > b ? a = b, 1 : 0; };

/// Author: tinhnopro
// end of template

const int MAXN = 5e5 + 11, MAX = 1e6 + 11;
//const int MOD = 1e9 + 7;
//const int INF = 1e9 + 11; const ll INFF = 1e18 + 11;
//const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};

int n, a[MAX], pos[MAX], dp[MAX], upPos[MAX];

void process(void) {
    cin >> n;
    FORE(i, 1, n) cin >> a[i];

    memset(pos, -1, sizeof pos);
    int ans = 0, last = -1;

    FORE(i, 1, n) {
        if (pos[a[i] + 1] != -1) {
            dp[i] = dp[pos[a[i] + 1]] + 1;
            upPos[i] = pos[a[i] + 1];
        } else {
            dp[i] = 1;
            upPos[i] = i;
        }
        pos[a[i]] = i;
        if (maximize(ans, dp[i])) {
            last = i;
        }
    }
    cout << ans << "\n";
    stack<int> st;
    st.push(last);
    while (upPos[last] != last) {
        last = upPos[last];
        st.push(last);
    }
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	file("c");
//	int t; cin >> t; while(t--)
	process();
	return 0;
}
