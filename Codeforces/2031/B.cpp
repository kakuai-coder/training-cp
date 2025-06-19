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

#define TASK "B"

using namespace std;

template <typename T> int isize(const T& a) { return a.size(); }

template <typename T1, typename T2> bool maximize(T1& a, T2 b) { return a < b ? a = b, true : false; }
template <typename T1, typename T2> bool minimize(T1& a, T2 b) { return a > b ? a = b, true : false; }


int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (ifstream(TASK ".inp")) {
		freopen(TASK ".inp", "r", stdin);
		freopen(TASK ".out", "w", stdout);
	}

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> a(n);
		for (auto &x : a) cin >> x;
		for (int i = 0; i < n - 1; ++i) {
			if (a[i] > a[i + 1] && abs(a[i] - a[i + 1]) == 1) {
				swap(a[i], a[i + 1]);
			}
		}

		if (is_sorted(a.begin(), a.end())) {
			cout << "YES\n";
		} else cout << "NO\n";
	}
}

