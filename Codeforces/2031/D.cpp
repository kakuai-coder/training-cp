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

#define TASK "D"

using namespace std;

template <typename T> int isize(const T& a) { return a.size(); }

template <typename T1, typename T2> bool maximize(T1& a, T2 b) { return a < b ? a = b, true : false; }
template <typename T1, typename T2> bool minimize(T1& a, T2 b) { return a > b ? a = b, true : false; }


void solve() {
	int n; cin >> n;

	vector<int> a(n + 2), pref(n + 2), suff(n + 2), answer(n + 2);

	for (int i = 1; i <= n; ++i) cin >> a[i];

	pref[0] = 0;
	for (int i = 1; i <= n; ++i) pref[i] = max(pref[i - 1], a[i]);

	suff[n + 1] = 1e9;
	for (int i = n; i; --i) suff[i] = min(suff[i + 1], a[i]);

	answer[n] = pref[n];
	for (int i = n - 1; i; --i) {
		if (pref[i] > suff[i + 1]) answer[i] = answer[i + 1];
		else answer[i] = pref[i];
	}

	for (int i = 1; i <= n; ++i) cout << answer[i] << ' ';

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

