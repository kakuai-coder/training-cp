/*
Author: kakuai
created: 5.8.2025
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

const int MaxN = 1e5 + 5, Cbit = 18, Mod = 1e9 + 7;

int n;
int a[MaxN], dp[(1 << Cbit) + 1];

inline int cube(int x) {
	int64_t tmp = 1LL * x * x * x;
	return (tmp % Mod);
}

void kakuai(void) {
	// voi26 = winner
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		dp[a[i]] = a[i];
	}

	for (int i = 0; i < Cbit; ++i) {
		for (int mask = 0; mask < (1 << Cbit); ++mask) if ((mask >> i) & 1) {
			dp[mask] |= dp[mask ^ (1 << i)];
		}
	}

	int ans = 0;

	for (int mask = 0; mask < (1 << Cbit); ++mask) {
		cerr << dp[mask] << '\n';
		ans += cube(dp[mask]);

		if (ans >= Mod) ans -= Mod;
	}

	cout << ans;
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "203881K"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
