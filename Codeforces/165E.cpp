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

const int maxN = 4e6 + 5, CBit = 22;

int n, a[maxN], dp[(1 << CBit) + 1];

void kakuai(void) {
	// voi26 = winner
	cin >> n;

	memset(dp, -1, sizeof(dp));

	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		dp[a[i]] = a[i];
	}

	for (int mask = 1; mask < (1 << CBit); ++mask) {
		if (~dp[mask]) continue;

		for (int i = 0; i < CBit; ++i) if ((mask >> i) & 1) {
			if (~dp[mask ^ (1 << i)]) {
				dp[mask] = dp[mask ^ (1 << i)];
				break;
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		int k = (1 << CBit) - 1;
		cout << dp[k ^ a[i]] << ' ';
	}
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "165E"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
