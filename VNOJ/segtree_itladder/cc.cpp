#include <bits/stdc++.h>

#define TASK ""

using namespace std;

using i64 = long long;

const int maxN = 2e5 + 5;
const int fix = 2e5;

i64 a[maxN], b[maxN], mark[2 * maxN];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m, q;
	cin >> n >> m >> q;

	for (int i = 1; i <= n; ++i)
		cin >> a[i];

	for (int i = 1; i <= m; ++i)
		cin >> b[i];

	i64 suma = 0, sumb = 0;

	for (int i = 1; i <= n; ++i) {
		suma += a[i];
	}

	for (int i = 1; i <= m; ++i) {
		sumb += b[i];
	}

	vector<i64> v1, v2;

	for (int i = 1; i <= n; ++i)
		v1.push_back(sumb * (suma - a[i]));

	for (int i = 1; i <= m; ++i)
		v2.push_back(suma * (sumb - b[i]));

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	v1.resize(unique(v1.begin(), v1.end()) - v1.begin());
	v2.resize(unique(v2.begin(), v2.end()) - v2.begin());

	while (v1.back() > fix) v1.pop_back();
	while (v2.back() > fix) v2.pop_back();

	for (i64 x : v1) cout << x << ' ';
	cout << '\n';
	for (i64 y : v2) cout << y << ' ';
	cout << '\n';

	for (i64 x : v1) {
		for (i64 y : v2) {
			if (x + y > fix) break;
			if (abs(x + y) <= fix) {
				mark[x + y + fix] = 1;
			}
		}
	}

	while (q--) {
		int x; cin >> x;
		cout << (mark[x + fix] == 1 ? "YES" : "NO") << '\n';
	}
}
