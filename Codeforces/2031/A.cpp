/**
 * author: tinhnopro (tinh nop)
 * created: 2024-12-02
**/
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 0
#endif // LOCAL

#include <bits/stdc++.h>

#define setIO(name) \
if (ifstream(name".inp")) freopen(name".inp", "r", stdin), freopen(name".out", "w", stdout)

using namespace std;

template <typename T> int isize(const T& a) { return a.size(); }

template <typename T1, typename T2> bool maximize(T1& a, T2 b) { return a < b ? a = b, true : false; }
template <typename T1, typename T2> bool minimize(T1& a, T2 b) { return a > b ? a = b, true : false; }


int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0); setIO("A");

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> a(n + 2);
		for (int i = 1; i <= n; ++i) cin >> a[i];
		int mx = 0;
		for (int i = 1; i <= n; ++i) {
			int cnt = 0;
			for (int j = 1; j <= n; ++j) {
				if (a[i] == a[j]) cnt++;
			}
			maximize(mx, cnt);
		}
		cout << n - mx << '\n';
	}
}
