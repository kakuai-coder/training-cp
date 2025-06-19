/**
 * author: tinhnopro (tinh nop)
 * created: 2024-11-25
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

const int maxN = 3e5 + 11;

int n, p[maxN];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
#ifdef LOCAL
	freopen("865D.inp", "r", stdin);
	freopen("865D.out", "w", stdout);
#endif // LOCAL

	cin >> n;

	priority_queue<int, vector<int>, greater<int>> pq;
	int64_t ans = 0;

	for (int i = 1; i <= n; ++i) {
		cin >> p[i];#
		pq.push(p[i]);
		pq.push(p[i]);
		ans += p[i] - pq.top();
		pq.pop();
	}

	cout << ans;
}
