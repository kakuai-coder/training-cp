/*
Author: kakuai
created: 3.8.2025
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

const int maxN = 2e6 + 5, maxM = 5005;

int n, m, a[maxN], dp[maxM][maxM], cnt[2][maxM][maxM];

void kakuai(void) {
	// voi26 = winner
	cin >> n >> m;

	vector<int> pos;

	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		if (a[i] == 0) pos.push_back(i);
	}

	pos.push_back(n + 1);

	int j = 1;

	for (int i = 1; i <= m + 1; ++i) {
		while (j < pos[i - 1]) {
			if (a[j] > 0) cnt[0][i][a[j]]++;
			if (a[j] < 0) cnt[1][i][abs(a[j])]++;
			j++;
		}

		for (int k = 1; k <= m; ++k) {
			cnt[0][i][k] += cnt[0][i][k - 1];
			cnt[1][i][k] += cnt[1][i][k - 1];
		}
	}

	int ans = 0;

	memset(dp, -0x3f, sizeof(dp));
	dp[1][0] = 0;
	dp[1][1] = 0;

	for (int i = 2; i <= m + 1; ++i) {
		for (int j = 0; j <= i; ++j) {
			int j1 = i - 1 - j;
			maximize(dp[i][j], dp[i - 1][j] + cnt[0][i][j] + cnt[1][i][j1]);
			j1 = i - j;
			if (j > 0) maximize(dp[i][j], dp[i - 1][j - 1] + cnt[0][i][j - 1] + cnt[1][i][j1]);
		}
	}

	for (int j = 0; j <= m + 1; ++j) maximize(ans, dp[m + 1][j]);

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
