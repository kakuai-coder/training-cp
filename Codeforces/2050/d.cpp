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
		string s; cin >> s;

		vector<int> a(s.size());

		for (int i = 0; i < s.size(); ++i) a[i] = s[i] - '0';

		for (int i = 1; i < s.size(); ++i) {
			int j = i;
			while (j > 0 && a[j] - 1 > a[j - 1]) {
				a[j]--;
				swap(a[j], a[j - 1]);
				j--;
			}
		}

		for (int i = 0; i < s.size(); ++i) cout << a[i];
		cout << '\n';
	}
}

