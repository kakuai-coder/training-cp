/*
Author: kakuai
created: 2025.07.19
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

int m, n;
Vec<int, 2> a;

bool check(int x) {
	int ret = 1;

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) if (a[i][j] < x) {
			if (ret <= j) ret = j;
			else return false;
		}
	}

	return true;
}

void kakuai(void) {
	// voi26 = winner
	cin >> m >> n;
	a = Vec<int, 2>(m + 1, n + 1, 0);

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> a[i][j];
		}
	}

	int lo = 0, hi = m * n + 1;

	while (hi - lo > 1) {
		int mid = (lo + hi) >> 1;

		if (check(mid)) {
			lo = mid;
		} else hi = mid;
	}

	cout << lo << '\n';
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "mex"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
