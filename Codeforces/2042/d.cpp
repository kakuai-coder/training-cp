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

#define TASK "d"

using namespace std;

template <typename T> int isize(const T& a) { return a.size(); }

bool maximize(int& a, int b) {
	return a < b ? a = b, true : false;
}

bool minimize(int& a, int b) {
	return a > b ? a = b, true : false;
}

struct Point {
	int l, r, id;
	Point() {
		l = r = id = 0;
	}
	Point(int _l, int _r, int _id) : l(_l), r(_r), id(_id) {}

	bool operator ==(const Point& other) const {
		return l == other.l && r == other.r;
	}

};

bool cmp(const Point& a, const Point& b) {
	if (a.r == b.r) {
		return a.l > b.l;
	}
	return a.r < b.r;
}

bool cmp2(const Point& a, const Point &b) {
	if (a.l == b.l) {
		return a.r < b.r;
	}
	return a.l < b.l;
}


void solve() {
	int n; cin >> n;
	vector<Point> p(n);

	for (int i = 0; i < n; ++i) {
		cin >> p[i].l >> p[i].r;
		p[i].id = i;
	}

	sort(p.begin(), p.end(), cmp);

	vector<int> suff(n + 2), ans(n + 2, 0), pref(n + 2);


	suff[n] = -1e9;
	for (int i = n - 1; ~i; --i) {
		if (p[i] == p[i - 1]) {
				suff[i] = max(suff[i + 1], p[i].l);
				continue;
		}
		int l = i + 1, r = n - 1;
		while (r - l > 1) {
			int mid = (l + r) >> 1;
			if (suff[mid] <= p[i].l) r = mid;
			else l = mid;
		}
		if (l < n && p[i].l >= suff[l]) ans[p[i].id] += p[i].l - suff[l];
		suff[i] = max(suff[i + 1], p[i].l);
	}

	sort(p.begin(), p.end(), cmp2);

	pref[0] = p[0].r;
	for (int i = 1; i < n; ++i) {

		if (p[i] == p[i + 1]) {
				pref[i] = max(pref[i - 1], p[i].r);
				continue;
		}
		int l = 0, r = i;

		while (r - l > 1) {
			int mid = (l + r) >> 1;
			if (pref[mid] >= p[i].l) l = mid;
			else r = mid;
		}

		debug(i, l, pref[l]);

		if (l < i && pref[l] >= p[i].r) {
			ans[p[i].id] += pref[l] - p[i].r;
		}
		pref[i] = max(pref[i - 1], p[i].r);
	}

	for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
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
	while (t--) {
		solve();
	}
}

