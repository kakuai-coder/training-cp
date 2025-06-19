/*
	Author: tinhnopro
	created: 24.02.2025 22:50:05
*/
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif // LOCAL

#define TASK "2"

using namespace std;

using i64 = long long;

struct query_t {
	int p, x, l, r, idx; 

	query_t() {
		p = x = l = r = idx = 0;
	}

	query_t(int _p, int _x) {
		p = _p; 
		x = _x; 
		l = r = idx = 0; 
	}

	bool operator<(const query_t& ot) const {
		return make_pair(p, x) < make_pair(ot.p, ot.x);
	}
};
 

const int maxN = 3e5 + 5; 
int n, q, a[maxN], l[maxN], r[maxN], mark[maxN], cnt[maxN];
query_t queries[maxN]; 
int ans[maxN]; 

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	if (fopen(TASK".inp", "r")) {
		freopen(TASK".inp", "r", stdin);
		freopen(TASK".out", "w", stdout);
	}

	cin >> n >> q; 
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}	

	vector<int> v; 
	v.clear(); 

	for (int i = 1; i <= n; ++i) {
		l[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin(); 
		if (l[i] == (int)v.size()) {
			v.push_back(a[i]); 
		} else {
			v[l[i]] = a[i]; 
		}

		l[i]++;
	}	

	v.clear(); 

	for (int i = n; i; --i) {
		r[i] = lower_bound(v.begin(), v.end(), a[i], greater<int>()) - v.begin(); 
		if (r[i] == (int)v.size()) {
			v.push_back(a[i]);
		} else {
			v[r[i]] = a[i];
		}
		r[i]++; 
	}

	int lis = v.size(); 

	for (int i = 1; i <= n; ++i) {
		if (l[i] + r[i] - 1 == lis) {
			mark[i] = 1; 
			cnt[l[i]]++; 
		}
	}

	auto isfullLIS = [](int idx) -> bool {
		return mark[idx] && cnt[l[idx]] == 1;
	};

	for (int i = 1; i <= q; ++i) {
		cin >> queries[i].p >> queries[i].x; 
		queries[i].idx = i; 
	}

	sort(queries + 1, queries + q + 1); 

	v.clear();

	for (int i = 1, j = 1; i <= n; ++i) {
		while (j <= q && queries[j].p < i) ++j; 
		while (j <= q && queries[j].p == i) {
			queries[j].l = lower_bound(v.begin(), v.end(), queries[j].x) - v.begin() + 1; 
			j++;
		}

		if (l[i] - 1 == (int)v.size()) {
			v.push_back(a[i]);
		} else {
			v[l[i] - 1] = a[i];
		}
	}

	v.clear(); 

	for (int i = n, j = q; i; --i) {
		while (j && queries[j].p > i) --j; 
		while (j && queries[j].p == i) {
			queries[j].r = lower_bound(v.begin(), v.end(), queries[j].x, greater<int>()) - v.begin() + 1; 
			j--;
		}
		if (r[i] - 1 == (int)v.size()) {
			v.push_back(a[i]);
		} else {
			v[r[i] - 1] = a[i];
		}
	}

	for (int i = 1; i <= q; ++i) {
		int x1 = 0; 
		if (!isfullLIS(queries[i].p)) {
			x1 = lis; 
		} else {
			x1 = lis - 1; 
		}

		int x2 = queries[i].l + queries[i].r - 1; 

		// cout << x1 << ' ' << x2 << '\n';

		ans[queries[i].idx] = max(x1, x2); 
	}

	for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
}