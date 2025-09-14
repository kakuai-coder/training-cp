/*
Author: kakuai
created: 2.8.2025
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

const int maxN = 1e5 + 5;

int n, a[maxN], phi[maxN], used[maxN];
vector<int> divs[maxN];


void kakuai(void) {
	// voi26 = winner

	for (int i = 1; i < maxN; ++i) {
		for (int j = i; j < maxN; j += i) divs[j].push_back(i);
	}

	phi[1] = 1;

	for (int i = 2; i < maxN; ++i) {
		phi[i] = i - 1;

		for (int j = 2; j * j <= i; ++j) {
			int m = i;
			while (m % j == 0) m /= j;
			if (m == i) continue;
			phi[i] = (m == 1 ? i - i / j : phi[m] * phi[i / m]);
			break;
		}
	}

	cin >> n;

	int ans = 0;

	used[1] = 1;

	for (int i = 1; i <= n + 1; ++i) {
		int t; cin >> t;
		for (auto &d : divs[t]) if (!used[d]) ans += phi[d];

		for (auto &d : divs[t]) used[d] = 1;
	}

	cout << ans;
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "a"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}
