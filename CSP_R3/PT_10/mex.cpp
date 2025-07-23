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

const int inf = 1e9 + 11; 


void kakuai(void) {
	// voi26 = winner
	int n, m; 
	cin >> n >> m; 
	Vec<int, 2> a(0, n + 2, m + 2), dp(-1, n + 2, m + 2);

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j];
		}
	}

	dp[1][1] = 1; 

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (i != 1 && j != 1) {
				if (dp[i - 1][j] != -1) {
					if 
				}
			}
		}
	}
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