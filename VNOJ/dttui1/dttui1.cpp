/**
 * author: tinhnopro (tinh nop)
 * created: 2024-11-28
**/

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif // LOCAL

#include <bits/stdc++.h>

using namespace std;

template <typename T> inline int isize(const T& a) { return a.size(); }

template <typename T1, typename T2> bool maximize(T1& a, T2 b) { return a < b ? a = b, true : false; }
template <typename T1, typename T2> bool minimize(T1& a, T2 b) { return a > b ? a = b, true : false; }


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
#ifdef LOCAL
	freopen("dttui1.inp", "r", stdin);
	freopen("dttui1.out", "w", stdout);
#endif // LOCAL

	int n, m;
	cin >> n >> m;

	vector<pair<int64_t, int64_t> > set1, set2;

	for (int i = 0, w, v; i < n; ++i) {
		cin >> w >> v;
		set1.emplace_back(w, v);
	}

	while (isize(set1) > n / 2) {
		set2.push_back(set1.back());
		set1.pop_back();
	}

	vector<pair<int64_t, int64_t> > answer1, answer2;

	for (int mask = 0; mask < (1 << isize(set1)); ++mask) {
		int64_t sum_w = 0, sum_v = 0;
		for (int i = 0; i < isize(set1); ++i) if ((mask >> i) & 1) {
			sum_w += set1[i].first;
			sum_v += set1[i].second;
		}
		answer1.emplace_back(sum_w, sum_v);
	}

	for (int mask = 0; mask < (1 << isize(set2)); ++mask) {
		int64_t sum_w = 0, sum_v = 0;
		for (int i = 0; i < isize(set2); ++i) if ((mask >> i) & 1) {
			sum_w += set2[i].first;
			sum_v += set2[i].second;
		}
		answer2.emplace_back(sum_w, sum_v);
	}

	sort(answer1.begin(), answer1.end());
	sort(answer2.begin(), answer2.end());

	for (int i = 1; i < isize(answer2); ++i) {
		maximize(answer2[i].second, answer2[i - 1].second);
	}

	debug(answer1);
	debug(answer2);

	int64_t ans = 0;

	for (int i = 0, j = answer2.size() - 1; i < isize(answer1); ++i) {
		while (j && answer1[i].first + answer2[j].first > m) --j;
		debug(i, j);
		if (answer1[i].first + answer2[j].first <= m)
			maximize(ans, answer1[i].second + answer2[j].second);
	}

	cout << ans;
}
