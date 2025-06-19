/**
 * author: tinhnopro (tinh nop)
 * created: 2024-12-09
**/
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 0
#endif // LOCAL

#include <bits/stdc++.h>

using namespace std;

const int maxN = 5e5 + 5;
const int64_t base = 311, mod = 1e9 + 7;

int n;
int64_t Hash[maxN], Pow[maxN], pref[maxN];
char c[maxN];

void init() {
	Pow[0] = 1;

	for (int i = 1; i <= n; ++i) {
		Pow[i] = Pow[i - 1] * base % mod;
		Hash[i] = (Hash[i - 1] * base % mod + (c[i] - 'a' + 1)) % mod;
	}
}

int64_t getHash(int l, int r) {
	return (Hash[r] - Hash[l - 1] * Pow[r - l + 1] % mod + mod * mod) % mod;
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (fopen("kmp_pscnt.inp", "r")) {
		freopen("kmp_pscnt.inp", "r", stdin);
		freopen("kmp_pscnt.out", "w", stdout);
	}

	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> c[i];

	init();

	for (int i = 1; i <= n; ++i) {
		int l = 0, r = n - i + 2;
		while (r - l > 1) {
			int mid = (l + r) >> 1;
			if (getHash(i, i + mid - 1) == getHash(1, mid)) l = mid;
			else r = mid;
		}
//		cout << i << ' ' << l << '\n';
		pref[1]++;
		pref[l + 1]--;
	}

	for (int i = 1; i <= n; ++i) pref[i] += pref[i - 1];

	vector<pair<int, int> > ans;

	for (int i = 1; i <= n; ++i) if (pref[i] && getHash(1, i) == getHash(n - i + 1, n)) {
		ans.emplace_back(i, pref[i]);
	}

	cout << ans.size() << '\n';
	for (auto x : ans) cout << x.first << ' ' << x.second << '\n';
}
