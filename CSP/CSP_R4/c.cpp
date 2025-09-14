/*
Author: kakuai
created: 2025.07.26
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

const int maxN = 155; 
const int inf = 1e9 + 11; 

int n, l, r, k, a[maxN]; 

void kakuai(void) {
	// voi26 = winner
	cin >> n >> l >> r >> k; 

	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	vector<pair<int, int> > L, R; 

	for (int i = 1; i <= n; ++i) {
		if (i < l || i > r) R.push_back({i, a[i]});
		else L.push_back({i, a[i]});
	}
	

	Vec<int, 3> dp(size32(L) + 1, size32(R) + 1, k + 1, -inf);

	dp[0][0][0] = 0;

	int ans = -inf;

	for (int i = 0; i <= size32(L); ++i) {
		for (int j = 0; j <= size32(R); ++j) {
			for (int t = 0; t <= k; ++t) if (dp[i][j][t] > -inf) {
				if (i < size32(L)) maximize(dp[i + 1][j][t], dp[i][j][t] + L[i].second);
				if (j < size32(R)) maximize(dp[i][j + 1][t], dp[i][j][t]);
				if (i < size32(L) && j < size32(R) && t + abs(L[i].first - R[j].first) <= k) 
					maximize(dp[i + 1][j + 1][t + abs(L[i].first - R[j].first)], dp[i][j][t] + R[j].second);   
			}
		}
	}
	for (int t = 0; t <= k; ++t) {
		maximize(ans, dp[size32(L)][size32(R)][t]);
		// cout << dp[size32(L)][size32(R)][t] << '\n';
	}

	cout << ans; 

}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#define cherry "c"
	if (fopen(cherry ".inp", "r")) {
		freopen(cherry ".inp", "r", stdin);
		freopen(cherry ".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	return 0;
}