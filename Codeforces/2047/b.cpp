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

#define TASK ""

using namespace std;


int32_t main() {
	cin.tie(0)->sync_with_stdio(false);
	if (fopen(TASK ".inp", "r")) {
		freopen(TASK ".inp", "r", stdin);
		freopen(TASK ".out", "w", stdout);
	}

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<char> a(n);
		vector<int> cnt(26, 0);
		for (auto &x : a) cin >> x;

		char max_char = '_';
		int max_cnt = -1, min_cnt = n + 1;
		for (auto &x : a) {
			cnt[x - 'a']++;
		}

//		debug(cnt);

		for (auto &x : a) {
			min_cnt = min(min_cnt, cnt[x - 'a']);
			if (max_cnt < cnt[x - 'a']) {
				max_cnt = cnt[x - 'a'];
				max_char = x;
			}
		}

		for (auto &x : a) {
			if (cnt[x - 'a'] == min_cnt && x != max_char) {
				x = max_char;
				break;
			}
		}

		for (auto &x : a) cout << x;
		cout << '\n';
	}
}

