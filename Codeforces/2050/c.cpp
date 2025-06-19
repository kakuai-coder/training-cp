/**
 * author: tinhnopro (tinh nop)
 * created: 2024-12-05
**/
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 0
#endif // LOCAL

#include <bits/stdc++.h>

using namespace std;

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t; cin >> t;
	while (t--) {
		string n;
		cin >> n;

		int res = 0, sum3 = 0, sum2 = 0, cnt2 = 0, cnt3 = 0;

		for (char c : n) {
			if (c == '3') {
				sum3 += 3;
				sum3 %= 9;
				cnt3++;
				continue;
			}
			if (c == '2') {
				cnt2++;
			}
			res += (c - '0');
			res %= 9;
		}

		if (cnt3 == 0) {
			while (res % 9 != 0 && cnt2) {
				res += 2;
				res %= 9;
				cnt2--;
			}

			if (res % 9 == 0) cout << "YES\n";
			else cout << "NO\n";
			continue;
		} else if (cnt3 == 1) {
			while (res % 9 != 0 && res % 9 != 6 && cnt2) {
				res += 2;
				res %= 9;
				cnt2--;
			}

			if (res % 9 == 0 || res % 9 == 6) cout << "YES\n";
			else cout << "NO\n";
			continue;
		} else {
			while (res % 9 != 0 && res % 9 != 6 && res % 9 != 3 && cnt2) {
				res += 2;
				res %= 9;
				cnt2--;
			}

			if (res % 9 == 0 || res % 9 == 3 || res % 9 == 6) cout << "YES\n";
			else cout << "NO\n";
			continue;
		}
	}
}

