/*
	Author: kakuai
	created: 2025.07.03 16:02:21
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#define int long long 

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

const int maxN = 2e5 + 5;
int n;
int a[maxN], w[maxN], dp[maxN];

struct Fenwick {
    int n;
    int f[maxN];
    void init(int _n) {
        n = _n;
        for (int i = 0; i <= n; ++i) f[i] = 0;
    }
    void update(int i, int v) {
        for (; i <= n; i += i & -i)
            f[i] = max(f[i], v);
    }
    int query(int i) {
        int res = 0;
        for (; i; i -= i & -i)
            res = max(res, f[i]);
        return res;
    }

		void update2(int i, int v) {
        for (; i; i -= i & -i)
            f[i] = max(f[i], v);
    }
    int query2(int i) {
        int res = 0;
        for (; i <= n; i += i & -i)
            res = max(res, f[i]);
        return res;
    }
} fenw1, fenw2;

void kakuai() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> w[i];

    vector<int> compress(a + 1, a + n + 1);
    sort(compress.begin(), compress.end());
    compress.erase(unique(compress.begin(), compress.end()), compress.end());
    int m = compress.size();

    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(compress.begin(), compress.end(), a[i]) - compress.begin() + 1;
    }

    fenw1.init(n + 2);
    for (int i = n; i >= 1; --i) {
        dp[i] = w[i] + fenw1.query2(a[i] + 1);
        fenw1.update2(a[i], dp[i]);

				// cout << dp[i] << ' ' << a[i] << '\n';
    }

    fenw2.init(n + 2);
    int res = 0;
    for (int i = n; i >= 1; --i) {
        int prefix = fenw2.query(a[i] - 1);
        res = max(res, dp[i] + prefix);
        fenw2.update(a[i], prefix + w[i]);
    }

    cout << res << '\n';
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "h"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}