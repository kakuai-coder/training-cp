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

const int MaxN = 1e6 + 5;
const int Mod = 1e9 + 7;
const int Cbit = 20;

int n, a[MaxN], dp[(1 << Cbit) + 1];

int Pow(int x, int base) {
	int res = 1;
	for (; base; base >>= 1LL, x = (1LL * x * x) % Mod) if (base & 1) {
		res = (1LL * res * x) % Mod;
	}

	return res;
}

void kakuai(void) {
	// voi26 = winner
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		dp[a[i]]++;
	}

	for (int i = 0; i < Cbit; ++i) {
		for (int mask = 0; mask < (1 << Cbit); ++mask) {
			if (!((mask >> i) & 1)) {
				dp[mask] += dp[mask ^ (1 << i)];
			}
		}
	}

	int ans = 0;

	for (int mask = 0; mask < (1 << Cbit); ++mask) {
		int c_bit = __builtin_popcount(mask);

		if (c_bit & 1) {
			ans -= Pow(2, dp[mask]) - 1;
			if (ans < 0) ans += Mod;
		} else {
			ans += Pow(2, dp[mask]) - 1;
			if (ans >= Mod) ans -= Mod;
		}
	}

	cout << ans;
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "449D"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
