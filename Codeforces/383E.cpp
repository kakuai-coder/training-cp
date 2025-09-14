/*
Author: kakuai
created: 4.8.2025
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

const int CBit = 24;

int n, dp[(1 << CBit) + 1];

void kakuai(void) {
	// voi26 = winner
	cin >> n;

	for (int i = 1; i <= n; ++i) {
		string s;
		cin >> s;

		int x = 0;

		for (char c : s) {
			x |= (1 << (c - 'a'));
		}

		dp[x]++;
	}

	for (int i = 0; i < CBit; ++i) {
		for (int mask = 0; mask < (1 << CBit); ++mask) if ((mask >> i) & 1) {
			dp[mask] += dp[mask ^ (1 << i)];
		}
	}

	int64_t ans = 0;

	for (int mask = 0; mask < (1 << CBit); ++mask) {
		int64_t x = 1LL * (n - dp[mask]) * (n - dp[mask]);
		ans ^= x;
	}

	cout << ans;

}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "383E"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
