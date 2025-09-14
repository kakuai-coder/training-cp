/*
Author: kakuai
created: ..
*/
#include <bits/stdc++.h>

using namespace std;

namespace std {

template <typename T>
using pqmin = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
bool maximize(T &a, const T &b) {
	return a < b ? a = b, true : false;
}
template <typename T>
bool minimize(T &a, const T &b) {
	return a > b ? a = b, true : false;
}

template <typename T>
int size32(const T &a) {
	return (int)a.size();
}

template <typename T, int D>
struct Vec : public vector<Vec<T, D - 1>> {
	static_assert(D >= 1, "Error");
	template <typename... Args>
	Vec(int n = 0, Args... args)
		: vector<Vec<T, D - 1>>(n, Vec<T, D - 1>(args...)) {}
};
template <typename T>
struct Vec<T, 1> : public vector<T> {
	Vec(int n = 0, const T &val = T()) : vector<T>(n, val) {}
};
}  // namespace std


void kakuai(void) {
	// voi26 = winner
	 int m, n;
	 cin >> m >> n;

	 Vec<int, 2> a(m + 1, n + 1, 0);

	 for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> a[i][j];
		}
	 }

	 Vec<int, 1> h(n + 1, 0), l(n + 1, 0), r(n + 1, 0);

	 int ans = 0;

	 for (int i = 1; i <= m; ++i) {

		for (int j = 1; j <= n; ++j) {
			if (a[i][j] == 1) {
				++h[j];
			} else h[j] = 0;

		}

		vector<int> stk;

		for (int j = 1; j <= n; ++j) {
			while (!stk.empty() && a[i][j] == 1 && h[stk.back()] >= h[j]) stk.pop_back();

			l[j] = stk.empty() ? 0 : stk.back();

			stk.push_back(j);
		}

		stk.clear();

		for (int j = n; j >= 1; --j) {
			while (!stk.empty() && a[i][j] == 1 && h[stk.back()] >= h[j]) stk.pop_back();

			r[j] = stk.empty() ? n + 1 : stk.back();

			stk.push_back(j);
		}


		for (int j = 1; j <= n; ++j) {
			maximize(ans, (r[j] - l[j] - 1) * h[j]);
		}
	 }

	 cout << ans;
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "qbrect"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
