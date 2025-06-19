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

#define TASK "C"

using namespace std;

template <typename T> int isize(const T& a) { return a.size(); }

template <typename T1, typename T2> bool maximize(T1& a, T2 b) { return a < b ? a = b, true : false; }
template <typename T1, typename T2> bool minimize(T1& a, T2 b) { return a > b ? a = b, true : false; }


void solve() {
	int n;
	cin >> n;
	if (n & 1) {
		if (n < 27) {
			cout << -1 << '\n';
			return ;
		}

		cout << 1 << ' ';
		for (int i = 3; i <= 6; ++i) cout << i << ' ' << i << ' ';
		cout << 1 << ' ' << 2 << ' ';
		for (int i = 7; i <= 13; ++i) cout << i << ' ' << i << ' ';
		cout << 1 << ' ' << 2 << ' ';

		for (int i = 14; i <= 14 + (n - 27) / 2 - 1; ++i) cout << i << ' ' << i << ' ';

		cout << '\n';
		return ;
	}

	for (int i = 1; i <= n / 2; ++i) {
		cout << i << ' ' << i << ' ';
	}
	cout << '\n';
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (ifstream(TASK ".inp")) {
		freopen(TASK ".inp", "r", stdin);
		freopen(TASK ".out", "w", stdout);
	}

	int t; cin >> t;
	while (t--) solve();
}
