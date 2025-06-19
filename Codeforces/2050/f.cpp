/**
 * author: tinhnopro (tinh nop)
 * created: 2024-12-03
**/
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 0
#endif // LOCAL

#include <bits/stdc++.h>

#define TASK ""

using namespace std;

template <typename T> int isize(const T& a) { return a.size(); }

bool maximize(int& a, int b) {
	return a < b ? a = b, true : false;
}

bool minimize(int& a, int b) {
	return a > b ? a = b, true : false;
}

const int maxN = 3e5 + 11, LOG = 20;

int n, q, a[maxN], diff[maxN], st[LOG + 1][maxN];

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	while (t--) {

		cin >> n >> q;

		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
		}

		for (int i = 1; i < n; ++i) {
			diff[i] = abs(a[i + 1] - a[i]);
		}

		// (l, r) -> (l, r - 1)

		for (int i = 1; i < n; ++i) {
			st[0][i] = diff[i];
		}

		for (int j = 1; j <= LOG; ++j) {
			for (int i = 1; i + (1 << j) - 1 < n; ++i) {
				st[j][i] = __gcd(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
			}
		}

		auto query = [&] (int l, int r) -> int {
			int k = __lg(r - l + 1);
			return __gcd(st[k][l], st[k][r - (1 << k) + 1]);
		};

		while (q--) {
			int l, r; cin >> l >> r;
			if (l == r) cout << 0;
			else {
				int ans = query(l, r - 1);
				if (ans == 0) cout << 0;
				else cout << ans;
			}
			cout << ' ';
		}
		cout << '\n';
	}
}

