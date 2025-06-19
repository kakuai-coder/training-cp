/**
 * author: tinhnopro (tinh nop)
 * created: 2024-11-26
**/

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif // LOCAL

#include <bits/stdc++.h>

using namespace std;

template <class A, class B>
bool maximize(A& a, B b) {
	return a < b ? a = b, true : false;
}

template <class A, class B>
bool minimize(A& a, B b) {
	return a > b ? a = b, true : false;
}

const int MAX = 1e6 + 11;

int n, k;
int mark[MAX], pref_mark[MAX];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> k;
	int min_val = MAX;
	for (int i = 0; i < n; ++i) {
		int x; cin >> x;
		mark[x]++;
		minimize(min_val, x);
	}

	for (int i = 1; i < MAX; ++i) pref_mark[i] = pref_mark[i - 1] + mark[i];

	int ans = min_val;
	for (int i = min_val; i > k; --i) {
		int cnt = 0;
		for (int j = 0; j < MAX; j += i)
			cnt += pref_mark[min({MAX - 1, j + k})] - pref_mark[max(0, j - 1)];

		if (cnt == n) {
			cout << i;
			return 0;
		}
	}
	cout << ans;
}
