/**
 * author: tinhnopro (tinh nop)
 * created: 2024-11-27
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

constexpr int maxN = 3e4 + 11, maxQ = 2e5 + 11, maxV = 1e6 + 11;
constexpr int blockSize = sqrt(maxN);

struct Query {
	int l, r, idx;

	Query() : l(0), r(0), idx(0) {}

	void read(const int& i) {
		cin >> l >> r;
		idx = i;
	}

	bool operator < (const Query &other) const {
		if (l / blockSize != other.l / blockSize) {
			return l < other.l;
		}

		return ((l / blockSize) % 2 ? r < other.r : r > other.r);
	}
};

int n, q, a[maxN], cnt[maxV];
Query queries[maxQ];
int ans[maxQ];

void del(int &ans, int idx) {
	if (cnt[a[idx]] == 1) ans--;
	cnt[a[idx]]--;
}

void add(int &ans, int idx) {
	if (cnt[a[idx]] == 0) ans++;
	cnt[a[idx]]++;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
#ifdef LOCAL
	freopen("dquery.inp", "r", stdin);
	freopen("dquery.out", "w", stdout);
#endif // LOCAL

	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];

	cin >> q;
	for (int i = 1; i <= q; ++i)
		queries[i].read(i);

	int res = 0;
	sort(queries + 1, queries + q + 1);

	for (int i = 1, l = 1, r = 0; i <= q; ++i) {
		while (l < queries[i].l) del(res, l++);
		while (l > queries[i].l) add(res, --l);
		while (r < queries[i].r) add(res, ++r);
		while (r > queries[i].r) del(res, r--);
		ans[queries[i].idx] = res;
	}

	for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
}
